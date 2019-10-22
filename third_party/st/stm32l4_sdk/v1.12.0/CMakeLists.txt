
project(libstm32l4sdk C CXX ASM)

estp_add_interface_library(
    NAME
        stm32l4sdk_cmsis
    ARCH
        armcm4f
    INCLUDE_DIRS
        "Drivers/CMSIS/Include"
        "Drivers/CMSIS/Device/ST/STM32L4xx/Include"
)

# Interface library target for CMSIS DSP library targeting hard FPU devices
estp_add_interface_library(
    NAME
        stm32l4sdk_dsp
    ARCH
        armcm4f
    LIBRARIES
        stm32l4sdk_cmsis
        "Drivers/CMSIS/Lib/GCC/libarm_cortexM4lf_math.a"
    DEFINES
        "__FPU_USED=1"
        "__FPU_PRESENT=1"
)

# Static library for SDK HAL
# TODO(palchak): replace file glob with harcoded list
file(GLOB STM32L4_SDK_HAL_SRCS "Drivers/STM32L4xx_HAL_Driver/Src/*.c")


# We have to put these flags into an interface library in order to control
# their order on the command line. Interface CFLAGS appear *after* the
# target-specific CFLAGS. Since we're turning off warnings that are explicitly
# turned on by the Estoppel build library, we need these flags to appear at
# the end of the command line. Hence the "_hack" suffix.
estp_add_interface_library(
    NAME
        stm32l4sdk_hal_warnings_hack
    CFLAGS
        # The SDK code has relies on some questionable constructs...
        "-Wno-conversion"
        "-Wno-sign-conversion"
        "-Wno-switch-enum"
        "-Wno-unused-parameter"
        "-Wno-attributes"
)

estp_add_static_library(
    NAME
        stm32l4sdk_hal-stm32l486
    ARCH
        armcm4f
    SOURCES
        ${STM32L4_SDK_HAL_SRCS}
    DEFINES PRIVATE
        "USE_HAL_DRIVER"
    INCLUDE_DIRS PUBLIC
        "Drivers/STM32L4xx_HAL_Driver/Inc"
    LIBRARIES
        PUBLIC
        # Depend on a library defined elsewhere that provides the configuration
        stm32l4sdk_config-stm32l486
        stm32l4sdk_cmsis
        PRIVATE
        stm32l4sdk_hal_warnings_hack
)
