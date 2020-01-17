#pragma once

#include "estp/base/bits.hh"
#include "estp/base/types.hh"

#include <type_traits>

namespace estp {

template <typename T, bool = std::is_enum_v<T>>
struct BitfieldStorage {
    using type = std::underlying_type_t<T>;
};

template <typename T>
struct BitfieldStorage<T, false> {
    using type = T;
};

template<typename T>
using BitfieldStorage_t = typename BitfieldStorage<T>::type;

template<Lsb LSB, Width WIDTH, typename VALUE, typename STORAGE=BitfieldStorage_t<VALUE> >
class Bitfield {
public:
    using Value = VALUE;
    using Storage = STORAGE;
    static constexpr Lsb kLsb = LSB;
    static constexpr Width kWidth = WIDTH;
    static constexpr Msb kMsb{static_cast<Index>(kLsb) + static_cast<Index>(kWidth) - 1};
    static constexpr Storage kMask = bitmask<Storage>(kLsb, kWidth);

    static_assert(sizeof(Value) == sizeof(Storage),
        "Value type must be same size as Storage type");
    static_assert(std::is_integral_v<Storage>, "Storage type must be integral");
    static_assert(std::is_unsigned_v<Storage>, "Storage type must be unsigned");
    static_assert(static_cast<Index>(kLsb) >= 0, "LSB can not be negative");
    static_assert(static_cast<Index>(kWidth) >= 0, "Width can not be negative");
    static_assert(static_cast<Index>(kMsb) < Index(sizeof(STORAGE)*CHAR_BIT),
        "MSB can not exceed bit width of storage type");

    constexpr Bitfield& operator=(Value v) {
        _storage = (_storage & ~kMask) | ((static_cast<Storage>(v) << static_cast<Index>(kLsb)) & kMask);
        return *this;
    }

    constexpr Value operator()() const {
        return Value{static_cast<Storage>((_storage & kMask) >> static_cast<Index>(kLsb))};
    }

    constexpr operator Value() const {
        return (*this)();
    }

private:
    Storage _storage;
};

template<Lsb LSB, Width WIDTH>
using Bitfield8 = Bitfield<LSB, WIDTH, uint8_t>;

template<Lsb LSB, Width WIDTH>
using Bitfield16 = Bitfield<LSB, WIDTH, uint16_t>;

template<Lsb LSB, Width WIDTH>
using Bitfield32 = Bitfield<LSB, WIDTH, uint32_t>;

} // namespace
