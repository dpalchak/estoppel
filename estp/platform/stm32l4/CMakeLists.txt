
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

# estp_add_static_library(
#     NAME
#         stm32l4x6xg
#     ARCH
#         armcm4f
#     SOURCES
#         stm32l4xx_vector_table.cc
#     LIBRARIES
#         PUBLIC
#             armcm4f
#         INTERFACE
#             # The order of the scripts here is important
#             "-T${CMAKE_CURRENT_SOURCE_DIR}/stm32l4x6xg_memory.ld"
#             "-T${CMAKE_CURRENT_BINARY_DIR}/stm32l4x6.ld"
#     DEPENDENCIES
#         gen_stm32l4x6_link_script
# )
add_estp_platform_libraries(stm32l4x6xg EXTENDS armcm4f)

target_sources(stm32l4x6xg_platform_sources PRIVATE stm32l4xx_vector_table.cc)

target_link_libraries(stm32l4x6xg_platform_link INTERFACE
    # The order of the scripts here is important, which is why we use
    # target_link_libraries() instead of target_link_options()
    "-T${CMAKE_CURRENT_SOURCE_DIR}/stm32l4x6xg_memory.ld"
    "-T${CMAKE_CURRENT_BINARY_DIR}/stm32l4x6.ld"
)

add_dependencies(stm32l4x6xg_platform_link gen_stm32l4x6_link_script)

target_link_libraries(stm32l4x6xg_platform_build INTERFACE
    stm32l4sdk_hal-stm32l486
)

# Configuration library for STM32L4 SDK
# estp_add_interface_library(
#     NAME
#         stm32l4sdk_config-stm32l486
#     ARCH
#         armcm4f
#     SOURCES
#         "${CMAKE_CURRENT_SOURCE_DIR}/stm32l4xx_hal_conf.h"
#     INCLUDE_DIRS
#         ${CMAKE_CURRENT_SOURCE_DIR}
#     DEFINES
#         "STM32L486xx=1"
# )
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
