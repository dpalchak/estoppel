


function(get_nrf5_sdk_root VAR_NAME)
    set("${VAR_NAME}" "${ESTP_ROOT}/third_party/nordic/nrf5_sdk/latest" PARENT_SCOPE)
endfunction()

get_nrf5_sdk_root(NRF5_SDK_ROOT)
message(STATUS "Using NRF5 SDK: '${NRF5_SDK_ROOT}'")

add_library(nrf5_sdk_warnings_hack INTERFACE)

target_compile_options(nrf5_sdk_warnings_hack INTERFACE
    "-Wno-conversion"
    "-Wno-undef"
    "-Wno-sign-conversion"
    "-Wno-expansion-to-defined"
    "-Wno-unused-parameter"
    "-Wno-switch-default"
    "-Wno-switch-enum"
    "-Wno-missing-field-initializers"
    $<$<COMPILE_LANGUAGE:C>:-Wno-discarded-qualifiers>
)

add_estp_platform_libraries(nrf52832_xxaa)

target_link_libraries(nrf52832_xxaa_platform_link INTERFACE
    "-L${CMAKE_CURRENT_LIST_DIR}"
)

target_include_directories(nrf52832_xxaa_platform_build INTERFACE
    ${NRF5_SDK_ROOT}/components
    ${NRF5_SDK_ROOT}/components/boards
    ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
    ${NRF5_SDK_ROOT}/components/libraries/atomic
    ${NRF5_SDK_ROOT}/components/libraries/atomic_fifo
    ${NRF5_SDK_ROOT}/components/libraries/balloc
    ${NRF5_SDK_ROOT}/components/libraries/bsp
    ${NRF5_SDK_ROOT}/components/libraries/button
    ${NRF5_SDK_ROOT}/components/libraries/delay
    ${NRF5_SDK_ROOT}/components/libraries/experimental_section_vars
    ${NRF5_SDK_ROOT}/components/libraries/led_softblink
    ${NRF5_SDK_ROOT}/components/libraries/log
    ${NRF5_SDK_ROOT}/components/libraries/log/src
    ${NRF5_SDK_ROOT}/components/libraries/low_power_pwm
    ${NRF5_SDK_ROOT}/components/libraries/memobj
    ${NRF5_SDK_ROOT}/components/libraries/mutex
    ${NRF5_SDK_ROOT}/components/libraries/pwr_mgmt
    ${NRF5_SDK_ROOT}/components/libraries/ringbuf
    ${NRF5_SDK_ROOT}/components/libraries/scheduler
    ${NRF5_SDK_ROOT}/components/libraries/sortlist
    ${NRF5_SDK_ROOT}/components/libraries/strerror
    ${NRF5_SDK_ROOT}/components/libraries/timer
    ${NRF5_SDK_ROOT}/components/libraries/util
    ${NRF5_SDK_ROOT}/components/toolchain/cmsis/include
    ${NRF5_SDK_ROOT}/external/fprintf
    ${NRF5_SDK_ROOT}/external/segger_rtt
    ${NRF5_SDK_ROOT}/integration/nrfx
    ${NRF5_SDK_ROOT}/integration/nrfx/legacy
    ${NRF5_SDK_ROOT}/modules/nrfx
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/include
    ${NRF5_SDK_ROOT}/modules/nrfx/hal
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk
)

target_compile_definitions(nrf52832_xxaa_platform_build INTERFACE
    "FLOAT_ABI_HARD"
    "NRF52"
    "NRF52832_XXAA"
    "NRF52_PAN_74"
    "APP_TIMER_V2"
)

target_compile_options(nrf52832_xxaa_platform_build INTERFACE
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

target_link_options(nrf52832_xxaa_platform_build INTERFACE
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

target_sources(nrf52832_xxaa_platform_sources PRIVATE
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52.S
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk/system_nrf52.c
)

target_link_libraries(nrf52832_xxaa_platform_sources PRIVATE
    nrf5_sdk_warnings_hack
)

add_estp_platform_libraries(nrf52_pca10040 EXTENDS nrf52832_xxaa)

target_compile_definitions(nrf52_pca10040_platform_build INTERFACE
    "BOARD_PCA10040"
)

target_sources(nrf52_pca10040_platform_sources PRIVATE
    ${NRF5_SDK_ROOT}/components/boards/boards.c
)

target_link_libraries(nrf52_pca10040_platform_sources PRIVATE
    nrf5_sdk_warnings_hack
)

set_estp_platform_jlink_config(nrf52_pca10040 NRF52832_XXAA SWD 4000)
