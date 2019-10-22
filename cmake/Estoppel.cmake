cmake_minimum_required(VERSION 3.10)

get_filename_component(ESTP_ROOT ${CMAKE_CURRENT_LIST_DIR} DIRECTORY)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

if(NOT DEFINED ESTP_ARCH)
    message(FATAL_ERROR "ESTP_ARCH not defined")
endif()
string(TOLOWER ${ESTP_ARCH} ESTP_ARCH)

if(ESTP_ARCH MATCHES "arm")
	set(CMAKE_TOOLCHAIN_FILE ToolchainGccArmEmbedded)
endif()

# Don't use CMake's build type control
unset(CMAKE_BUILD_TYPE)

# Global project includes
include(EstoppelTools)
include(EstoppelBuild)
