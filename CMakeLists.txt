cmake_minimum_required(VERSION 3.9)
include(CMakePrintHelpers)

set(ESTOPPEL_ROOT ${CMAKE_SOURCE_DIR})

if(NOT DEFINED ARCH)
    set(ARCH "HOST")
endif()
string(TOUPPER ${ARCH} ARCH)

# Ensure that ARCH is a valid value
set(EMBEDDED_ARCHS "ARM_CM4F;ARM_CM3;ARM_CM0")
set(HOST_ARCHS "HOST;HOST64;HOST32")

if(${ARCH} IN_LIST EMBEDDED_ARCHS)
    set(ARCH_TYPE "EMBEDDED")
    set(ARCH_TYPE_EMBEDDED ON)
    set(ARCH_TYPE_HOST OFF)
    set(DEFAULT_BUILD_TYPE "Debug")

	if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
		set(CMAKE_TOOLCHAIN_FILE
			"${ESTOPPEL_ROOT}/cmake/toolchain-arm-gcc.cmake"
			CACHE STRING "Toolchain for embedded targets"
		)
	endif()

elseif(${ARCH} IN_LIST HOST_ARCHS)
    set(ARCH_TYPE "HOST")
    set(ARCH_TYPE_EMBEDDED OFF)
    set(ARCH_TYPE_HOST ON)
    set(DEFAULT_BUILD_TYPE "Release")

else() # unknown ARCH
    message(FATAL_ERROR
        "Unknown target architecture: ${ARCH}\n"
        "Valid options are: ${EMBEDDED_ARCHS};${HOST_ARCHS}\n"
    )
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE} CACHE STRING "build type" FORCE)
endif()

# Top-level project
project("Estoppel")

# Common includes
include("${ESTOPPEL_ROOT}/cmake/utility.cmake")
include("${ESTOPPEL_ROOT}/cmake/compile_flags.cmake")
include("${ESTOPPEL_ROOT}/cmake/embedded_targets.cmake")

message(STATUS "Architecture: ${ARCH}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(third_party)
add_subdirectory(lib)
add_subdirectory(app)
