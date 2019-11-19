

set(NRF5_SDK_ROOT "${ESTP_ROOT}/third_party/nordic/nrf5_sdk/latest")

add_library(nordic_sdk_warnings_hack INTERFACE)

target_compile_options(nordic_sdk_warnings_hack INTERFACE
    "-Wno-conversion"
    "-Wno-undef"
    "-Wno-sign-conversion"
    "-Wno-expansion-to-defined"
    "-Wno-unused-parameter"
    "-Wno-switch-default"
    $<$<COMPILE_LANGUAGE:C>:-Wno-discarded-qualifiers>
)

add_estp_platform_libraries(nrf52)

target_link_libraries(nrf52_platform_link INTERFACE
    "-L${NRF5_SDK_ROOT}/modules/nrfx/mdk"
)

target_include_directories(nrf52_platform_build INTERFACE
    ${NRF5_SDK_ROOT}/components
    ${NRF5_SDK_ROOT}/components/boards
    ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
    ${NRF5_SDK_ROOT}/components/libraries/atomic_fifo
    ${NRF5_SDK_ROOT}/components/libraries/atomic
    ${NRF5_SDK_ROOT}/components/libraries/balloc
    ${NRF5_SDK_ROOT}/components/libraries/bsp
    ${NRF5_SDK_ROOT}/components/libraries/delay
    ${NRF5_SDK_ROOT}/components/libraries/experimental_section_vars
    ${NRF5_SDK_ROOT}/components/libraries/led_softblink
    ${NRF5_SDK_ROOT}/components/libraries/log
    ${NRF5_SDK_ROOT}/components/libraries/log/src
    ${NRF5_SDK_ROOT}/components/libraries/low_power_pwm
    ${NRF5_SDK_ROOT}/components/libraries/memobj
    ${NRF5_SDK_ROOT}/components/libraries/ringbuf
    ${NRF5_SDK_ROOT}/components/libraries/scheduler
    ${NRF5_SDK_ROOT}/components/libraries/sortlist
    ${NRF5_SDK_ROOT}/components/libraries/strerror
    ${NRF5_SDK_ROOT}/components/libraries/timer
    ${NRF5_SDK_ROOT}/components/libraries/util
    ${NRF5_SDK_ROOT}/components/toolchain/cmsis/include
    ${NRF5_SDK_ROOT}/external/fprintf
    ${NRF5_SDK_ROOT}/integration/nrfx
    ${NRF5_SDK_ROOT}/integration/nrfx/legacy
    ${NRF5_SDK_ROOT}/modules/nrfx
    ${NRF5_SDK_ROOT}/modules/nrfx/hal
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/include
)

target_compile_definitions(nrf52_platform_build INTERFACE
    "FLOAT_ABI_HARD"
    "NRF52"
    "NRF52832_XXAA"
    "NRF52_PAN_74"
    "APP_TIMER_V2"
    "BSP_DEFINES_ONLY"
)

target_compile_options(nrf52_platform_build INTERFACE
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

target_link_options(nrf52_platform_build INTERFACE
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

# TODO(palchak): fix this shit by creating real libraries for NRF5 SDK
target_sources(nrf52_platform_sources PRIVATE
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52.S
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk/system_nrf52.c
    ${NRF5_SDK_ROOT}/modules/nrfx/soc/nrfx_atomic.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_clock.c
    ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c
    ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_str_formatter.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_error.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_error_handler_gcc.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_error_weak.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_util_platform.c
    ${NRF5_SDK_ROOT}/components/libraries/util/nrf_assert.c
    ${NRF5_SDK_ROOT}/components/libraries/scheduler/app_scheduler.c
    ${NRF5_SDK_ROOT}/components/libraries/timer/app_timer2.c
    ${NRF5_SDK_ROOT}/components/libraries/timer/drv_rtc.c
    ${NRF5_SDK_ROOT}/components/libraries/led_softblink/led_softblink.c
    ${NRF5_SDK_ROOT}/components/libraries/low_power_pwm/low_power_pwm.c
    ${NRF5_SDK_ROOT}/components/libraries/atomic_fifo/nrf_atfifo.c
    ${NRF5_SDK_ROOT}/components/libraries/atomic/nrf_atomic.c
    ${NRF5_SDK_ROOT}/components/libraries/balloc/nrf_balloc.c
    ${NRF5_SDK_ROOT}/components/libraries/memobj/nrf_memobj.c
    ${NRF5_SDK_ROOT}/components/libraries/ringbuf/nrf_ringbuf.c
    ${NRF5_SDK_ROOT}/components/libraries/sortlist/nrf_sortlist.c
    ${NRF5_SDK_ROOT}/components/libraries/strerror/nrf_strerror.c
    ${NRF5_SDK_ROOT}/integration/nrfx/legacy/nrf_drv_clock.c
    ${NRF5_SDK_ROOT}/external/fprintf/nrf_fprintf.c
    ${NRF5_SDK_ROOT}/external/fprintf/nrf_fprintf_format.c
)

target_link_libraries(nrf52_platform_sources PRIVATE
    nordic_sdk_warnings_hack
)

add_estp_platform_libraries(nrf52_pca10040 EXTENDS nrf52)

target_compile_definitions(nrf52_pca10040_platform_build INTERFACE
    "BOARD_PCA10040"
)

target_sources(nrf52_pca10040_platform_sources PRIVATE
    ${NRF5_SDK_ROOT}/components/boards/boards.c
)

target_link_libraries(nrf52_pca10040_platform_sources PRIVATE
    nordic_sdk_warnings_hack
)