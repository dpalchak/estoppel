cmake_minimum_required(VERSION 3.9)

# Enforce minimum language standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${ARCH_TYPE_EMBEDDED})
    if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU")
        message(FATAL_ERROR "Non-GNU compilers not supported for embedded targets")
    endif()
endif()

string(APPEND EMBEDDED_C_CXX_FLAGS
    " -Wall"                    # common warnings
    " -Wextra"                  # extra warnings
    " -Werror"                  # warnings are errors
    " -Wundef"                  # no evaluation of undefined identifiers in #if
    " -Wswitch-enum"            # each enum value must appear in switch
    " -Wswitch-default"         # switch must have default
    " -Wsign-conversion"        # no implicit signedness conversions
    " -Wdouble-promotion"       # no automatic promotion to double
    " -Wconversion"             # check if conversion might affect value
    " -Winit-self"              # no self-initialization
    " -Wlogical-op"             # check bitwise vs logical operations
    " -Wformat=2"               # printf format checking
    " -Wwrite-strings"          # string literals are const
    " -Wno-comment"             # nested comments fine
    " -fdiagnostics-color"      # color compiler output
	" -fomit-frame-pointer"     # no frame pointer
	" -ffunction-sections"      # one section per function
	" -fdata-sections"          # one section per static variable
	" -ffreestanding"           # do not assume existence of standard facilities
	" -fno-common"              # no common section
	" -fdebug-types-section"    # optimize debug sections
	" -fno-exceptions"          # disable exceptions
	" -fno-unwind-tables"       # omit unwind tables
	" -fshort-enums"            # allow enum types to be smallest possible type
	" -g3"                      # all builds include debug info
)

string(APPEND EMBEDDED_CXXFLAGS
    " -Wsuggest-override"       # virtual functions not marked with override
    " -Wplacement-new=2"        # no undefined behavior with placement new
	" -Wno-register"    		# do not warn about deprecated register keyword
	" -fno-rtti"				# disable RTTI
	" -fno-exceptions"			# disable exceptions
	" -fno-threadsafe-statics"	# disable locking during static init
	" -fno-use-cxa-atexit"      # disable atexit for destructors of global objects
)

string(APPEND EMBEDDED_LDFLAGS
	" -static"					# static linking
    " -fdiagnostics-color"      # color output
    " -fno-exceptions"          # disable exceptions
    " -fno-unwind-tables"       # omit unwind tables
    " -fshort-enums"            # allow enum types to be smallest possible type
	" -Wl,--gc-sections"		# elide unused sections (functions and vars)
	" --specs=nano.specs"		# use minimal newlib config
	" --specs=nosys.specs"		# 
)

string(APPEND EMBEDDED_ASMFLAGS
	" -Wa,--warn"				# enable warnings
	" -x assembler-with-cpp"    # assembly files contain C preprocessor directives
)

string(APPEND EMBEDDED_DEFINES
	" -DCROSS_COMPILE=1"
	" -DESTOPPEL=1"
)

if (CMAKE_C_COMPILER_ID MATCHES "GNU")
	string(APPEND HOST_C_CXX_FLAGS
        " -Wall"                    # common warnings
        " -Wextra"                  # extra warnings
        " -Werror"                  # warnings are errors
        " -Wundef"                  # no evaluation of undefined identifiers in #if
        " -Wswitch-enum"            # each enum value must appear in switch
        " -Wswitch-default"         # switch must have default
        " -Wsign-conversion"        # no implicit signedness conversions
        " -Wformat=2"               # printf format checking
        " -Wwrite-strings"          # string literals are const
        " -Wno-comment"             # nested comments fine
        " -fdiagnostics-color"      # color compiler output
	)

    string(APPEND HOST_CFLAGS
        " -fexceptions"             # propagate exceptions (from C++)
    )

elseif (CMAKE_C_COMPILER_ID MATCHES "Clang")
    string(APPEND HOST_C_CXX_FLAGS
        " -Wall"                         # common warnings
        " -Wextra"                       # extra warnings
        " -Werror"                       # warnings are errors
        " -Wundef"                       # no evaluation of undefined identifiers in #if
        " -Wimplicit-fallthrough"        # no fall-through in switch
        " -Wno-covered-switch-default"   # don't need default for complete switch
        " -Wsign-conversion"             # no implicit signedness conversions
        " -Wno-comment"                  # nested comments fine
        " -Wno-reserved-id-macro"        # CppUTest: allow macros for reserved IDs
        " -Wno-disabled-macro-expansion" # CppUTest: nested macros
        " -fcolor-diagnostics"           # color compiler output
    )

    string(APPEND HOST_CFLAGS
        " -fexceptions"           		 # propagate exceptions (from C++)
    )

    string(APPEND HOST_CXXFLAGS
        " -Wno-keyword-macro"            # CppUTest: #define 'new'
    )
else()
	message(FATAL_ERROR "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
endif()

# Architecture specific flags
string(APPEND ARCH_ARM_CM4F_FLAGS
    " -mcpu=cortex-m4"
    " -mlittle-endian"
    " -mfpu=fpv4-sp-d16"
    " -mfloat-abi=hard"
    " -mthumb"
    " -mthumb-interwork"
    " -mabi=aapcs"
)

string(APPEND ARCH_ARM_CM3_FLAGS
    " -mcpu=cortex-m3"
    " -mlittle-endian"
    " -mfloat-abi=soft"
    " -mthumb"
    " -mthumb-interwork"
    " -mabi=aapcs"
)

string(APPEND ARCH_ARM_CM0_FLAGS
    " -mcpu=cortex-m0"
    " -mlittle-endian"
    " -mfloat-abi=soft"
    " -mthumb"
    " -mthumb-interwork"
    " -mabi=aapcs"
)

string(APPEND ARCH_HOST64_FLAGS
    " -m64"
)

string(APPEND ARCH_HOST32_FLAGS
    " -m32"
)

set(ARCH_HOST_FLAGS ${ARCH_HOST64_FLAGS})

string(APPEND CMAKE_C_FLAGS
    "${ARCH_${ARCH}_FLAGS}"
    "${${ARCH_TYPE}_C_CXX_FLAGS}"
    "${${ARCH_TYPE}_CFLAGS}"
)

string(APPEND CMAKE_CXX_FLAGS
    "${ARCH_${ARCH}_FLAGS}"
    "${${ARCH_TYPE}_C_CXX_FLAGS}"
    "${${ARCH_TYPE}_CXXFLAGS}"
)

string(APPEND CMAKE_ASM_FLAGS
    "${ARCH_${ARCH}_FLAGS}"
    "${${ARCH_TYPE}_ASMFLAGS}"
)

string(APPEND CMAKE_EXE_LINKER_FLAGS
    "${ARCH_${ARCH}_FLAGS}"
    "${${ARCH_TYPE}_LDFLAGS}"
)

add_definitions("${${ARCH_TYPE}_DEFINES}")

#This is necessary on OS X platforms
#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#	unset(CMAKE_C_LINK_FLAGS)
#	unset(CMAKE_CXX_LINK_FLAGS)
#endif()

#include(CMakePrintHelpers)
#cmake_print_variables(CMAKE_C_FLAGS)
#cmake_print_variables(CMAKE_CXX_FLAGS)
#cmake_print_variables(CMAKE_ASM_FLAGS)
#cmake_print_variables(CMAKE_EXE_LINKER_FLAGS)
