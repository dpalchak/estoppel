CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(ESTP_ARCH "arm")
include("estoppel/cmake/Estoppel.cmake")

project(hello_world C CXX ASM)

add_subdirectory(estoppel)

estp_add_firmware_executable(
    NAME
        hello_world.elf
    ARCH
        armcm4f
    SOURCES
    	main.cc
	LIBRARIES PRIVATE
        stm32l4sdk_hal-stm32l486
        stm32l4x6xg
    LDFLAGS PRIVATE
        --specs=nano.specs       # use minimal newlib config
        --specs=nosys.specs      # use empty syscalls
)
