#pragma once

#include "base/types.h"

#include <cstdint>
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
using Conditional = Invoke<::std::conditional<GetValue<If>(),Then,Else> >;

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

// Strips all reference and cv qualifiers from a type
template<typename T>
using Unqualified = Invoke< std::remove_reference< Invoke<::std::remove_cv<T> > > >;

// Standard Library Type Traits as LazyBools
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

// Control flow
template<typename If, typename Then=void>
using EnableIf = Invoke<::std::enable_if<If::value,Then> >;

template<typename T, typename C>
using EnableIfSame = EnableIf< IsSame<Decay<T>, Decay<C>> >;

template<typename T, typename C>
using EnableIfDifferent = EnableIf< Not< IsSame<Decay<T>, Decay<C>> > >;

template<typename From, typename To>
using IsConvertible = Bool<GetValue<::std::is_convertible<From,To>>(), From, To>;

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

// Shortcuts for integral constants and native types
using Void = Type<void>;

template<char V>
struct CharConstant : public std::integral_constant<char, V> {};

template<int V>
struct IntConstant : public std::integral_constant<int, V> {};

template<unsigned V>
struct UnsignedConstant : public std::integral_constant<unsigned, V> {};

template<Index V>
struct IndexConstant : public std::integral_constant<Index, V> {};

template<std::uint8_t V>
struct Uint8Constant : public std::integral_constant<std::uint8_t, V> {};

template<std::uint16_t V>
struct Uint16Constant : public std::integral_constant<std::uint16_t, V> {};

template<std::uint32_t V>
struct Uint32Constant : public std::integral_constant<std::uint32_t, V> {};

template<std::uint64_t V>
struct Uint64Constant : public std::integral_constant<std::uint64_t, V> {};

template<std::int8_t V>
struct Int8Constant : public std::integral_constant<std::int8_t, V> {};

template<std::int16_t V>
struct Int16Constant : public std::integral_constant<std::int16_t, V> {};

template<std::int32_t V>
struct Int32Constant : public std::integral_constant<std::int32_t, V> {};

template<std::int64_t V>
struct Int64Constant : public std::integral_constant<std::int64_t, V> {};

// Useful functions for working with index sequences
template <std::size_t Offset, std::size_t ... Indices>
constexpr auto AddOffsetToSequence(std::index_sequence<Indices...>) -> std::index_sequence<(Indices+Offset)...> {
    return {};
}

template <std::size_t Offset, std::size_t N>
struct MakeOffsetIndexSequence : public decltype(AddOffsetToSequence<Offset>(std::make_index_sequence<N>{})) {};

template <std::size_t Offset, std::size_t ... Indices>
constexpr auto SubtractOffsetFromSequence(std::index_sequence<Indices...>) -> std::index_sequence<(Indices-Offset)...> {
    return {};
}

template <std::size_t Offset, std::size_t N>
struct MakeNegativeOffsetIndexSequence : public decltype(SubtractOffsetFromSequence<Offset>(std::make_index_sequence<N>{})) {};

template <std::size_t Offset, std::size_t ... Indices>
constexpr auto SubtractSequenceFromOffset(std::index_sequence<Indices...>) -> std::index_sequence<(Offset-Indices)...> {
    return {};
}

template <std::size_t N>
struct MakeReverseIndexSequence : public decltype(SubtractSequenceFromOffset<N-1>(std::make_index_sequence<N>{})) {};


} // namespace estp
