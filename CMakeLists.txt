cmake_minimum_required(VERSION 3.10)
include(CMakePrintHelpers)

if(NOT DEFINED ESTP_ROOT)
    include("cmake/Estoppel.cmake")
endif()

# Top-level project
project("Estoppel")

# Add all of the build libraries supported by the toolchain we're using
# The build libraries set the necessary compiler and linker flags for every target
# All Estoppel targets depend on one or more build libraries
set(ESTP_ARM_ARCHS arm armcm4f armcm4 armcm3 armcm0p)
set(ESTP_HOST_ARCHS host host32)
set(ESTP_ARCHS ${ESTP_ARM_ARCHS} ${ESTP_HOST_ARCHS})

if(ESTP_ARCH MATCHES "arm")
    if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU")
        message(FATAL_ERROR "Unsupported compiler for ARM architecture: ${CMAKE_C_COMPILER_ID}")
    endif()

    # Generic arm build target
    estp_add_build_library(arm)

    # Architecture specific arm targets
    foreach(ARCH armcm4f armcm4 armcm3 armcm0p)
        estp_add_build_library(${ARCH} arm)
    endforeach()

elseif(ESTP_ARCH MATCHES "host")
    if(NOT ${CMAKE_C_COMPILER_ID} MATCHES "GNU|Clang")
        message(FATAL_ERROR "Unsupported compiler for host architecture: ${CMAKE_C_COMPILER_ID}")
    endif()

    estp_add_build_library(host)
    estp_add_build_library(host32 host)

    include(CTest)
    include("${ESTP_ROOT}/third_party/catch2/upstream/contrib/Catch.cmake")
    enable_testing()

else()
    message(FATAL_ERROR "Unknown architecture: ${ESTP_ARCH}")

endif()

add_subdirectory(third_party)
add_subdirectory(lib)
