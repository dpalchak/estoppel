cmake_minimum_required(VERSION 3.9)
include(CMakePrintHelpers)

set(ESTOPPEL_ROOT ${CMAKE_SOURCE_DIR})

# Ensure that BUILD_ENV is a valid value
set(BUILD_ENV_VALUES "firmware;firmware_tests;host;host_tests")
if(NOT DEFINED BUILD_ENV)
	message(FATAL_ERROR 
		"BUILD_ENV must be defined\n"
		"Valid options are ${BUILD_ENV_VALUES}\n"
	)
endif()
if(NOT ${BUILD_ENV} IN_LIST BUILD_ENV_VALUES)
	message(FATAL_ERROR 
		"Unknown BUILD_ENV: ${BUILD_ENV}\n"
		"Valid options are: ${BUILD_ENV_VALUES}\n"
	)
endif()

if(${BUILD_ENV} STREQUAL "firmware")
	if(NOT CMAKE_BUILD_TYPE)
	  set(CMAKE_BUILD_TYPE "Debug")
	endif()
	
	if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
		set(CMAKE_TOOLCHAIN_FILE
			"${ESTOPPEL_ROOT}/cmake/toolchain-arm-gcc.cmake"
			CACHE STRING "Toolchain for firmware targets"
		)
	endif()
	
	if(NOT DEFINED TARGET_DEVICE)
		message(FATAL_ERROR "Firmware builds must define a TARGET_DEVICE")
	endif()
else()
	if(NOT CMAKE_BUILD_TYPE)
	  set(CMAKE_BUILD_TYPE "Release")
	endif()
	set(TARGET_DEVICE "host")
endif()


# Place executables in //out/{debug,release,...} 
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE_DIRNAME)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ESTOPPEL_ROOT}/out/${BUILD_TYPE_DIRNAME}")

# Top-level project
project("Estoppel" C CXX)

# Common includes
include("${ESTOPPEL_ROOT}/cmake/utility.cmake")
include("${ESTOPPEL_ROOT}/cmake/compile_flags.cmake")
include("${ESTOPPEL_ROOT}/cmake/firmware.cmake")

# Device-specific configuration
set(DEVICE_CONFIG_FILE "${ESTOPPEL_ROOT}/cmake/device/${TARGET_DEVICE}.cmake")
if(NOT EXISTS "${DEVICE_CONFIG_FILE}")
	message(FATAL_ERROR "Unknown target device: ${TARGET_DEVICE}")
endif()
include("${DEVICE_CONFIG_FILE}")

message(STATUS "Environment: ${BUILD_ENV}")
message(STATUS "Device: ${TARGET_DEVICE}")
message(STATUS "Type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(third_party)
add_subdirectory(lib)
add_subdirectory(app)
