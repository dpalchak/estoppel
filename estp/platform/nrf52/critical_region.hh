#pragma once

#include "app_util_platform.h"

namespace estp {

class Nrf52CriticalRegion {
public:
    Nrf52CriticalRegion() {
        app_util_critical_region_enter(nullptr);
    }

    ~Nrf52CriticalRegion() {
        app_util_critical_region_exit(0);
    }
};

}
