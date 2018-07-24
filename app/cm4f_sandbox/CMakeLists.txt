
project(cm4f_sandbox C CXX ASM)

estp_add_firmware_executable(
    NAME
        cm4f_sandbox.elf
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
