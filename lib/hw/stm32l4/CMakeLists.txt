
project(libstm32l4 C CXX ASM)

# TODO(palchak): wrap this in a function that provides a means to
# configure link script options

# Use the C preprocessor to generate a linker script
add_custom_command(
    OUTPUT "stm32l4x6.ld"
    COMMAND ${CMAKE_CPP} -P -CC "${CMAKE_CURRENT_SOURCE_DIR}/stm32l4xx.ld.in" -o "stm32l4x6.ld"
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/stm32l4xx.ld.in"
    COMMENT "Generating STM32L4x6 linker script"
    VERBATIM
)

# Create a custom target that generates a linker script
add_custom_target(gen_stm32l4x6_link_script DEPENDS "stm32l4x6.ld")

estp_add_static_library(
    NAME
        stm32l4x6xg
    ARCH
        armcm4f
    SOURCES
        stm32l4xx_vector_table.cc
    LIBRARIES INTERFACE
        armcm4f
        # The order of the scripts here is important
        "-T${CMAKE_CURRENT_SOURCE_DIR}/stm32l4x6xg_memory.ld"
        "-T${CMAKE_CURRENT_BINARY_DIR}/stm32l4x6.ld"
    DEPENDENCIES
        gen_stm32l4x6_link_script
)

# Configuration library for STM32L4 SDK
estp_add_interface_library(
    NAME
        stm32l4sdk_config-stm32l486
    ARCH
        armcm4f
    SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/stm32l4xx_hal_conf.h"
    INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
    DEFINES
        "STM32L486xx=1"
)

