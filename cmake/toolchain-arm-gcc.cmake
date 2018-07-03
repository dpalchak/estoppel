# A CMake toolchain file for cross-compiling for arm-none-eabi targets
# Require CMake >= 3.10 in order to support C++17 standard
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# The Generic system name is used for embedded targets (targets without OS) in Cmake
set(CMAKE_SYSTEM_NAME          Generic)

# Enforce minimum language standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXECUTABLE_SUFFIX_C ".elf")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXECUTABLE_SUFFIX_CPP ".elf")

# Set a toolchain path. You only need to set this if the toolchain isn't in
# your system path
string(TOLOWER "${CMAKE_HOST_SYSTEM_NAME}" HOST_SYSTEM_NAME)
set(TOOLCHAIN_PATH "${ESTOPPEL_ROOT}/third_party/gcc/${HOST_SYSTEM_NAME}/latest/bin")

# Tell CMake to try building static libraries instead of executables to explore compiler
set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

# Set standard compiler commands
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/arm-none-eabi-as")

# Just use GCC for assembly, it does the Right Thing
set(CMAKE_ASM_COMPILE_OBJECT "<CMAKE_C_COMPILER> <FLAGS> <DEFINES> -o <OBJECT> -c <SOURCE>")

# Set other build commands
# AR and RANLIB have to be cached because CMake is broken and doesn't cross-compile 
# correctly otherwise
set(CMAKE_AR "${TOOLCHAIN_PATH}/arm-none-eabi-ar" CACHE FILEPATH "")
set(CMAKE_RANLIB "${TOOLCHAIN_PATH}/arm-none-eabi-ranlib" CACHE FILEPATH "")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/arm-none-eabi-objcopy")
set(CMAKE_OBJDUMP "${TOOLCHAIN_PATH}/arm-none-eabi-objdump")
set(CMAKE_SIZEINFO "${TOOLCHAIN_PATH}/arm-none-eabi-size")

# Only look for libraries and include files in the toolchain path
set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Never look for tools or programs
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
