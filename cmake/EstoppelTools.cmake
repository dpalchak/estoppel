
include (CMakeParseArguments)

# Get the Estoppel build library name for a given architecture in OUT_VAR
# If the architecture isn't supported by the current toolchain, the
# value "" will be returned
function(estp_get_arch_build_library OUT_VAR ARCH)
    set(ARCH_BUILD_LIB "estoppel_build-${ARCH}")
    if(NOT TARGET ${ARCH_BUILD_LIB})
        set(ARCH_BUILD_LIB "")
    endif()
    set(${OUT_VAR} ${ARCH_BUILD_LIB} PARENT_SCOPE)
endfunction()

# More convenient function for parsing arguments
function(estp_parse_arguments input_text)
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
function(estp_target_lang_compile_options TARGET_NAME LANG)
    if(NOT TARGET ${TARGET_NAME})
        message(FATAL_ERROR "Unknown target ${TARGET_NAME}")
        return()
    endif()

    estp_parse_arguments("${ARGN}" LIST_ARGS PRIVATE PUBLIC INTERFACE)

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

# Estoppel-specific commands for adding targets
# These automatically account for the current toolchain
function(estp_add_executable)
    estp_parse_arguments("${ARGN}"
        VALUE_ARGS
            NAME ARCH
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS CXXFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME ARCH SOURCES
    )

    # First get the build library for the specified architecture
    estp_get_arch_build_library(ARCH_BUILD_LIB ${ARG_ARCH})
    if(ARCH_BUILD_LIB)
        message(STATUS "Adding executable ${ARG_NAME} (${ARG_ARCH})")
    else()
        message(STATUS "Skipping executable ${ARG_NAME} (${ARG_ARCH})")
        return() # Bail out
    endif()

    add_executable(${ARG_NAME} ${ARG_SOURCES})

    # Add private dependency on architecture-specific library to pull-in build settings
    target_link_libraries(${ARG_NAME} PRIVATE ${ARCH_BUILD_LIB})

    if(ARG_DEFINES)
        target_compile_definitions(${ARG_NAME} ${ARG_DEFINES})
    endif()

    if(ARG_CFLAGS)
        target_compile_options(${ARG_NAME} ${ARG_CFLAGS})
    endif()

    if(ARG_CXXFLAGS)
        estp_target_lang_compile_options(${ARG_NAME} CXX ${ARG_CXXFLAGS})
    endif()

    if(ARG_INCLUDE_DIRS)
        target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRS})
    endif()

    if(ARG_LDFLAGS)
        target_link_libraries(${ARG_NAME} ${ARG_LDFLAGS})
    endif()

    if(ARG_LIBRARIES)
        target_link_libraries(${ARG_NAME} ${ARG_LIBRARIES})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

endfunction() #estp_add_executable


function(estp_add_static_library)
    estp_parse_arguments("${ARGN}"
        VALUE_ARGS
            NAME ARCH
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME ARCH SOURCES
    )

    # First get the build library for the specified architecture
    estp_get_arch_build_library(ARCH_BUILD_LIB ${ARG_ARCH})
    if(ARCH_BUILD_LIB)
        message(STATUS "Adding static library ${ARG_NAME} (${ARG_ARCH})")
    else()
        message(STATUS "Skipping static library ${ARG_NAME} (${ARG_ARCH})")
        return() # Bail out
    endif()

    add_library(${ARG_NAME} STATIC ${ARG_SOURCES})

    # Add private dependency on architecture-specific library to pull-in build settings
    target_link_libraries(${ARG_NAME} PRIVATE ${ARCH_BUILD_LIB})

    if(ARG_LDFLAGS)
        target_link_libraries(${ARG_NAME} ${ARG_LDFLAGS})
    endif()

    if(ARG_LIBRARIES)
        target_link_libraries(${ARG_NAME} ${ARG_LIBRARIES})
    endif()

    if(ARG_DEFINES)
        target_compile_definitions(${ARG_NAME} ${ARG_DEFINES})
    endif()

    if(ARG_CFLAGS)
        target_compile_options(${ARG_NAME} ${ARG_CFLAGS})
    endif()

    if(ARG_INCLUDE_DIRS)
        target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRS})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

endfunction() #estp_add_static_library

# Interface libraries are different than static libraries in that interface libraries
# are not required to specify a specific architecture
function(estp_add_interface_library)
    estp_parse_arguments("${ARGN}"
        VALUE_ARGS
            NAME ARCH
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME
    )

    if(DEFINED ARG_ARCH)
        # First get the build library for the specified architecture
        estp_get_arch_build_library(ARCH_BUILD_LIB ${ARG_ARCH})
        if(ARCH_BUILD_LIB)
            message(STATUS "Adding interface library ${ARG_NAME} (${ARG_ARCH})")
        else()
            message(STATUS "Skipping interface library ${ARG_NAME} (${ARG_ARCH})")
            return() # Bail out
        endif()
    else()
        message(STATUS "Adding interface library ${ARG_NAME} (noarch)")
    endif()

    add_library(${ARG_NAME} INTERFACE)

    if(ARCH_BUILD_LIB)
        # Add dependency on architecture-specific library to pull-in build settings
        target_link_libraries(${ARG_NAME} INTERFACE ${ARCH_BUILD_LIB})
    endif()

    if(ARG_SOURCES)
        target_sources(${ARG_NAME} INTERFACE ${ARG_SOURCES})
    endif()

    if(ARG_LDFLAGS)
        target_link_libraries(${ARG_NAME} INTERFACE ${ARG_LDFLAGS})
    endif()

    if(ARG_LIBRARIES)
        target_link_libraries(${ARG_NAME} INTERFACE ${ARG_LIBRARIES})
    endif()

    if(ARG_DEFINES)
        target_compile_definitions(${ARG_NAME} INTERFACE ${ARG_DEFINES})
    endif()

    if(ARG_CFLAGS)
        target_compile_options(${ARG_NAME} INTERFACE ${ARG_CFLAGS})
    endif()

    if(ARG_INCLUDE_DIRS)
        target_include_directories(${ARG_NAME} INTERFACE ${ARG_INCLUDE_DIRS})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()
