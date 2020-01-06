CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
include_guard()

# Enforce minimum language standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define compilation options using the following format
# ESTP_${COMPILER_ID}_${ARCHITECTURE}_${LANGUAGE}_${CATEGORY}
#
# Compiler ID: GNU, CLANG
# Target: HOST, DEVICE
# Language: COMMON, C, CXX, ASM, LINK
# Category: WARNINGS, FLAGS, DEFINES
#
# Only the 'category' field is required
#

set(ESTP_DEFINES
    "ESTOPPEL=1"
    "ESTP=1"
)

set(ESTP_DEVICE_DEFINES
    "ESTP_DEVICE=1"
)

set(ESTP_GNU_DEVICE_WARNINGS
    "-Wall"                    # common warnings
    "-Wextra"                  # extra warnings
    "-Werror"                  # warnings are errors
    "-Wundef"                  # no evaluation of undefined identifiers in #if
    "-Wswitch-enum"            # each enum value must appear in switch
    "-Wswitch-default"         # switch must have default
    #"-Wsign-conversion"       # no implicit signedness conversions -- this is disabled due to GCC bug 87519
    "-Wdouble-promotion"       # no automatic promotion to double
    "-Wconversion"             # check if conversion might affect value
    "-Winit-self"              # no self-initialization
    "-Wlogical-op"             # check bitwise vs logical operations
    "-Wformat=2"               # printf format checking
    "-Wwrite-strings"          # string literals are const
    "-Wno-comment"             # nested comments fine
)

set(ESTP_GNU_DEVICE_COMMON_FLAGS
    "-fwrapv"                  # signed numbers wrap around on arithemtic overflow/underflow
    "-fdiagnostics-color"      # color compiler output
    "-fomit-frame-pointer"     # no frame pointer
    "-ffunction-sections"      # one section per function
    "-fdata-sections"          # one section per static variable
    "-ffreestanding"           # do not assume existence of standard facilities
    "-fno-common"              # no common section
    "-fdebug-types-section"    # optimize debug sections
    "-fno-exceptions"          # disable exceptions
    "-fno-unwind-tables"       # omit unwind tables
    "-fshort-enums"            # allow enum types to be smallest possible type
    "-finline-small-functions" # inline functions their body is smaller than the call overhead
    "-findirect-inlining"      # allow indirect calls to be inlined
    "-g3"                      # all builds include debug info
)

set(ESTP_GNU_DEVICE_CXX_FLAGS
    "-Weffc++"                 # Scott Meyers' Effective C++ warnings
    "-Wsuggest-override"       # virtual functions not marked with override
    "-Wplacement-new=2"        # no undefined behavior with placement new
    "-Wno-register"            # do not warn about deprecated register keyword
    "-fno-rtti"                # disable RTTI
    "-fno-exceptions"          # disable exceptions
    "-fno-threadsafe-statics"  # disable locking during static init
    "-fno-use-cxa-atexit"      # disable atexit for destructors of global objects
    "-fno-implicit-templates"  # require explicit instantiation of all templates
)

set(ESTP_GNU_DEVICE_LINK_FLAGS
    "-static"                  # static linking
    "-fdiagnostics-color"      # color output
    "-fno-exceptions"          # disable exceptions
    "-fno-unwind-tables"       # omit unwind tables
    "-fshort-enums"            # allow enum types to be smallest possible type
    "-Wl,--gc-sections"        # elide unused sections (functions and vars)
    "-std=gnu++17"
)

set(ESTP_GNU_DEVICE_ASM_FLAGS
    "-Wa,--warn"               # enable warnings
)

set(ESTP_GNU_HOST_WARNINGS
    "-Wall"                    # common warnings
    "-Wextra"                  # extra warnings
    "-Werror"                  # warnings are errors
    "-Wundef"                  # no evaluation of undefined identifiers in #if
    "-Wswitch-enum"            # each enum value must appear in switch
    "-Wswitch-default"         # switch must have default
    "-Wsign-conversion"        # no implicit signedness conversions
    "-Wformat=2"               # printf format checking
    "-Wwrite-strings"          # string literals are const
    "-Wno-comment"             # nested comments fine
)

set(ESTP_HOST_DEFINES
    "ESTP_HOST=1"
)

set(ESTP_GNU_HOST_COMMON_FLAGS
    "-fdiagnostics-color"      # color compiler output
    "-fexceptions"             # propagate exceptions (from C++)
    "-fwrapv"                  # signed numbers wrap around on arithemtic overflow/underflow
)

set(ESTP_CLANG_HOST_WARNINGS
    "-Wall"                         # common warnings
    "-Wextra"                       # extra warnings
    "-Werror"                       # warnings are errors
    "-Wundef"                       # no evaluation of undefined identifiers in #if
    "-Wimplicit-fallthrough"        # no fall-through in switch
    "-Wno-covered-switch-default"   # don't need default for complete switch
    "-Wsign-conversion"             # no implicit signedness conversions
    "-Wno-comment"                  # nested comments fine
    "-Wno-reserved-id-macro"        # CppUTest: allow macros for reserved IDs
    "-Wno-disabled-macro-expansion" # CppUTest: nested macros
    "-Wno-missing-braces"           # Disable Clang's overzealous missing-braces warnings
    "-Wno-gnu-string-literal-operator-template" # TypeString string literal operator templates use a GNU extension
)

set(ESTP_CLANG_HOST_COMMON_FLAGS
    "-fcolor-diagnostics"           # color compiler output
    "-fexceptions"                  # propagate exceptions (from C++)
    "-fwrapv"                       # signed numbers wrap around on arithemtic overflow/underflow
)

set(ESTP_CLANG_HOST_CXX_FLAGS
    "-Wno-keyword-macro"            # CppUTest: #define 'new'
)

set(ESTP_OPT_NONE_FLAGS
    "-O0"
)

set(ESTP_OPT_DEBUG_FLAGS
    "-Og"
)

set(ESTP_OPT_SIZE_FLAGS
    "-Os"
)

set(ESTP_OPT_SPEED_FLAGS
    "-O3"
)
