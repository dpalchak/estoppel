cmake_minimum_required(VERSION 3.13)
include(CMakePrintHelpers)

set(ESTP_ROOT ${CMAKE_CURRENT_LIST_DIR})

# Don't use CMake's build type control
unset(CMAKE_BUILD_TYPE)

# Global project includes
include("cmake/EstoppelTargets.cmake")
include("cmake/EstoppelFlags.cmake")
include("third_party/catch2/upstream/contrib/Catch.cmake")

# Top-level project
project("Estoppel")

# Add all of the flags libraries supported by the toolchain we're using
# The flags libraries set the necessary compiler and linker flags for every target
# All Estoppel targets depend on one or more flags libraries
set(ESTP_ARM_ARCHS armcm4f armcm4 armcm3 armcm0p)
set(ESTP_HOST_ARCHS x86 x86_64)
set(ESTP_ARCHS ${ESTP_ARM_ARCHS} ${ESTP_HOST_ARCHS})

if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU")
        message(FATAL_ERROR "Unsupported compiler for ARM architecture: ${CMAKE_C_COMPILER_ID}")
    endif()

    # Generic arm build target
    estp_add_flags_library(arm)

    # Architecture specific arm targets
    foreach(ARCH armcm4f armcm4 armcm3 armcm0p)
        estp_add_flags_library(${ARCH} arm)
    endforeach()

elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "x86")
    if(NOT ${CMAKE_C_COMPILER_ID} MATCHES "GNU|Clang")
    message(FATAL_ERROR "Unsupported compiler for ${CMAKE_SYSTEM_PROCESSOR} architecture: ${CMAKE_C_COMPILER_ID}")
    endif()

    estp_add_flags_library(x86_64)
    estp_add_flags_library(x86 x86_64)

else()
    message(FATAL_ERROR "Unsupported processor: ${CMAKE_SYSTEM_PROCESSOR}")

endif()

add_subdirectory(third_party)
add_subdirectory(lib)
