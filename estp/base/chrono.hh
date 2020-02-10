#pragma once

#include "estp/base/types.hh"

#include <chrono>
#include <ratio>

namespace estp {

using Duration = std::chrono::duration<int32_t>;

template<typename C, typename D = Duration>
using TimePoint = std::chrono::time_point<C, D>;

using Microseconds = std::chrono::duration<int64_t, std::micro>;
// 2^31 milliseconds = 24.8 days (596 hours)
using Milliseconds = std::chrono::duration<int32_t, std::milli>;
using Seconds = std::chrono::duration<int32_t>;
using Minutes = std::chrono::duration<int32_t, std::ratio<60>>;
using Hours = std::chrono::duration<int32_t, std::ratio<3600>>;

}
