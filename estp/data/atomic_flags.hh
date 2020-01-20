#pragma once

#include "estp/base/types.hh"
#include "estp/data/flags.hh"

#include <atomic>
#include <type_traits>

namespace estp {

template <typename S, typename E>
class AtomicFlags {
    static_assert(std::is_unsigned_v<S>, "Underlying storage type must be unsigned");
    static_assert(std::is_enum_v<E>, "Flag values must be an enumeration");
public:
    using Bits = S;
    using Flag = E;
    using FlagsValue = Flags<S,E>;
    using This = AtomicFlags<S,E>;

    constexpr AtomicFlags() : _bits{0} {}

    constexpr AtomicFlags(Flag flag) : _bits{_bit(flag)} {}

    template<typename... Args>
    constexpr AtomicFlags(Flag f, Args ...rest) :
        _bits{ static_cast<Bits>(_bit(f) | (FlagsValue{rest...}).bits()) } {}

    constexpr auto& Set(FlagsValue rhs) {
        _bits |= rhs.bits();
        return *this;
    }

    template<typename... T>
    auto& Set(Flag f, T ...rest) {
        return Set(FlagsValue{f, rest...});
    }

    auto& Clear(FlagsValue rhs) {
        _bits &= (~rhs.bits());
        return *this;
    }

    template<typename... T>
    auto& Clear(Flag f, T ...rest) {
        return Clear(FlagsValue{f, rest...});
    }

    auto& Toggle(FlagsValue rhs) {
        _bits ^= rhs.bits();
        return *this;
    }

    template<typename... T>
    auto& Toggle(Flag f, T ...rest) {
        return Toggle(FlagsValue{f, rest...});
    }

    bool Test(Flag flag) const {
        return (Load().bits() & _bit(flag));
    }

    bool TestAndSet(Flag f) {
        Bits prev = _bits.fetch_or(_bit(f));
        return (~prev & _bit(f));
    }

    bool TestAndClear(Flag f) {
        Bits prev = _bits.fetch_and(static_cast<Bits>(~_bit(f)));
        return (prev & _bit(f));
    }

    bool Any() const {
        return Load().bits() != 0;
    }

    bool TestAny(FlagsValue other) const {
        return (Load().bits() & other.bits());
    }

    template<typename... T>
    bool TestAny(Flag f, T ...rest) const {
        return TestAny(FlagsValue{f, rest...});
    }

    bool TestAndSetAny(FlagsValue other) {
        Bits prev = _bits.fetch_or(other.bits());
        return (~prev & other.bits());
    }

    template<typename... T>
    bool TestAndSetAny(Flag f, T ...rest) {
        return TestAndSetAny(FlagsValue{f, rest...});
    }

    bool TestAndClearAny(FlagsValue other) {
        Bits prev = _bits.fetch_and(static_cast<Bits>(~other.bits()));
        return (prev & other.bits());
    }

    template<typename... T>
    bool TestAndClearAny(Flag f, T ...rest) {
        return TestAndClearAny(FlagsValue{f, rest...});
    }

    bool TestAll(FlagsValue other) const {
        return other.bits() == (Load().bits() & other.bits());
    }

    template<typename... T>
    bool TestAll(Flag f, T ...rest) const {
        return TestAll(FlagsValue{f, rest...});
    }

    bool TestAndSetAll(FlagsValue other) {
        Bits prev = _bits.fetch_or(other.bits());
        return 0 == (prev & other.bits());
    }

    template<typename... T>
    bool TestAndSetAll(Flag f, T ...rest) {
        return TestAndSetAll(FlagsValue{f, rest...});
    }

    bool TestAndClearAll(FlagsValue other) {
        Bits prev = _bits.fetch_and(static_cast<Bits>(~other.bits()));
        return other.bits() == (prev & other.bits());
    }

    template<typename... T>
    bool TestAndClearAll(Flag f, T ...rest) {
        return TestAndClearAll(FlagsValue{f, rest...});
    }

    bool None() const {
        return 0 == Load().bits();
    }

    inline void Store(FlagsValue flags) {
        _bits.store(flags.bits());
    }

    inline FlagsValue Load() const {
        return FlagsValue::from_bits(_bits.load());
    }

    inline operator FlagsValue() const {
        return Load();
    }

    inline auto& operator= (FlagsValue flags) {
        Store(flags);
        return *this;
    }

    inline FlagsValue Exchange(FlagsValue flags) {
        Bits prev = _bits.exchange(flags.bits());
        return FlagsValue{prev};
    }

    constexpr static This from_bits(Bits bits) {
        return This{bits};
    }

private:
    explicit constexpr AtomicFlags(Bits bits) : _bits{bits} {}

    constexpr static Bits _bit(Flag flag) {
        return static_cast<Bits>(Bits{1} << static_cast<Bits>(flag));
    }

    std::atomic<Bits> _bits;
};

template<typename S, typename E>
bool operator==(AtomicFlags<S,E> const &lhs, AtomicFlags<S,E> const &rhs) {
    return lhs.Load().bits() == rhs.Load().bits();
}

template<typename S, typename E>
bool operator!=(AtomicFlags<S,E> const &lhs, AtomicFlags<S,E> const &rhs) {
    return lhs.Load().bits() != rhs.Load().bits();
}


}  // namespace estp
