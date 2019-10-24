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

// A convenience typedef for readability
template<auto N>
using StringLiteral = char const (&)[N];

// Readability types for 'zero' (aka null) terminated strings
// These are borrowed from the C++ Guideline Support Library (GSL)
using ZString = char *;
using CZString = char const *;

// Template classes for creating named types
// Named types are useful for improving call site readability and
// differentiating function overloads. These are simple types that support
// aggregate initialization.

template<typename Name>
struct NamedIndex {
	Index as_index;
};

template<typename Name>
struct NamedInt8 {
	int8_t as_int8;
};

template<typename Name>
struct NamedInt16 {
	int16_t as_int16;
};

template<typename Name>
struct NamedInt32 {
	int32_t as_int32;
};

template<typename Name>
struct NamedInt64 {
	int64_t as_int64;
};

template<typename Name>
struct NamedInt {
	int8_t as_int;
};

template<typename Name>
struct NamedUint8 {
	uint8_t as_uint8;
};

template<typename Name>
struct NamedUint16 {
	uint16_t as_uint16;
};

template<typename Name>
struct NamedUint32 {
	uint32_t as_uint32;
};

template<typename Name>
struct NamedUint64 {
	uint64_t as_uint64;
};

template<typename Name>
struct NamedUnsigned {
	unsigned as_unsigned;
};

template<typename Name>
struct NamedFloat {
	float as_float;
};

template<typename Name>
struct NamedDouble {
	double as_double;
};

template<typename Name>
struct NamedBool {
	bool as_bool;
};

// We don't use our own IsPointer here to avoid circular dependency in the header files
template<typename T, typename = typename std::enable_if< std::is_pointer<T>::value >::type >
using Owner = T;


} // namespace estp
