CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(ESTP_PLATFORM nrf52_pca10040)
set(ESTP_OPT speed)

include("estoppel/cmake/estp_app.cmake")

project(LedSoftBlink)

set(NRF5_SDK_ROOT "${ESTP_ROOT}/third_party/nordic/nrf5_sdk/latest")
set(EXAMPLE_ROOT "${NRF5_SDK_ROOT}/examples/peripheral/led_softblink")
set(EXAMPLE_CONFIG_ROOT "${EXAMPLE_ROOT}/pca10040/blank/config")

target_compile_definitions(estp_build INTERFACE
    "APP_TIMER_V2_RTC1_ENABLED"
    "CONFIG_GPIO_AS_PINRESET"
    "__HEAP_SIZE=8192"
    "__STACK_SIZE=8192"
)

target_include_directories(estp_build INTERFACE
    ${EXAMPLE_ROOT}
    ${EXAMPLE_CONFIG_ROOT}
)

target_link_libraries(estp_link INTERFACE
    "-Tnrf52832_xxaa_nosd.ld"
)

add_estp_executable(led_softblink
    ${EXAMPLE_ROOT}/main.c
)

target_link_options(led_softblink PRIVATE
    --specs=nano.specs       # use minimal newlib config
    --specs=nosys.specs      # use empty syscalls
)

target_link_libraries(led_softblink PRIVATE
    nordic_sdk_warnings_hack
)
