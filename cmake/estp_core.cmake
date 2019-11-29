CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
include_guard()

include (CMakeParseArguments)

# More convenient function for parsing arguments
function(parse_estp_arguments input_text)
    # First we need to parse our optional arguments into three lists, only one of which we care about
    set(options )
    set(oneValueArgs PREFIX)
    set(multiValueArgs FLAG_ARGS VALUE_ARGS LIST_ARGS REQUIRED_ARGS)
    cmake_parse_arguments(NAMES_OF
        "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NAMES_OF_UNPARSED_ARGUMENTS)
        message(FATAL_ERROR "Failed to parse arguments: ${NAMES_OF_UNPARSED_ARGUMENTS}")
    endif()

    # Clear any existing variables in parent scope
    if(NAMES_OF_PREFIX)
        set(OUT_PREFIX "${NAMES_OF_PREFIX}")
    else()
       set(OUT_PREFIX "ARG")
    endif()

    foreach(ARGNAME ${NAMES_OF_FLAG_ARGS} ${NAMES_OF_VALUE_ARGS} ${NAMES_OF_LIST_ARGS})
        unset(${OUT_PREFIX}_${ARGNAME})
        unset(${OUT_PREFIX}_${ARGNAME} PARENT_SCOPE)
    endforeach()

    # Now parse input text looking for specified arguments
    cmake_parse_arguments(
        "${OUT_PREFIX}"
        "${NAMES_OF_FLAG_ARGS}"
        "${NAMES_OF_VALUE_ARGS}"
        "${NAMES_OF_LIST_ARGS}"
        ${input_text}
        )

    set(unparsed_args_var_name "${OUT_PREFIX}_UNPARSED_ARGUMENTS")
    if("${${unparsed_args_var_name}}")
        message(FATAL_ERROR "Failed to parse arguments: ${${unparsed_args_var_name}}")
    endif()

    # Check all required arguments were passed
    foreach (REQ_ARG ${NAMES_OF_REQUIRED_ARGS})
        if(NOT ${OUT_PREFIX}_${REQ_ARG})
            message(FATAL_ERROR "Required argument not provided: ${REQ_ARG}")
        endif()
    endforeach()

    # Set argument variables in parent scope
    foreach(ARGNAME ${NAMES_OF_FLAG_ARGS} ${NAMES_OF_VALUE_ARGS} ${NAMES_OF_LIST_ARGS})
        set(varname "${OUT_PREFIX}_${ARGNAME}")
        set(${varname} ${${varname}} PARENT_SCOPE)
    endforeach()
endfunction()

# Helper functions to add language-specific compile options to targets
function(estp_add_target_lang_compile_options TARGET_NAME LANG)
    if(NOT TARGET ${TARGET_NAME})
        message(FATAL_ERROR "Unknown target ${TARGET_NAME}")
        return()
    endif()

    parse_estp_arguments("${ARGN}" LIST_ARGS PRIVATE PUBLIC INTERFACE)

    set(ACCESS_KEYWORDS "PRIVATE" "PUBLIC" "INTERFACE")
    set(OPT_STRING "")
    foreach(ACCESS PRIVATE PUBLIC INTERFACE)
        if(ARG_${ACCESS})
            foreach(OPT ${ARG_${ACCESS}})
                target_compile_options(${TARGET_NAME} ${ACCESS}
                    $<$<COMPILE_LANGUAGE:${LANG}>:${OPT}>
                )
            endforeach()
        endif()
    endforeach()
endfunction()

# Remove a particular flag from a target
function(estp_remove_target_compile_options TARGET_NAME)
    get_target_property(TARGET_OPTS ${TARGET_NAME} COMPILE_OPTIONS)
    if(TARGET_OPTS)
        foreach(OPT ${ARGN})
            list(REMOVE_ITEM TARGET_OPTS ${OPT})
        endforeach()
        set_target_properties(${TARGET_NAME} PROPERTIES COMPILE_OPTIONS "${TARGET_OPTS}")
    endif()
endfunction()

# Easy way to add target link libraries surround with "whole-archive" flag
function(target_link_whole_libraries NAME ACCESS)
    string(TOLOWER "${CMAKE_HOST_SYSTEM_NAME}" HOST_SYSTEM_NAME)
    if(HOST_SYSTEM_NAME MATCHES "darwin")
        set(WHOLE_LIB_PREFIX_FLAG "") #-Wl,-all_load")
        set(WHOLE_LIB_SUFFIX_FLAG "") #-Wl,-noall_load")
    else()
        set(WHOLE_LIB_PREFIX_FLAG "-Wl,--whole-archive")
        set(WHOLE_LIB_SUFFIX_FLAG "-Wl,--no-whole-archive")
    endif()
    target_link_libraries(${NAME} ${ACCESS}
        ${WHOLE_LIB_PREFIX_FLAG}
        ${ARGN}
        ${WHOLE_LIB_SUFFIX_FLAG}
    )
endfunction(target_link_whole_libraries)

# Add a platform/processor
function(add_estp_platform_libraries NAME)
    parse_estp_arguments("${ARGN}"
        LIST_ARGS
            EXTENDS
    )

    set(BUILD_LIB "${NAME}_platform_build")
    set(LINK_LIB "${NAME}_platform_link")
    set(SOURCES_LIB "${NAME}_platform_sources")

    message(STATUS "Adding ${NAME} platform libraries: ${BUILD_LIB}, ${LINK_LIB}, ${SOURCES_LIB}")

    add_library(${BUILD_LIB} INTERFACE)
    add_library(${LINK_LIB} INTERFACE)
    # The SOURCES_LIB is a static library with an empty file added
    # just in case no other sources get added
    add_library(${SOURCES_LIB} STATIC)
    _estp_add_empty_file_to_target(${SOURCES_LIB})
    target_link_libraries(${SOURCES_LIB} PUBLIC estp_build)

    foreach(DEP ${ARG_EXTENDS})
        message(STATUS "Adding dependency to platform ${NAME} on platform ${DEP}")
        target_link_libraries(${BUILD_LIB} INTERFACE "${DEP}_platform_build")
        target_link_libraries(${LINK_LIB} INTERFACE "${DEP}_platform_link")
        target_link_whole_libraries(${SOURCES_LIB} PUBLIC
            "${DEP}_platform_sources"
        )
    endforeach()

    if(NAME STREQUAL ESTP_PLATFORM)
        message(STATUS "Selecting target platform: ${NAME}")
        target_link_libraries(estp_build INTERFACE ${BUILD_LIB})
        target_link_libraries(estp_link INTERFACE ${LINK_LIB})
        target_link_whole_libraries(estp_platform INTERFACE
            ${SOURCES_LIB}
        )
    endif()

endfunction(add_estp_platform_libraries)

# Adds an executable with dependencies on estp_build, estp_link, and estp_platform libraries
function(add_estp_executable NAME)
    message(STATUS "Adding executable ${NAME}")

    add_executable(${NAME} ${ARGN})

    target_link_libraries(${NAME} PRIVATE
        estp_build
        estp_platform
        estp_link
    )

    if(ESTP_DEVICE_PLATFORM)
        add_custom_command(TARGET ${NAME} POST_BUILD
            COMMAND chmod -x $<TARGET_FILE_NAME:${NAME}>
        )
        _add_estp_bin_output(${NAME})
        _add_estp_hex_output(${NAME})
        _add_estp_sizeinfo_output(${NAME})
    endif()
    _add_estp_mapfile_output(${NAME})

endfunction(add_estp_executable)

# Adds a library with a public dependency on estp_build
function(add_estp_library NAME)
    add_library("${NAME}" ${ARGN})

    set(visibility PUBLIC)
    if(ARGN)
        list(GET ARGN 0 libtype)
        if(libtype STREQUAL INTERFACE)
            set(visibility INTERFACE)
        endif()
    endif()

    target_link_libraries("${NAME}" "${visibility}" estp_build)
endfunction(add_estp_library)

# Adds an executable comprising one or more unit tests
function(add_estp_unit_test NAME)
    # For now we only support unit tests running on the host platform
    if(ESTP_BUILD_TESTING)
        message(STATUS "Adding unit test ${NAME}")
    else()
        message(STATUS "Unit tests not supported on current platform. Skipping unit test ${NAME}")
        return()
    endif()

    add_executable(${NAME} ${ARGN})
    target_link_libraries(${NAME} PRIVATE
        estp_build
        estp_platform
        estp_link
        catch2_test_fixture
    )
    catch_discover_tests(${NAME} TEST_PREFIX "[FOO]...")
endfunction(add_estp_unit_test)


# Simple helper functions for common usage scenarios
function(add_estp_host_executable)
    if(ESTP_HOST_PLATFORM)
        add_estp_executable(${ARGN})
    endif()
endfunction()

function(add_estp_device_executable)
    if(ESTP_DEVICE_PLATFORM)
        add_estp_executable(${ARGN})
    endif()
endfunction()

function(add_estp_host_library)
    if(ESTP_HOST_PLATFORM)
        add_estp_library(${ARGN})
    endif()
endfunction()

function(add_estp_device_library)
    if(ESTP_DEVICE_PLATFORM)
        add_estp_library(${ARGN})
    endif()
endfunction()

function(add_estp_host_test)
    if(ESTP_HOST_PLATFORM)
        add_estp_unit_test(${ARGN})
    endif()
endfunction()

function(add_estp_device_library)
    if(ESTP_DEVICE_PLATFORM)
        add_estp_unit_test(${ARGN})
    endif()
endfunction()

function(add_host_subdirectory)
    if(ESTP_HOST_PLATFORM)
        add_subdirectory(${ARGN})
    endif()
endfunction()

function(add_device_subdirectory)
    if(ESTP_DEVICE_PLATFORM)
        add_subdirectory(${ARGN})
    endif()
endfunction()