endfunction() #estp_add_interface_library

# A shortcut for adding an executable with extra outputs
function(estp_add_firmware_executable)
    # Add the executable first, to make sure the arguments are valid
    estp_add_executable(${ARGN})

    # Extract the NAME argument only
    # First find the index of the keyword 'NAME'
    list(FIND ARGN NAME NAME_INDEX)
    # Awful CMake syntax for incrementing a value, because we want the item
    # following the keyword 'NAME'
    math(EXPR NAME_INDEX "${NAME_INDEX}+1")
    list(GET ARGN ${NAME_INDEX} TARGET_NAME)

    if(NOT TARGET ${TARGET_NAME})
        # Target wasn't added, which means it's not supported by this toolchain
        return()
    endif()

    get_target_property(TARGET_PREFIX ${TARGET_NAME} PREFIX)
    if(${TARGET_PREFIX} MATCHES "NOTFOUND")
        set(TARGET_PREFIX "")
    endif()

    get_target_property(TARGET_OUTPUT_NAME ${TARGET_NAME} OUTPUT_NAME)
    if(${TARGET_OUTPUT_NAME} MATCHES "NOTFOUND")
        set(TARGET_OUTPUT_NAME ${TARGET_NAME})
    endif()

    get_target_property(TARGET_SUFFIX ${TARGET_NAME} SUFFIX)
    if(${TARGET_SUFFIX} MATCHES "NOTFOUND")
        set(TARGET_SUFFIX "")
    endif()

    set(EXE_FILE_NAME "${TARGET_PREFIX}${TARGET_OUTPUT_NAME}${TARGET_SUFFIX}")

    string(REPLACE ".elf" ".map" MAP_FILE_NAME "${EXE_FILE_NAME}")
    string(REPLACE ".elf" ".bin" BIN_FILE_NAME "${EXE_FILE_NAME}")
    string(REPLACE ".elf" ".hex" HEX_FILE_NAME "${EXE_FILE_NAME}")

    # Generate map output file
    target_link_libraries(${TARGET_NAME} PRIVATE "-Wl,-Map=${MAP_FILE_NAME}")

    # Create binary image
    add_custom_command(
        TARGET ${TARGET_NAME}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${EXE_FILE_NAME} ${BIN_FILE_NAME}
        DEPENDS ${TARGET_NAME}
        WORKING_DIRECTORY "${TARGET_OUTPUT_DIR}"
        COMMENT "Create binary image: ${BIN_FILE_NAME}"
    )

    # Create hex image
    add_custom_command(
        TARGET ${TARGET_NAME}
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXE_FILE_NAME} ${HEX_FILE_NAME}
        DEPENDS ${TARGET_NAME}
        WORKING_DIRECTORY "${TARGET_OUTPUT_DIR}"
        COMMENT "Create ihex image: ${HEX_FILE_NAME}"
    )

    # Print executable size info
    add_custom_command(
        TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZEINFO} --format=sysv ${EXE_FILE_NAME}
    	WORKING_DIRECTORY "${TARGET_OUTPUT_DIR}"
        COMMENT "Image size:"
    )
endfunction()

# A shortcut for adding a set of unit tests
function(estp_add_test_executable)
    estp_parse_arguments("${ARGN}"
        VALUE_ARGS
            NAME ARCH
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS CXXFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME ARCH SOURCES
    )

    if(NOT (${ARCH} IN_LIST ESTP_HOST_ARCHS))
        message(FATAL_ERROR "Test executables must specify a host architecture")
    endif()

    # First get the build library for the specified architecture
    estp_get_arch_build_library(ARCH_BUILD_LIB ${ARG_ARCH})
    if(ARCH_BUILD_LIB)
        message(STATUS "Adding test executable ${ARG_NAME} (${ARG_ARCH})")
    else()
        message(STATUS "Skipping test executable ${ARG_NAME} (${ARG_ARCH})")
        return() # Bail out
    endif()

    add_executable(${ARG_NAME} ${ARG_SOURCES})

    # Add private dependencies on architecture-specific library and Catch2 test runner
    target_link_libraries(${ARG_NAME} PRIVATE 
        ${ARCH_BUILD_LIB}
        catch2_test_main-${ARG_ARCH}
    )

    if(ARG_DEFINES)
        target_compile_definitions(${ARG_NAME} ${ARG_DEFINES})
    endif()

    if(ARG_CFLAGS)
        target_compile_options(${ARG_NAME} ${ARG_CFLAGS})
    endif()

    if(ARG_CXXFLAGS)
        estp_target_lang_compile_options(${ARG_NAME} CXX ${ARG_CXXFLAGS})
    endif()

    if(ARG_INCLUDE_DIRS)
        target_include_directories(${ARG_NAME} ${ARG_INCLUDE_DIRS})
    endif()

    if(ARG_LDFLAGS)
        target_link_libraries(${ARG_NAME} ${ARG_LDFLAGS})
    endif()

    if(ARG_LIBRARIES)
        target_link_libraries(${ARG_NAME} ${ARG_LIBRARIES})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

    catch_discover_tests(${ARG_NAME})

endfunction()
