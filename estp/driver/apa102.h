#pragma once

#include "estp/base/assert.h"
#include "estp/base/macros.h"
#include "estp/base/types.h"
#include "estp/data/accumulator.h"
#include "estp/data/bitfield.h"
#include "estp/data/color.h"
#include "estp/data/span.h"

#include <algorithm>
#include <cstring>

namespace estp {

class Apa102 {
public:
    constexpr static uint8_t kLeader[] = {0,0,0,0};
    constexpr static uint8_t kTrailer[] = {0xE0,0,0,0};
    const static Apa102 kOff;

    constexpr Apa102() {}

    constexpr Apa102(RgbColor8 color) : _blue{color.blue}, _green{color.green}, _red{color.red} {}

    constexpr Apa102(RgbColor8 color, uint8_t scale) :
        _blue{color.blue}, _green{color.green}, _red{color.red} {
            _scale = scale;
    }

    constexpr Apa102& SetColor(RgbColor8 rgb) {
        _blue = rgb.blue;
        _green = rgb.green;
        _red = rgb.red;
        return *this;
    }

    constexpr Apa102& operator= (RgbColor8 rgb) {
        SetColor(rgb);
        return *this;
    }

    constexpr RgbColor8 color() const {
        return RgbColor8{.red = _red, .green = _green, .blue = _blue};
    }

    constexpr Apa102& SetScale(uint8_t i) {
        _scale = i;
        return *this;
    }

    constexpr uint8_t scale() const {
        return _scale();
    }

    constexpr Apa102& SetRed(uint8_t r) {
        _red = r;
        return *this;
    }

    constexpr uint8_t red() const {
        return _red;
    }

    constexpr Apa102& SetGreen(uint8_t g) {
        _green = g;
        return *this;
    }

    constexpr uint8_t green() const {
        return _green;
    }

    constexpr Apa102& SetBlue(uint8_t b) {
        _blue = b;
        return *this;
    }

    constexpr uint8_t blue() const {
        return _blue;
    }

    constexpr Apa102& SetOff() {
        return SetScale(0);
    }

    inline void SerializeInto(Span<uint8_t> dest) const {
        EXPECTS(dest.size() >= 4);
        std::memcpy(dest.data(), this, 4);
    }

    inline void SerializeInto(Accumulator<uint8_t> &dest) const {
        EXPECTS(dest.empty_size() >= 4);
        dest.PushBack(_control);
        dest.PushBack(_blue);
        dest.PushBack(_green);
        dest.PushBack(_red);
    }

    inline Span<uint8_t const> as_span() const {
        return {reinterpret_cast<uint8_t const*>(this), 4};
    }

private:
    union {
        Bitfield8<Lsb(0), Width(5)> _scale;
        uint8_t _control{0xE0};
    };
    uint8_t _blue = 0;
    uint8_t _green = 0;
    uint8_t _red = 0;

};

constexpr Apa102 Apa102::kOff{};

static_assert(4 == sizeof(Apa102), "Compiler generates and invalid class layout for Apa102");

} // namespace
