CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
include_guard()

function(_estp_add_static_or_object_library LIB_TYPE)
    estp_parse_arguments("${ARGN}"
        VALUE_ARGS
            NAME
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME SOURCES
    )

    message(STATUS "Adding library ${ARG_NAME} (${LIB_TYPE})")

    add_library(${ARG_NAME} ${LIB_TYPE} ${ARG_SOURCES})

    # Add private dependency on architecture-specific library to pull-in build settings
    target_link_libraries(${ARG_NAME} PRIVATE estp_platform)

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

endfunction(_estp_add_static_or_object_library)

# Add an executable with the appropriate dependencies
function(estp_add_executable)
    parse_estp_arguments("${ARGN}"
        VALUE_ARGS
            NAME
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS CXXFLAGS LDFLAGS
            DEPENDENCIES EXTRA_OUTPUTS
        REQUIRED_ARGS
            NAME SOURCES
    )

    message(STATUS "Adding executable ${ARG_NAME}")

    add_executable(${ARG_NAME} ${ARG_SOURCES})

    #get_property(EXE_SUFFIX GLOBAL PROPERTY ESTP_EXECUTABLE_SUFFIX)
    #set_target_properties(${ARG_NAME} PROPERTIES SUFFIX "${EXE_SUFFIX}")

    # Add private dependency on architecture-specific library to pull-in build settings
    target_link_libraries(${ARG_NAME} PRIVATE ${FLAGS_LIB})

    _estp_add_mapfile_output(${ARG_NAME})

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

    target_link_libraries(${ARG_NAME}
        PRIVATE
            estp_platform
            estp_linker_script
    )

    if(ARG_LDFLAGS)
        target_link_libraries(${ARG_NAME} ${ARG_LDFLAGS})
    endif()

    if(ARG_LIBRARIES)
        target_link_libraries(${ARG_NAME} ${ARG_LIBRARIES})
    endif()

    if(ARG_DEPENDENCIES)
        add_dependencies(${ARG_NAME} ${ARG_DEPENDENCIES})
    endif()

    if("BIN" IN_LIST ARG_EXTRA_OUTPUTS)
        _estp_add_bin_output(${ARG_NAME})
    endif()

    if("HEX" IN_LIST ARG_EXTRA_OUTPUTS)
        _estp_add_hex_output(${ARG_NAME})
    endif()

    if("SIZEINFO" IN_LIST ARG_EXTRA_OUTPUTS)
        _estp_add_sizeinfo_output(${ARG_NAME})
    endif()

endfunction() #estp_add_executable

function(estp_add_static_library)
    _estp_add_static_or_object_library(STATIC ${ARGN})
endfunction()

function(estp_add_object_library)
    _estp_add_static_or_object_library(OBJECT ${ARGN})
endfunction()

# Interface libraries are different than static libraries in that interface libraries
# are not required to specify a specific architecture
function(estp_add_interface_library)
    parse_estp_arguments("${ARGN}"
        VALUE_ARGS
            NAME
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME
    )

    message(STATUS "Adding interface library ${ARG_NAME}")

    add_library(${ARG_NAME} INTERFACE)

    if(ARG_SOURCES)
        target_sources(${ARG_NAME} INTERFACE ${ARG_SOURCES})
    endif()

    #target_link_libraries(${ARG_NAME} INTERFACE estp_platform)

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

# A shortcut for adding a set of unit tests
function(estp_add_host_test)
    parse_estp_arguments("${ARGN}"
        VALUE_ARGS
            NAME
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS CXXFLAGS LDFLAGS DEPENDENCIES
        REQUIRED_ARGS
            NAME SOURCES
    )

    if(ESTP_HOST_PLATFORM AND ESTP_BUILD_TESTS)
        message(STATUS "Adding host test executable ${ARG_NAME}")
    else()
        message(STATUS "Skipping host test executable ${ARG_NAME}")
        return()
    endif()

    add_executable(${ARG_NAME} ${ARG_SOURCES})

    # Add private dependencies on platform library and Catch2 test runner
    target_link_libraries(${ARG_NAME} PRIVATE
        estp_platform
        catch2_test_fixture
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