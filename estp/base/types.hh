#pragma once

#include <cstdint>
#include <cstddef>
#include <climits>
#include <type_traits>

namespace estp {

// Use signed values for sizes and indices
// Undefined overflow/underflow behavior can be eliminated using the
// '-fwrapv' flag with GCC/Clang
using Index = std::ptrdiff_t;
using Size = Index;

// A convenience typedef for readability
template<auto N>
using StringLiteral = char const (&)[N];

// Readability types for 'zero' (aka null) terminated strings
// These are borrowed from the C++ Guideline Support Library (GSL)
using ZString = char *;
using CZString = char const *;

// Template class for creating strong types
// Strong types are useful for improving call site readability and
// differentiating function overloads. The StrongType<> class is intended
// to be used as the base class for a user-defined strong type
template<typename Value, typename Tag>
struct StrongType {
    Value v;
};

// We don't use our own IsPointer here to avoid circular dependency in the header files
template<typename T, typename = std::enable_if_t< std::is_pointer_v<T> > >
using Owner = T;

// Shortcuts for integral constants and native types
template<Index V>
struct IndexConstant : public std::integral_constant<Index, V> {};

template<Index V>
constexpr IndexConstant<V> Index_k{};

template<char V>
struct CharConstant : public std::integral_constant<char, V> {};

template<char V>
constexpr CharConstant<V> Char_k{};

template<int V>
struct IntConstant : public std::integral_constant<int, V> {};

template<unsigned V>
struct UnsignedConstant : public std::integral_constant<unsigned, V> {};

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
} // namespace estp
