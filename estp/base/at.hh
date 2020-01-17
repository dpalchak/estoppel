#pragma once

#include "estp/base/assert.hh"
#include "estp/base/casting.hh"
#include "estp/base/types.hh"

#include <array>

// Basic implementation of the at() function as described in the C++ GSL

namespace estp {

template<typename T, Index N>
constexpr decltype(auto) at(T (&arr)[N], Index index) {
	EXPECTS(0 <= index && index < N);
	return arr[index];
}

template<typename T, std::size_t N>
constexpr decltype(auto) at(std::array<T, N> &arr, Index index) {
	EXPECTS(0 <= index && index < narrow_cast<Index>(N));
	return arr[index];
}

template<typename Container>
constexpr decltype(auto) at(Container &c, Index index) {
	EXPECTS(0 <= index && index < narrow_cast<Index>(c.size()));
	return c[index];
}

template<typename T>
constexpr decltype(auto) at(std::initializer_list<T> c, Index index) {
	EXPECTS(0 < = index && index < narrow_cast<Index>(c.size()));
	return *(c.begin() + index);
}

}
