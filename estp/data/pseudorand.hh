#pragma once

#include "estp/base/types.hh"

namespace estp {

class PseudoRand32 {
public:
    using Bit = uint32_t;
    using Word = uint32_t;

    constexpr PseudoRand32() {}

    constexpr PseudoRand32(uint32_t a) : _state{a, 0xFACADE, 0xA9CADE, 42} {}

    constexpr PseudoRand32(uint32_t a, uint32_t b, uint32_t c, uint32_t d) :
        _state{a, b, c, d} {}

    inline uint32_t Next() {
        // Xorshift128 algorithm from p. 5 of Marsaglia, "Xorshift RNGs"
        // Copied from wikipedia
        uint32_t temp = _state[3];
        uint32_t const s0 = _state[0];

        _state[3] = _state[2];
        _state[2] = _state[1];
        _state[1] = _state[0];

        temp ^= temp << 11;
        temp ^= temp >> 8;
        return _state[0] = temp ^ s0 ^ (s0 >> 19);
    }

private:
    uint32_t _state[4] {0xFACADE, 0xDEADBEEF, 0xA9CADE, 42};
};

}
