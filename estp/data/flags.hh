#pragma once

#include "estp/base/types.hh"

#include <type_traits>

namespace estp {

template <typename S, typename E>
class Flags {
    static_assert(std::is_unsigned_v<S>, "Underlying storage type must be unsigned");
    static_assert(std::is_enum_v<E>, "Flag values must be an enumeration");
public:
    using Bits = S;
    using Flag = E;
    using This = Flags<S,E>;

    constexpr Flags() : _bits{0} {}

    constexpr Flags(Flag flag) : _bits{_bit(flag)} {}

    template<typename... Args>
    constexpr Flags(Flag f, Args ...rest) :
        _bits{ static_cast<Bits>(_bit(f) | (Flags{rest...}).bits()) } {}

    constexpr auto& Set(Flags rhs) {
        _bits |= rhs.bits();
        return *this;
    }

    template<typename... T>
    constexpr auto& Set(Flag f, T ...rest) {
        return Set(Flags{f, rest...});
    }

    constexpr auto& Clear(Flags rhs) {
        _bits &= (~rhs.bits());
        return *this;
    }

    template<typename... T>
    constexpr auto& Clear(Flag f, T ...rest) {
        return Clear(Flags{f, rest...});
    }

    constexpr auto& Toggle(Flags rhs) {
        _bits ^= rhs.bits();
        return *this;
    }

    template<typename... T>
    constexpr auto& Toggle(Flag f, T ...rest) {
        return Toggle(Flags{f, rest...});
    }

    constexpr bool Test(Flag flag) const {
        return (bits() & _bit(flag));
    }

    constexpr bool TestAndSet(Flag f) {
        bool was_set = Test(f);
        Set(f);
        return !was_set;
    }

    constexpr bool TestAndClear(Flag f) {
        bool const was_set = Test(f);
        Clear(f);
        return was_set;
    }

    constexpr bool Any() const {
        return bits() != 0;
    }

    constexpr bool TestAny(Flags other) const {
        return (bits() & other.bits());
    }

    template<typename... T>
    constexpr bool TestAny(Flag f, T ...rest) const {
        return TestAny(Flags{f, rest...});
    }

    constexpr bool TestAndSetAny(Flags other) {
        bool all_were_set = TestAll(other);
        Set(other);
        return !all_were_set;
    }

    template<typename... T>
    constexpr bool TestAndSetAny(Flag f, T ...rest) {
        return TestAndSetAny(Flags{f, rest...});
    }

    constexpr bool TestAndClearAny(Flags other) {
        bool were_any_set = TestAny(other);
        Clear(other);
        return were_any_set;
    }

    template<typename... T>
    constexpr bool TestAndClearAny(Flag f, T ...rest) {
        return TestAndClearAny(Flags{f, rest...});
    }

    constexpr bool TestAll(Flags other) const {
        return other.bits() == (bits() & other.bits());
    }

    template<typename... T>
    constexpr bool TestAll(Flag f, T ...rest) const {
        return TestAll(Flags{f, rest...});
    }

    constexpr bool TestAndSetAll(Flags other) {
        bool none_were_set = !TestAny(other);
        Set(other);
        return none_were_set;
    }

    template<typename... T>
    constexpr bool TestAndSetAll(Flag f, T ...rest) {
        return TestAndSetAll(Flags{f, rest...});
    }

    constexpr bool TestAndClearAll(Flags other) {
        bool were_all_set = TestAll(other);
        Clear(other);
        return were_all_set;
    }

    template<typename... T>
    constexpr bool TestAndClearAll(Flag f, T ...rest) {
        return TestAndClearAll(Flags{f, rest...});
    }

    constexpr bool None() const {
        return 0 == bits();
    }

    constexpr Bits bits() const { return _bits; }

    constexpr static This from_bits(Bits bits) {
        return This{bits};
    }

private:
    explicit constexpr Flags(Bits bits) : _bits{bits} {}

    constexpr static Bits _bit(Flag flag) {
        return static_cast<Bits>(Bits{1} << static_cast<Bits>(flag));
    }

    Bits _bits;
};

template<typename S, typename E>
constexpr bool operator==(Flags<S,E> lhs, Flags<S,E> rhs) {
    return lhs.bits() == rhs.bits();
}

template<typename S, typename E>
constexpr bool operator!=(Flags<S,E> lhs, Flags<S,E> rhs) {
    return lhs.bits() != rhs.bits();
}


}  // namespace estp
