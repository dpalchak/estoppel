#pragma once

#include "estp/base/macros.h"
#include "estp/base/types.h"

#include <type_traits>
#include <utility>

namespace estp {

namespace _casting {

template<typename T, typename U>
constexpr bool HaveDifferentSignedness() {
	return std::is_signed<T>::value != std::is_signed<U>::value;
}

template<typename T>
constexpr bool IsPositive(T t) {
	return t >= T();
}

} // namespace _casting

template<typename T, typename U>
INLINE constexpr static decltype(auto) narrow_cast(U && u) noexcept {
    return static_cast<T>(std::forward<U>(u));
}

template<typename T, typename U>
INLINE constexpr static decltype(auto) range_cast(U && u) noexcept {
    return static_cast<T>(std::forward<U>(u));
}

template<typename T, typename U>
inline T narrow(U u) {
    T t = narrow_cast<T>(u);
    ASSERT(static_cast<U>(t) == u);
    if(_casting::HaveDifferentSignedness<T,U>()) {
    	ASSERT(_casting::IsPositive<T>(t) == _casting::IsPositive<U>(u));
    }
    return t;
}

template<typename T, typename U>
INLINE constexpr static decltype(auto) down_cast(U && u) noexcept {
	return static_cast<T>(std::forward<U>(u));
}

template<typename T, typename U>
INLINE constexpr static decltype(auto) up_cast(U && u) noexcept {
	return static_cast<T>(std::forward<U>(u));
}

template<typename E>
INLINE constexpr static decltype(auto) enum_cast(E val) noexcept {
  return static_cast<typename ::std::underlying_type<E>::type>(val);
}

} // namespace estp
