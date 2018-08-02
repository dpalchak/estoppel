#pragma once

#include <cstdint>
#include <cstddef>

namespace estp {

using size_t = std::size_t;

// A convenience typedef for readability
template<std::size_t N>
using StringLiteral = char const (&)[N];

// Readability types for 'zero' (aka null) terminated strings
// These are borrowed from the C++ Guideline Support Library (GSL)
using ZString = char *;
using CZString = char const *;

}
