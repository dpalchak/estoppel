cmake_minimum_required(VERSION 3.9)

if(NOT ${ARCH} STREQUAL "ARM_CM4F")
    return()
endif()

project(stm32l4_sdk C CXX ASM)

# Simple interface library for CMSIS includes (including device-specific)
add_library(stm32l4_sdk_cmsis INTERFACE)
target_include_directories(stm32l4_sdk_cmsis INTERFACE
    "Drivers/CMSIS/Include"
    "Drivers/CMSIS/Device/ST/STM32L4xx/Include"
)

# Static library target for CMSIS DSP library targeting hard FPU devices
add_library(stm32l4_sdk_dsp_m4f INTERFACE)
target_link_libraries(stm32l4_sdk_dsp_m4f INTERFACE
    stm32l4_sdk_cmsis
    "Drivers/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a"
)
target_compile_definitions(stm32l4_sdk_dsp_m4f INTERFACE
    "__FPU_USED=1"
    "__FPU_PRESENT=1"
)

# Static library for SDK HAL
file(GLOB STM32L4_SDK_HAL_SRCS "Drivers/STM32L4xx_HAL_Driver/Src/*.c")

add_library(stm32l4_sdk_hal STATIC 
    ${STM32L4_SDK_HAL_SRCS}
)

# The SDK code has relies on some questionable constructs...
target_compile_options(stm32l4_sdk_hal PRIVATE
    "-Wno-conversion"
    "-Wno-sign-conversion"
    "-Wno-switch-enum"
    "-Wno-unused-parameter"
)

target_compile_definitions(stm32l4_sdk_hal PRIVATE 
    "USE_HAL_DRIVER"
)

target_include_directories(stm32l4_sdk_hal PUBLIC
    "Drivers/STM32L4xx_HAL_Driver/Inc"
)

# Depend on a library defined elsewhere that provides the configuration
target_link_libraries(stm32l4_sdk_hal PUBLIC
    config_stm32l4_sdk_hal
    stm32l4_sdk_cmsis
)
