cmake_minimum_required(VERSION 3.9)

# Enforce minimum language standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if($<BUILD_ENV:firmware>)
	if(NOT CMAKE_C_COMPILER_ID MATCHES "GNU")
		message(FATAL_ERROR 
			"Non-GNU compilers not supported for firmware builds: "
			${CMAKE_C_COMPILER_ID}
		)
	endif()
				
	set(ESTP_C_CXX_FLAGS
        " -Wall"                    # common warnings
        " -Wextra"                  # extra warnings
        " -Werror"                  # warnings are errors
        " -Wswitch-enum"            # each enum value must appear in switch
        " -Wswitch-default"         # switch must have default
        " -Wsign-conversion"        # no implicit signedness conversions
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
		" -g"                       # all builds include debug info
	)

	set(ESTP_CXXFLAGS
		" -Wno-register"    		# do not warn about deprecated register keyword
		" -fno-rtti"				# disable RTTI
		" -fno-exceptions"			# disable exceptions
		" -fno-threadsafe-statics"	# disable locking during static init
		" -fno-use-cxa-atexit"      # disable atexit for destructors of global objects 
	)

	set(ESTP_LDFLAGS
		" -Wl,--gc-sections"		# omit unused sections (functions and vars)
		" --specs=nosys.specs"		# no system libraries
	)
	
	set(ESTP_ASMFLAGS
		" -Wa,--warn"				# enable warnings
		" -x assembler-with-cpp"    # assembly files contain C preprocessor directives
	)
		
	string(APPEND ESTP_DEFINES
		" -DCROSS_COMPILE=1"
		" -DESTOPPEL=1"
	)
	
	set(CMAKE_EXECUTABLE_SUFFIX ".elf")
	set(CMAKE_DEBUG_POSTFIX "-dbg")
	set(CMAKE_RELEASE_POSTFIX "-rel")
	set(CMAKE_MINSIZEREL_POSTFIX "-rel")
	set(CMAKE_RELWITHDEBINFO_POSTFIX "-rel")

else() # All other targets

    if (CMAKE_C_COMPILER_ID MATCHES "GNU")
    	set(ESTP_C_CXX_FLAGS
	        " -Wall"                    # common warnings
	        " -Wextra"                  # extra warnings
	        " -Werror"                  # warnings are errors
	        " -Wswitch-enum"            # each enum value must appear in switch
	        " -Wswitch-default"         # switch must have default
	        " -Wsign-conversion"        # no implicit signedness conversions
	        " -Wconversion"             # check if conversion might affect value
	        " -Winit-self"              # no self-initialization
	        " -Wlogical-op"             # check bitwise vs logical operations
	        " -Wformat=2"               # printf format checking
	        " -Wwrite-strings"          # string literals are const
	        " -Wno-comment"             # nested comments fine
	        " -fdiagnostics-color"      # color compiler output
		)

        set(ESTP_CFLAGS
            " -fexceptions"             # propagate exceptions (from C++)
        )

    elseif (CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(ESTP_C_CXX_FLAGS
            " -Wall"                         # common warnings
            " -Wextra"                       # extra warnings
            " -Werror"                       # warnings are errors
            " -Wimplicit-fallthrough"        # no fall-through in switch
            " -Wno-covered-switch-default"   # don't need default for complete switch
            " -Wsign-conversion"             # no implicit signedness conversions
            " -Wno-comment"                  # nested comments fine
            " -Wno-reserved-id-macro"        # CppUTest: allow macros for reserved IDs
            " -Wno-disabled-macro-expansion" # CppUTest: nested macros
            " -fcolor-diagnostics"           # color compiler output
        )

        set(ESTP_CFLAGS
            " -fexceptions"           		 # propagate exceptions (from C++)
        )

        set(ESTP_CXXFLAGS
            " -Wno-keyword-macro"            # CppKUTest: #define 'new'
        )
    else()
    	message(FATAL_ERROR "Unsupported compiler: ${CMAKE_C_COMPILER_ID}")
    endif()
endif() # BUILD_ENV

string(APPEND CMAKE_C_FLAGS ${ESTP_C_CXX_FLAGS} ${ESTP_CFLAGS})
string(APPEND CMAKE_CXX_FLAGS ${ESTP_C_CXX_FLAGS} ${ESTP_CXXFLAGS})
string(APPEND CMAKE_ASM_FLAGS ${ESTP_ASMFLAGS})
string(APPEND CMAKE_EXE_LINKER_FLAGS ${ESTP_LDFLAGS})

add_definitions(${ESTP_DEFINES})

#This is necessary on OS X platforms
#if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#	unset(CMAKE_C_LINK_FLAGS)
#	unset(CMAKE_CXX_LINK_FLAGS)
#endif()


