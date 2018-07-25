
project(armcm4f C CXX ASM)

estp_add_static_library(
    NAME
        armcm4f
    ARCH
        armcm4f
    SOURCES
    	reset_handler.cc
    	vector_table.cc
	LDFLAGS INTERFACE
       -nostartfiles    # Because we provide our own start-up routines
)

