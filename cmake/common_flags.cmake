cmake_minimum_required(VERSION 3.9)

if(CMAKE_C_COMPILER_ID MATCHES "GNU")
	# Set common flags for GCC
	set(ESTP_CFLAGS
		"-Wall "
		)

	set(ESTP_CXXFLAGS
		"-Wall "
		"-Wno-register "
		)

	set(ESTP_LDFLAGS
		"-Wl,--gc-sections "
		)

	set(ESTP_ASMFLAGS
		"-Wa,--warn "
		"-x assembler-with-cpp "
		)

	set(ESTP_DEFINES
		"-DESTOPPEL=1 "
		)
else()
	message(FATAL_ERROR "Non-GNU compilers not yet supported.")
endif() # GCC compiler

if(CMAKE_CROSSCOMPILING)
	string(APPEND ESTP_CFLAGS
		"-fomit-frame-pointer "
		"-ffunction-sections "
		"-fdata-sections "
		"-ffreestanding "
		)

	string(APPEND ESTP_CXXFLAGS
		"-fomit-frame-pointer "
		"-ffunction-sections "
		"-fdata-sections "
		"-ffreestanding "
		"-fno-rtti "
		"-fno-exceptions "
		"-fno-threadsafe-statics "
		)

	string(APPEND ESTP_LDFLAGS
		"-Wl,-Map=system.map "
		"-static "
		"--specs=nosys.specs "
		)

	string(APPEND ESTP_DEFINES
		"-DCROSS_COMPILE=1 "
		)

	set(ESTP_LINK_LIBRARIES_PREFIX "-Wl,--whole-archive ")
	set(ESTP_LINK_LIBRARIES_SUFFIX "-Wl,--no-whole-archive ")

endif() #Cross compiling

string(APPEND CMAKE_C_FLAGS ${ESTP_CFLAGS})
string(APPEND CMAKE_CXX_FLAGS ${ESTP_CXXFLAGS})
string(APPEND CMAKE_ASM_FLAGS ${ESTP_ASMFLAGS})
string(APPEND CMAKE_EXE_LINKER_FLAGS ${ESTP_LDFLAGS})

add_definitions(${ESTP_DEFINES})

#This is necessary on OS X platforms
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	unset(CMAKE_C_LINK_FLAGS)
	unset(CMAKE_CXX_LINK_FLAGS)
endif()


