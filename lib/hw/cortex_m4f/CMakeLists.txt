
if(NOT ${ARCH} STREQUAL "ARM_CM4F")
    return()
endif()

project(cm4f_startup C CXX ASM)

estp_add_static_library(
    NAME
        libstartup-armcm4f
    ARCH
        armcm4f
    SOURCES
    	startup_ARMCM4.S
)

