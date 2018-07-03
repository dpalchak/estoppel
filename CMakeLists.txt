cmake_minimum_required(VERSION 3.9)

set(ESTOPPEL_ROOT ${CMAKE_SOURCE_DIR})

if(NOT DEFINED DEVICE)
	set(DEVICE "host")
	message(WARNING "Setting device to `host`")
endif()

set(DEVICE_CONFIG_FILE "${ESTOPPEL_ROOT}/cmake/device/${DEVICE}.cmake")
if(NOT EXISTS "${DEVICE_CONFIG_FILE}")
	message(FATAL_ERROR "Unknown device: ${DEVICE}")
endif()

# Top-level project
project("Estoppel" C CXX)

# Common includes
include("${ESTOPPEL_ROOT}/cmake/estp_util.cmake")
include("${ESTOPPEL_ROOT}/cmake/common_flags.cmake")
include("${ESTOPPEL_ROOT}/cmake/embedded_targets.cmake")
#include("${ESTOPPEL_ROOT}/cmake/host_targets.cmake")
include("${ESTOPPEL_ROOT}/cmake/pylink.cmake")

# Device-specific configuration
include("${DEVICE_CONFIG_FILE}")

message(STATUS "Device: ${DEVICE}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_subdirectory(third_party)
add_subdirectory(lib)
add_subdirectory(app)
