CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
include_guard()

get_filename_component(ESTP_ROOT "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
message(STATUS "Found Estoppel at ${ESTP_ROOT}")

if(NOT ESTP_PLATFORM)
    message(FATAL_ERROR "ESTP_PLATFORM not defined!")
endif()
string(TOLOWER ${ESTP_PLATFORM} ESTP_PLATFORM)
message(STATUS "Building for platform ${ESTP_PLATFORM}")

# Shortcut variables for commonly used conditionals
if(ESTP_PLATFORM MATCHES "host")
    set(ESTP_HOST_PLATFORM ON)
    set(ESTP_DEVICE_PLATFORM OFF)
else()
    set(ESTP_HOST_PLATFORM OFF)
    set(ESTP_DEVICE_PLATFORM ON)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(ESTP_DEVICE_PLATFORM AND (NOT CMAKE_TOOLCHAIN_FILE))
    set(CMAKE_TOOLCHAIN_FILE "${ESTP_ROOT}/third_party/gcc-arm-none-eabi/gcc-arm-none-eabi.cmake")
endif()

# Don't use CMake's built-in build types
unset(CMAKE_BUILD_TYPE)

# Prefer instead to select optimization through a normal variable
set(_ESTP_VALID_OPT_VALUES none debug size speed)
if(NOT ESTP_OPT)
    set(ESTP_OPT debug)
endif()

set(ESTP_OPT ${ESTP_OPT} CACHE STRING "Optimization level")

if(NOT ESTP_OPT IN_LIST _ESTP_VALID_OPT_VALUES)
    message(FATAL_ERROR "Invalid ESTP_OPT optimization setting: '${ESTP_OPT}'")
    message(STATUS "Valid values are ${_ESTP_VALID_OPT_VALUES}")
else()
    message(STATUS "Optimizing for '${ESTP_OPT}'")
endif()


project(EstoppelApp LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${ESTP_ROOT}/cmake")

include(estp_build_flags)
include(estp_internal)
include(estp_core)
include(estp_jlink)

# Add customization libraries at the top-level so they can be modified by any
# subdirectory, including user-provided ones
_add_estp_customization_libraries()

if(ESTP_DEVICE_PLATFORM)
    enable_language(ASM)
    set(CMAKE_EXECUTABLE_SUFFIX .elf)
    if(ESTP_BUILD_TESTING)
        message(STATUS "Unit testing not supported on target platform. Disabling.")
        set(ESTP_BUILD_TESTING OFF)
    endif()
endif()

if(ESTP_BUILD_TESTING)
    include(CTest)
    enable_testing()
    include("${ESTP_ROOT}/third_party/catch2/contrib/Catch.cmake")
    message(STATUS "Testing enabled")
endif()

# Add Estoppel directory for processing
add_subdirectory("${ESTP_ROOT}" estoppel EXCLUDE_FROM_ALL)

