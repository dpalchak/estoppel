#pragma once

#include "base/types.h"

namespace estp {

template<typename T>
constexpr auto bitsize() -> std::integral_constant<size_t, sizeof(T)*CHAR_BIT> {
	return {};
}

struct Lsb : NamedUnsigned<Lsb> {};
struct Msb : NamedUnsigned<Msb> {};
struct Width : NamedUnsigned<Width> {};

// For all bitmask() functions the MSB and LSB are included in the mask
// For example: bitmask<uint8_t>(Lsb{0}, Msb{7}) == 0xFF

template<typename T>
constexpr T bitmask(Lsb lsb) {
    return static_cast<T>(static_cast<T>(~0) << lsb.as_unsigned);
}

template<typename T>
constexpr T bitmask(Msb msb) {
    return static_cast<T>(static_cast<T>(~0) >>
    		(bitsize<T>() - msb.as_unsigned - 1));
}

template<typename T>
constexpr T bitmask(Msb msb, Lsb lsb) {
	return bitmask<T>(msb) & bitmask<T>(lsb);
}

template<typename T>
constexpr T bitmask(Lsb lsb, Msb msb) {
	return bitmask<T>(msb, lsb);
}

template<typename T>
constexpr T bitmask(Msb msb, Width width) {
    if (0 == width.as_unsigned) {
    	return 0;
    } else {
    	return bitmask<T>(msb, Lsb{msb.as_unsigned - width.as_unsigned + 1});
    }
}

template<typename T>
constexpr T bitmask(Lsb lsb, Width width) {
	if (0 == width.as_unsigned) {
		return 0;
	} else {
		return bitmask<T>(lsb, Msb{lsb.as_unsigned + width.as_unsigned - 1});
	}
}

#ifdef __GNUC__

inline size_t ctz(unsigned char value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_ctz(value));
	}
}

inline size_t ctz(unsigned short value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_ctz(value));
	}
}

inline size_t ctz(unsigned int value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_ctz(value));
	}
}
inline size_t ctz(unsigned long value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_ctzl(value));
	}
}

inline size_t ctz(unsigned long long value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_ctzll(value));
	}
}

inline size_t clz(unsigned char value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_clz(value)) -
				(bitsize<unsigned int>() - bitsize<unsigned char>());
	}
}

inline size_t clz(unsigned short value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_clz(value)) -
				(bitsize<unsigned int>() - bitsize<unsigned short>());
	}
}

inline size_t clz(unsigned int value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_clz(value));
	}
}
inline size_t clz(unsigned long value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_clzl(value));
	}
}

inline size_t clz(unsigned long long value) {
	if (0 == value) {
		return -1;
	} else {
		return size_t(__builtin_clzll(value));
	}
}

template<typename T>
inline size_t FindMsb(T value) {
	if (0 == value) {
		return -1;
	} else {
		return bitsize<T>() - clz(value) - 1;
	}
}

#endif // __GNUC__

} // Namespace
