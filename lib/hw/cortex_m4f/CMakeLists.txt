
if(NOT ${ARCH} STREQUAL "ARM_CM4F")
    return()
endif()

project(cm4f_startup C CXX ASM)

add_library(cm4f_startup STATIC
	startup_ARMCM4.S
)

