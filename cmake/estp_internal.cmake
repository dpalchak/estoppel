CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
include_guard()

# add_estp_platform_libraries():
#   creates $NAME_platform_build (i/f), $NAME_platform_link (i/f), $NAME_platform_sources (static)
# estp_build : default flags -> $PLATFORM_build -> $EXTENDS_build
# estp_link -> $PLATFORM_link -> $EXTENDS_link
# estp_$LIB -> estp_build
# $PLATFORM_sources : platform sources -> estp_build, $EXTENDS_sources, [estp_libs]
# estp_platform -> $PLATFORM_sources
# user_libs -> estp_libs, [estp_platform]
# executable -> estp_build, user_libs+sources, estp_platform, estp_link


# Add a static library with at least one empty source file
# Other sources can be specified as arguments or added later with
# standard target_sources() call(s)
function(_estp_add_empty_file_to_target NAME)
    set(EMPTY_FILE "${CMAKE_BINARY_DIR}/estp_empty_file.cc")
    file(TOUCH ${EMPTY_FILE})
    if(TARGET ${NAME})
        target_sources(${NAME} PRIVATE ${EMPTY_FILE})
    else()
        message(FATAL_ERROR "Unable to add empty file to target '${NAME}' -- target does not exist")
    endif()
endfunction()


# Creates the estp_build library that provides the "global" build flags
# for all targets. This needs to be called in the top-level CMakeLists.txt
# *after* the platform has been defined.
# The flags library hierarchy in Estoppel is as follows:
# estp_add_platform_libraries(NAME) -> creates $NAME_build (i/f), $NAME_link (i/f),
# $NAME_sources (static)
# estp_build = default flags -> $PLATFORM_build
function(_add_estp_build_library)

    # Estoppel-specific flags/defines
    add_library(estp_build INTERFACE)

    target_include_directories(estp_build INTERFACE "${ESTP_ROOT}")

    string(TOUPPER ${CMAKE_C_COMPILER_ID} TOOL)
    string(TOUPPER ${ESTP_OPT} OPT)

    if(ESTP_DEVICE_PLATFORM)
        set(PLAT "DEVICE")
    else()
        set(PLAT "HOST")
    endif()

    target_compile_options(estp_build INTERFACE
        ${ESTP_WARNINGS}
        ${ESTP_${PLAT}_WARNINGS}
        ${ESTP_${TOOL}_WARNINGS}
        ${ESTP_${TOOL}_${PLAT}_WARNINGS}
        ${ESTP_COMMON_FLAGS}
        ${ESTP_${PLAT}_COMMON_FLAGS}
        ${ESTP_${TOOL}_COMMON_FLAGS}
        ${ESTP_${TOOL}_${PLAT}_COMMON_FLAGS}
        ${ESTP_OPT_${OPT}_FLAGS}
    )

    foreach(LANG C CXX ASM)
        estp_add_target_lang_compile_options(estp_build ${LANG} INTERFACE
            ${ESTP_${LANG}_FLAGS}
            ${ESTP_${PLAT}_${LANG}_FLAGS}
            ${ESTP_${TOOL}_${LANG}_FLAGS}
            ${ESTP_${TOOL}_${PLAT}_${LANG}_FLAGS}
        )
    endforeach()

    target_compile_definitions(estp_build INTERFACE
        ${ESTP_DEFINES}
        ${ESTP_${TOOL}_DEFINES}
        ${ESTP_${PLAT}_DEFINES}
        ${ESTP_${TOOL}_${PLAT}_DEFINES}
    )

    target_link_libraries(estp_build INTERFACE
        ${ESTP_LINK_FLAGS}
        ${ESTP_${PLAT}_LINK_FLAGS}
        ${ESTP_${TOOL}_${PLAT}_LINK_FLAGS}
    )

endfunction(_add_estp_build_library)

# Creates the estp_link interface library
# This library is depended on by executables to provide linker script command line flags
# The estp_link library is made to depend on the $PLATFORM_link library once the latter is added
function(_add_estp_link_library)
    add_library(estp_link INTERFACE)
    target_compile_definitions(estp_link INTERFACE "ESTP_LINK=1")
endfunction(_add_estp_link_library)

# Creates the estp_platform interface library
# This library is depended on by user libraries and executables that need access to
# platform-specific (aka hardware-specific) functionality.
# This estp_platform library is made to depend on the $PLATFORM_sources library once the latter
# gets defined
function(_add_estp_platform_library)
    add_library(estp_platform INTERFACE)
    target_compile_definitions(estp_platform INTERFACE "ESTP_PLATFORM=1")
endfunction()

function(_add_estp_customization_libraries)
    _add_estp_build_library()
    _add_estp_link_library()
    _add_estp_platform_library()
endfunction()

# Add binary output to target
function(_add_estp_bin_output TARGET_NAME)
    #_estp_target_file_name(EXE_FILE_NAME ${TARGET_NAME})
    #_estp_replace_target_file_name_suffix(BIN_FILE_NAME ${TARGET_NAME} ".bin")
    set(BIN_FILE_NAME "${TARGET_NAME}.bin")
    add_custom_command(
        TARGET ${TARGET_NAME}
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE_NAME:${TARGET_NAME}> ${BIN_FILE_NAME}
        DEPENDS ${TARGET_NAME}
        COMMENT "Create binary image: ${BIN_FILE_NAME}"
    )
endfunction()

# Add Intel hex output to target
function(_add_estp_hex_output TARGET_NAME)
    set(HEX_FILE_NAME "${TARGET_NAME}.hex")
    add_custom_command(
        TARGET ${TARGET_NAME}
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE_NAME:${TARGET_NAME}> ${HEX_FILE_NAME}
        DEPENDS ${TARGET_NAME}
        COMMENT "Create ihex image: ${HEX_FILE_NAME}"
    )
endfunction()

# Print size information for target
function(_add_estp_sizeinfo_output TARGET_NAME)
    if(NOT DEFINED CMAKE_SIZEINFO)
        set(CMAKE_SIZEINFO "size")
    endif()
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZEINFO} --format=sysv "$<TARGET_FILE:${TARGET_NAME}>"
        COMMENT "Image size:"
    )
endfunction()

# Adds map file generation to a target
function(_add_estp_mapfile_output TARGET_NAME)
    # Generate map output file
    set(MAP_FILE_NAME "${TARGET_NAME}.map")
    if(CMAKE_C_COMPILER_ID MATCHES "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE "-Wl,-Map=${MAP_FILE_NAME}")
    elseif(CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_link_libraries(${TARGET_NAME} PRIVATE "-Wl,-map,${MAP_FILE_NAME}")
    else()
        message(WARNING "Unsupported compiler ID: skipping MAP file generation for ${TARGET_NAME}")
    endif()
endfunction()
