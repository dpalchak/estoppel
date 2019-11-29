CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(ESTP_PLATFORM nrf52_pca10040)
set(ESTP_OPT speed)

include("estoppel/cmake/estp_app.cmake")

project(SpiMaster)

get_nrf5_sdk_root(NRF5_SDK_ROOT)
set(EXAMPLE_ROOT "${NRF5_SDK_ROOT}/examples/peripheral/spi")
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

add_estp_executable(spi_master
    main.c
    ${NRF5_SDK_ROOT}/components/boards/boards.c
    # ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_nvic.c
    ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd/nrf_soc.c
    ${NRF5_SDK_ROOT}/components/libraries/atomic_fifo/nrf_atfifo.c
    ${NRF5_SDK_ROOT}/components/libraries/atomic/nrf_atomic.c
    ${NRF5_SDK_ROOT}/components/libraries/balloc/nrf_balloc.c
    ${NRF5_SDK_ROOT}/components/libraries/bsp/bsp.c
    ${NRF5_SDK_ROOT}/components/libraries/button/app_button.c
    # ${NRF5_SDK_ROOT}/components/libraries/led_softblink/led_softblink.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_backend_rtt.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_backend_serial.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_backend_uart.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_default_backends.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_frontend.c
    ${NRF5_SDK_ROOT}/components/libraries/log/src/nrf_log_str_formatter.c
    # ${NRF5_SDK_ROOT}/components/libraries/low_power_pwm/low_power_pwm.c
    ${NRF5_SDK_ROOT}/components/libraries/memobj/nrf_memobj.c
    ${NRF5_SDK_ROOT}/components/libraries/ringbuf/nrf_ringbuf.c
    ${NRF5_SDK_ROOT}/components/libraries/scheduler/app_scheduler.c
    ${NRF5_SDK_ROOT}/components/libraries/sortlist/nrf_sortlist.c
    ${NRF5_SDK_ROOT}/components/libraries/strerror/nrf_strerror.c
    ${NRF5_SDK_ROOT}/components/libraries/timer/app_timer2.c
    ${NRF5_SDK_ROOT}/components/libraries/timer/drv_rtc.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_error_handler_gcc.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_error_weak.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_error.c
    ${NRF5_SDK_ROOT}/components/libraries/util/app_util_platform.c
    ${NRF5_SDK_ROOT}/components/libraries/util/nrf_assert.c
    ${NRF5_SDK_ROOT}/external/fprintf/nrf_fprintf_format.c
    ${NRF5_SDK_ROOT}/external/fprintf/nrf_fprintf.c
    ${NRF5_SDK_ROOT}/external/segger_rtt/SEGGER_RTT_printf.c
    ${NRF5_SDK_ROOT}/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c
    ${NRF5_SDK_ROOT}/external/segger_rtt/SEGGER_RTT.c
    # ${NRF5_SDK_ROOT}/integration/nrfx/legacy/nrf_drv_clock.c
    ${NRF5_SDK_ROOT}/integration/nrfx/legacy/nrf_drv_spi.c
    ${NRF5_SDK_ROOT}/integration/nrfx/legacy/nrf_drv_uart.c
    # ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_clock.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_gpiote.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_spi.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_spim.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uart.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/nrfx_uarte.c
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/src/prs/nrfx_prs.c
    # ${NRF5_SDK_ROOT}/modules/nrfx/soc/nrfx_atomic.c
)

target_link_options(spi_master PRIVATE
    --specs=nano.specs       # use minimal newlib config
    --specs=nosys.specs      # use empty syscalls
)

target_link_libraries(spi_master PRIVATE
    nrf5_sdk_warnings_hack
    "-Tnrf52832_xxaa_nosd.ld"   # use SDK provided linker script
)

add_estp_jlink_targets(spi_master)
