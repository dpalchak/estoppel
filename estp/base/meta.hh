#pragma once

#include "estp/base/types.hh"

#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>

namespace estp {

// Metaprogramming functions
// Credit: many of these are borrow from R. Martinho Fernandes
// See his website Flaming Dangerous (rmf.io)

// Saves redundant typename ... ::type
template<typename Meta>
using Invoke = typename Meta::type;

// Use a template function to get the value of a type so that it can be
// specialized if necessary
template<typename T>
constexpr auto GetValue(T const&) {
	return T::value;
}

// Provide an alternative form that doesn't require type instantiation
template<typename T>
constexpr auto GetValue() {
	return T::value;
}

// Simple identity/alias templates
// These are useful for inhibiting type deduction, since the compiler
// won't deduce dependent types
template <typename T>
struct Type { using type = T; };

template <typename T>
using Identity = Invoke<Type<T>>;

template<typename T>
using Decay = Invoke<::std::decay<T>>;

template<typename...>
using Void = void;

// Lazy bool type, useful for postponing evaluation of a compile-time expression
template<bool B, typename...>
struct LazyBool : public std::integral_constant<bool, B> {};

template<bool B, typename... T>
using Bool = LazyBool<B, T...>;

template<typename... T>
using True = Bool<true, T...>;

template<typename... T>
using False = Bool<false, T...>;

template<typename T>
using Not = Bool<!GetValue<T>()>;

template<typename If, typename Then, typename Else>
using Conditional = Invoke<::std::conditional<If::value,Then,Else> >;

// Meta-logical Or
template<typename... T>
struct Or : public False<T...> {};

template<typename Head, typename... Tail>
struct Or<Head, Tail...> : public Conditional<Head, True<>, Or<Tail...> > {};

// Meta-logical And
template<typename...>
struct And : public True<> {};

template<typename Head, typename... Tail>
struct And<Head, Tail...> : public Conditional<Head, And<Tail...>, False<> > {};

// Standard Library Type Traits as LazyBools
template<typename T>
using IsConst = Bool<::std::is_const<T>::value, T>;

template<typename T>
using IsIntegral = Bool<::std::is_integral<T>::value, T>;

template<typename T>
using IsSigned = Bool<::std::is_signed<T>::value, T>;

template<typename T>
using IsUnsigned = Bool<::std::is_unsigned<T>::value, T>;

template<typename T>
using IsClass = Bool<::std::is_class<T>::value, T>;

template<typename B, typename D>
using IsBaseOf = Bool<::std::is_base_of<B,D>::value, B, D>;

template<typename D, typename B>
using IsDerivedFrom = Bool<IsBaseOf<B,D>::value, D, B>;

template<typename T>
using IsAbstract = Bool<::std::is_abstract<T>::value, T>;

template<typename T>
using IsRvalue = Bool<::std::is_rvalue_reference<T&&>::value, T>;

template<typename T>
using IsLvalue = Bool<::std::is_lvalue_reference<T&>::value, T>;

template<typename T, typename S>
using IsSame = Bool<::std::is_same<T,S>::value, T, S>;

template<typename T, typename S>
using IsConvertible = Bool<::std::is_convertible<T,S>::value, T, S>;

template<typename T, typename = Void<> >
struct HasSize : False<T> {};

template<typename T>
struct HasSize<T, Void< decltype(std::size(std::declval<T>())) > > : True<T> {};

template<typename T, typename = Void<> >
struct HasData : False<T> {};

template<typename T>
struct HasData<T, Void< decltype(std::data(std::declval<T>())) > > : True<T> {};

// Control flow
template<typename If, typename Then=void>
using EnableIf = Invoke<::std::enable_if<If::value,Then> >;

template<typename T, typename C>
using EnableIfSame = EnableIf< IsSame<Decay<T>, Decay<C>> >;

template<typename T, typename C>
using EnableIfDifferent = EnableIf< Not< IsSame<Decay<T>, Decay<C>> > >;

// Traits

// Strips all reference and cv qualifiers from a type
template<typename T>
using Unqualified = Invoke< std::remove_reference< Invoke<::std::remove_cv<T> > > >;

template<typename T>
using AddConst = Invoke< std::add_const<T> >;

template<typename T>
using RemoveConst = Invoke< std::remove_const<T> >;

template<typename T>
using AddPointer = Invoke< ::std::add_pointer<T> >;

template<typename T>
using RemovePointer = Invoke< ::std::remove_pointer<T> >;

template<typename T>
using ElementType = RemovePointer<decltype(std::data(std::declval<T>()))>;

template<typename T>
struct FunctionTraits;

template<typename R, typename... A>
struct FunctionTraits<R(A...)> {
  using ReturnType = R;
  using ArgTypes = ::std::tuple<A...>;
  using Signature = R(A...);
  using PointerType = Signature *;
};

template<typename SIG>
using FunctionPointer = typename FunctionTraits<SIG>::PointerType;

template<typename T, typename C=void>
struct MethodTraits;

template<typename R, typename... A, typename C>
struct MethodTraits<R(A...), C> {
  using ReturnType = R;
  using ArgTypes = ::std::tuple<A...>;
  using ClassType = C;
  using Signature = R(A...);
  using PointerType = Signature C::*;
};

template<typename R, typename... A, typename C>
struct MethodTraits<R(C::*)(A...), void> {
  using ReturnType = R;
  using ArgTypes = ::std::tuple<A...>;
  using ClassType = C;
  using Signature = R(A...);
  using PointerType = Signature C::*;
};

template<typename R, typename... A, typename C>
struct MethodTraits<R(C::*)(A...) const, void> {
  using ReturnType = R;
  using ArgTypes = ::std::tuple<A...>;
  using ClassType = C const;
  using Signature = R(A...);
  using PointerType = Signature ClassType::*;
};

template<typename SIG, typename C=void>
using MethodPointer = typename MethodTraits<SIG,C>::PointerType;

// Useful functions for working with Index sequences
template<Index... Is>
using IndexSequence = std::integer_sequence<Index, Is...>;

template<Index N>
using MakeIndexSequence = std::make_integer_sequence<Index, N>;

template<typename... T>
using IndexSequenceFor = MakeIndexSequence<sizeof...(T)>;

template<Index Offset, Index... Is>
constexpr auto AddOffsetToIndexSequence(IndexSequence<Is...>) -> IndexSequence<(Offset+Is)...> {
    return {};
}

template <Index Offset, Index N>
using MakeOffsetIndexSequence = decltype(AddOffsetToIndexSequence<Offset>(MakeIndexSequence<N>{}));

} // namespace estp
