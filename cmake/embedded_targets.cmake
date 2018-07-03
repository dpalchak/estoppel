
function(estp_embedded_executable EXE_NAME)
    estp_parse_args("${ARGN}"
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS
        REQUIRED_ARGS
            SOURCES)

    project(${EXE_NAME} C CXX ASM)
    
    add_executable(${EXE_NAME} ${ARG_SOURCES})

    target_include_directories(${EXE_NAME} PRIVATE ${ARG_INCLUDE_DIRS})

	target_compile_definitions(${EXE_NAME} PRIVATE ${ARG_DEFINES})

    target_compile_options(${EXE_NAME}, PRIVATE ${ARG_CFLAGS})

	target_link_libraries(${EXE_NAME} PRIVATE ${ARG_LDFLAGS})
	
    target_link_libraries(${EXE_NAME} PRIVATE
        ${ESTP_LINK_LIBRARIES_PREFIX}
        ${ARG_LIBRARIES}
        ${ESTP_LINK_LIBRARIES_SUFFIX})

    add_custom_command(TARGET ${EXE_NAME}
        COMMAND "cp ${EXE_NAME} ${CMAKE_BINARY_DIR}/${EXE_NAME}.elf"
        COMMENT "Rename: ${EXE_NAME} -> ${EXE_NAME}.elf")

    add_custom_command(TARGET ${EXE_NAME}
        COMMAND "${CMAKE_OBJCOPY} -O binary ${CMAKE_BINARY_DIR}/${EXE_NAME}.elf ${CMAKE_BINARY_DIR}/${EXE_NAME}.bin"
        COMMENT "Create binary image: ${EXE_NAME}.elf -> ${EXE_NAME}.bin")

    add_custom_command(TARGET ${EXE_NAME}
        COMMAND "${CMAKE_OBJCOPY} -O ihex ${CMAKE_BINARY_DIR}/${EXE_NAME}.elf ${CMAKE_BINARY_DIR}/${EXE_NAME}.hex"
        COMMENT "Create ihex image: ${EXE_NAME}.elf -> ${EXE_NAME}.hex")

    add_custom_command(TARGET ${EXE_NAME}
        COMMAND "${CMAKE_SIZEINFO} ${CMAKE_BINARY_DIR}/${EXE_NAME}.elf"
        COMMENT "Image size:")

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
        ${CMAKE_BINARY_DIR}/${EXE_NAME}.elf
        ${CMAKE_BINARY_DIR}/${EXE_NAME}.bin
        ${CMAKE_BINARY_DIR}/${EXE_NAME}.hex)

endfunction()


function(estp_embedded_library LIB_NAME)
    estp_parse_args("${ARGN}"
        LIST_ARGS
            SOURCES  
            LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS
            PUBLIC_LIBRARIES PUBLIC_INCLUDE_DIRS PUBLIC_DEFINES PUBLIC_CFLAGS PUBLIC_LDFLAGS
        REQUIRED_ARGS
            SOURCES)

    project(${LIB_NAME} C CXX ASM)
    add_library(${LIB_NAME} STATIC ${ARG_SOURCES)
    
    target_include_directories(${LIB_NAME} PRIVATE ${ARG_INCLUDE_DIRS})
    target_include_directories(${LIB_NAME} PUBLIC ${ARG_PUBLIC_INCLUDE_DIRS})
    
    target_compile_definitions(${LIB_NAME} PRIVATE ${ARG_DEFINES})
    target_compile_definitions(${LIB_NAME} PUBLIC ${ARG_PUBLIC_DEFINES})

    target_compile_options(${LIB_NAME} PRIVATE ${ARG_CFLAGS})
    target_compile_options(${LIB_NAME} PUBLIC ${ARG_PUBLIC_CFLAGS})
    
    target_link_libraries(${LIB_NAME} PRIVATE ${ARG_LIBRARIES} ${ARG_LDFLAGS})
    target_link_libraries(${LIB_NAME} PUBLIC ${ARG_PUBLIC_LDFLAGS})
    
    target_link_libraries(${LIB_NAME} PRIVATE
        ${ESTP_LINK_LIBRARIES_PREFIX}
        ${ARG_LIBRARIES}
        ${ESTP_LINK_LIBRARIES_SUFFIX})
    
    target_link_libraries(${LIB_NAME} PUBLIC
        ${ESTP_LINK_LIBRARIES_PREFIX}
        ${ARG_PUBLIC_LIBRARIES}
        ${ESTP_LINK_LIBRARIES_SUFFIX})

endfunction()

function(estp_interface_library LIB_NAME)
    estp_parse_args("${ARGN}"
        LIST_ARGS
            SOURCES LIBRARIES INCLUDE_DIRS DEFINES CFLAGS LDFLAGS)

    project(${LIB_NAME} C CXX ASM)
    # This is an interface library, which means that all sources and include directories are INTERFACE
    add_library(${LIB_NAME} INTERFACE)
    target_sources(${LIB_NAME} INTERFACE ${ARG_SOURCES})
    target_include_directories(${LIB_NAME} INTERFACE ${ARG_INCLUDE_DIRS})
	target_compile_definitions(${LIB_NAME} INTERFACE ${ARG_DEFINES})
    target_compile_options(${LIB_NAME} INTERFACE ${ARG_CFLAGS})  
    target_link_libraries(${LIB_NAME} INTERFACE ${ARG_LDFLAGS})    
    target_link_libraries(${LIB_NAME} INTERFACE
        ${ESTP_LINK_LIBRARIES_PREFIX}
        ${ARG_LIBRARIES}
        ${ESTP_LINK_LIBRARIES_SUFFIX})
endfunction()
    
    
    