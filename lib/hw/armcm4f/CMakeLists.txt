
project(armcm4f C CXX ASM)

estp_add_static_library(
    NAME
        startup-armcm4f
    ARCH
        armcm4f
    SOURCES
    	startup_ARMCM4.S
)

