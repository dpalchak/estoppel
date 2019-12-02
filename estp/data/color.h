#pragma once

#include "estp/base/types.h"

#include <limits>

namespace estp {

template<typename T>
struct RgbColor {
    T red = 0;
    T green = 0;
    T blue = 0;

    constexpr static T kChannelMax{std::numeric_limits<T>::max()};
    constexpr static RgbColor kBlack{0,0,0};
    constexpr static RgbColor kWhite{kChannelMax, kChannelMax, kChannelMax};
    constexpr static RgbColor kRed{kChannelMax, 0, 0};
    constexpr static RgbColor kGreen{0, kChannelMax, 0};
    constexpr static RgbColor kBlue{0, 0, kChannelMax};
    constexpr static RgbColor kCyan{0, kChannelMax, kChannelMax};
    constexpr static RgbColor kMagenta{kChannelMax, 0, kChannelMax};
    constexpr static RgbColor kYellow{kChannelMax, kChannelMax, 0};
};

using RgbColor8 = RgbColor<uint8_t>;

}
