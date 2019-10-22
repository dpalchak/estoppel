cmake_minimum_required(VERSION 3.9)

# Enforce minimum language standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define compilation options using the following format
# ESTP_${COMPILER_ID}_${ARCHITECTURE}_${LANGUAGE}_${CATEGORY}
#
# Compiler ID: GNU, CLANG
# Architecture: ARM, ARMCMxx, HOST, HOST32
# Language: C, CXX, ASM, COMMON, LINK
# Category: WARNINGS, FLAGS, DEFINES
#
# Only the 'category' field is required
#

set(ESTP_DEFINES
    "ESTOPPEL=1"
    "ESTP=1"
)

set(ESTP_ARM_DEFINES
    "ESTP_ARM=1"
)

set(ESTP_GNU_ARM_WARNINGS
    "-Wall"                    # common warnings
    "-Wextra"                  # extra warnings
    "-Werror"                  # warnings are errors
    "-Wundef"                  # no evaluation of undefined identifiers in #if
    "-Wswitch-enum"            # each enum value must appear in switch
    "-Wswitch-default"         # switch must have default
    "-Wsign-conversion"        # no implicit signedness conversions
    "-Wdouble-promotion"       # no automatic promotion to double
    "-Wconversion"             # check if conversion might affect value
    "-Winit-self"              # no self-initialization
    "-Wlogical-op"             # check bitwise vs logical operations
    "-Wformat=2"               # printf format checking
    "-Wwrite-strings"          # string literals are const
    "-Wno-comment"             # nested comments fine
)

set(ESTP_GNU_ARM_COMMON_FLAGS
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

set(ESTP_GNU_ARM_CXX_FLAGS
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

set(ESTP_GNU_ARM_LINK_FLAGS
    "-static"                  # static linking
    "-fdiagnostics-color"      # color output
    "-fno-exceptions"          # disable exceptions
    "-fno-unwind-tables"       # omit unwind tables
    "-fshort-enums"            # allow enum types to be smallest possible type
    "-Wl,--gc-sections"        # elide unused sections (functions and vars)
)

set(ESTP_GNU_ARM_ASM_FLAGS
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
)

set(ESTP_CLANG_HOST_COMMON_FLAGS
    "-fcolor-diagnostics"           # color compiler output
    "-fexceptions"                  # propagate exceptions (from C++)
    "-fwrapv"                       # signed numbers wrap around on arithemtic overflow/underflow
)

set(ESTP_CLANG_HOST_CXX_FLAGS
    "-Wno-keyword-macro"            # CppUTest: #define 'new'
)

# Architecture specific flags
# ARM Cortex-M4F
set(ESTP_GNU_ARMCM4F_COMMON_FLAGS
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)
set(ESTP_GNU_ARMCM4F_LINK_FLAGS
    ${ESTP_GNU_ARMCM4F_COMMON_FLAGS}
)
set(ESTP_ARMCM4F_DEFINES
    "ESTP_ARMCM4F=1"
)

# ARM Cortex-M4 (no FPU)
set(ESTP_GNU_ARMCM4_COMMON_FLAGS
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfloat-abi=soft"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)
set(ESTP_GNU_ARMCM4_LINK_FLAGS
    ${ESTP_GNU_ARMCM4_COMMON_FLAGS}
)
set(ESTP_ARMCM4_DEFINES
    "ESTP_ARMCM4=1"
)

# ARM Cortex-M3
set(ESTP_GNU_ARMCM3_COMMON_FLAGS
    "-mcpu=cortex-m3"
    "-mlittle-endian"
    "-mfloat-abi=soft"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)
set(ESTP_GNU_ARMCM3_LINK_FLAGS
    ${ESTP_GNU_ARMCM3_COMMON_FLAGS}
)
set(ESTP_ARMCM3_DEFINES
    "ESTP_ARMCM3=1"
)

# ARM Cortex-M0
set(ESTP_GNU_ARMCM0P_COMMON_FLAGS
    "-mcpu=cortex-m0plus"
    "-mlittle-endian"
    "-mfloat-abi=soft"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)
set(ESTP_GNU_ARMCM0P_LINK_FLAGS
    ${ESTP_GNU_ARMCM0P_COMMON_FLAGS}
)
set(ESTP_ARMCM0P_DEFINES
    "ESTP_ARMCM0P=1"
)

# 32-bit host arch
set(ESTP_HOST32_COMMON_FLAGS
    "-m32"
)
set(ESTP_HOST32_LINK_FLAGS
    ${ESTP_HOST32_COMMON_FLAGS}
)
set(ESTP_HOST32_DEFINES
    "ESTP_HOST32=1"
)

# Create interface libraries that all targets can depend on
# to inherit the necessary compiler flags and warnings
# We can't use estp_add_interface_library here because that function automatically
# adds a dependency on the Estoppel flags library that we're trying to define.

function(estp_add_flags_library ARCH)
    string(TOLOWER ${ARCH} LIBARCH)
    string(TOUPPER ${ARCH} ARCH)
    string(TOUPPER ${CMAKE_C_COMPILER_ID} TOOL)
    set(LIB_NAME estp_flags-${LIBARCH})

    message(STATUS "Adding flags library ${LIB_NAME} (${LIBARCH})")

    add_library(${LIB_NAME} INTERFACE)
    target_compile_options(${LIB_NAME} INTERFACE
        ${ESTP_WARNINGS}
        ${ESTP_${ARCH}_WARNINGS}
        ${ESTP_${TOOL}_WARNINGS}
        ${ESTP_${TOOL}_${ARCH}_WARNINGS}
        ${ESTP_COMMON_FLAGS}
        ${ESTP_${ARCH}_COMMON_FLAGS}
        ${ESTP_${TOOL}_COMMON_FLAGS}
        ${ESTP_${TOOL}_${ARCH}_COMMON_FLAGS}
    )

    foreach(LANG C CXX ASM)
        estp_target_lang_compile_options(${LIB_NAME} ${LANG} INTERFACE
            ${ESTP_${LANG}_FLAGS}
            ${ESTP_${ARCH}_${LANG}_FLAGS}
            ${ESTP_${TOOL}_${LANG}_FLAGS}
            ${ESTP_${TOOL}_${ARCH}_${LANG}_FLAGS}
        )
    endforeach()

    target_compile_definitions(${LIB_NAME} INTERFACE
        ${ESTP_DEFINES}
        ${ESTP_${TOOL}_DEFINES}
        ${ESTP_${ARCH}_DEFINES}
        ${ESTP_${TOOL}_${ARCH}_DEFINES}
    )

    target_link_libraries(${LIB_NAME} INTERFACE
        ${ESTP_LINK_FLAGS}
        ${ESTP_${ARCH}_LINK_FLAGS}
        ${ESTP_${TOOL}_${ARCH}_LINK_FLAGS}
    )

    foreach(PARENT_ARCH ${ARGN})
        target_link_libraries(${LIB_NAME} INTERFACE estp_flags-${PARENT_ARCH})
    endforeach()

    list(APPEND ESTP_ACTIVE_ARCHS ${ARCH})
endfunction()

# Get the Estoppel build library name for a given architecture in OUT_VAR
# If the architecture isn't supported by the current toolchain, the
# value "" will be returned
function(estp_get_arch_flags_lib OUT_VAR ARCH)
    set(FLAGS_LIB "estp_flags-${ARCH}")
    if(NOT TARGET ${FLAGS_LIB})
        set(FLAGS_LIB "")
    endif()
    set(${OUT_VAR} ${FLAGS_LIB} PARENT_SCOPE)
endfunction()