
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

add_estp_platform_libraries(stm32l4x6xg EXTENDS armcm4f)

target_sources(stm32l4x6xg_platform_sources PRIVATE stm32l4xx_vector_table.cc)

target_link_libraries(stm32l4x6xg_platform_link INTERFACE
    "-L${CMAKE_CURRENT_SOURCE_DIR}"
    "-T${CMAKE_CURRENT_BINARY_DIR}/stm32l4x6.ld"
)

add_dependencies(stm32l4x6xg_platform_link gen_stm32l4x6_link_script)

target_link_libraries(stm32l4x6xg_platform_build INTERFACE
    stm32l4sdk_hal-stm32l486
)


add_estp_library(stm32l4sdk_config-stm32l486 INTERFACE)

target_sources(stm32l4sdk_config-stm32l486 INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/stm32l4xx_hal_conf.h"
)

target_include_directories(stm32l4sdk_config-stm32l486 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(stm32l4sdk_config-stm32l486 INTERFACE
    "STM32L486xx=1"
)
