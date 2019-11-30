#pragma once

#include "estp/base/types.h"
#include "estp/base/meta.h"

namespace estp {

template<typename T>
constexpr auto bitsize() -> IndexConstant<static_cast<Index>(sizeof(T)*CHAR_BIT)> {
    return {};
}

// Use enums instead of StrongType here so that these values can be used as non-type template
// parameters as well as ordinary values
enum class Lsb : Index {kMin = 0};
enum class Msb : Index {kMin = 0};
enum class Width : Index {kMin = 0};

// For all bitmask() functions the MSB and LSB are included in the mask
// For example: bitmask<uint8_t>(Lsb{0}, Msb{7}) == 0xFF

template<typename T>
constexpr T bitmask(Lsb lsb) {
    return static_cast<T>(static_cast<T>(~0) << static_cast<Index>(lsb));
}

template<typename T>
constexpr T bitmask(Msb msb) {
    return static_cast<T>(static_cast<T>(~0) >>
            (bitsize<T>() - static_cast<Index>(msb) - 1));
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
    if (0 == static_cast<Index>(width)) {
        return 0;
    } else {
        return bitmask<T>(msb, Lsb{static_cast<Index>(msb) - static_cast<Index>(width) + 1});
    }
}

template<typename T>
constexpr T bitmask(Lsb lsb, Width width) {
    if (0 == static_cast<Index>(width)) {
        return 0;
    } else {
        return bitmask<T>(lsb, Msb{static_cast<Index>(lsb) + static_cast<Index>(width) - 1});
    }
}

#ifdef __GNUC__

inline Index ctz(unsigned char value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_ctz(value));
    }
}

inline Index ctz(unsigned short value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_ctz(value));
    }
}

inline Index ctz(unsigned int value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_ctz(value));
    }
}
inline Index ctz(unsigned long value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_ctzl(value));
    }
}

inline Index ctz(unsigned long long value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_ctzll(value));
    }
}

inline Index clz(unsigned char value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_clz(value)) -
            (bitsize<unsigned int>() - bitsize<unsigned char>());
    }
}

inline Index clz(unsigned short value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_clz(value)) -
            (bitsize<unsigned int>() - bitsize<unsigned short>());
    }
}

inline Index clz(unsigned int value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_clz(value));
    }
}
inline Index clz(unsigned long value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_clzl(value));
    }
}

inline Index clz(unsigned long long value) {
    if (0 == value) {
        return -1;
    } else {
        return Index(__builtin_clzll(value));
    }
}

template<typename T>
inline Index FindMsb(T value) {
    if (0 == value) {
        return -1;
    } else {
        return bitsize<T>() - clz(value) - 1;
    }
}

#endif // __GNUC__

} // Namespace
