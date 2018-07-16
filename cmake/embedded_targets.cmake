function(add_embedded_executable EXE_TARGET)
    project(exe_target C CXX ASM)

    add_executable(${EXE_TARGET} ${ARGN})

    if ("Debug" STREQUAL ${CMAKE_BUILD_TYPE})
	    set(ELF_FILE_NAME "${EXE_TARGET}-dbg.elf")
    else()
	    set(ELF_FILE_NAME "${EXE_TARGET}-rel.elf")
	endif()
    
	set_target_properties(${EXE_TARGET} PROPERTIES OUTPUT_NAME "${ELF_FILE_NAME}")
	string(REPLACE ".elf" ".map" MAP_FILE_NAME "${ELF_FILE_NAME}")
    string(REPLACE ".elf" ".hex" HEX_FILE_NAME "${ELF_FILE_NAME}")
    string(REPLACE ".elf" ".bin" BIN_FILE_NAME "${ELF_FILE_NAME}")

    # Generate map output file
    target_link_libraries(${EXE_TARGET} PRIVATE
        "-Wl,-Map=${MAP_FILE_NAME}"
    )

    add_custom_command(TARGET ${EXE_TARGET}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${ELF_FILE_NAME} ${BIN_FILE_NAME}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Create binary image: ${BIN_FILE_NAME}"
    )

    add_custom_command(TARGET ${EXE_TARGET}
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${ELF_FILE_NAME} ${HEX_FILE_NAME}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Create ihex image: ${HEX_FILE_NAME}"
    )

    add_custom_command(TARGET ${EXE_TARGET}
        COMMAND ${CMAKE_SIZEINFO} ${ELF_FILE_NAME}
    	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Image size:"
    )

    set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES
        "${MAP_FILE_NAME}"
        "${BIN_FILE_NAME}"
        "${HEX_FILE_NAME}"
    )

    # Set dependent filenames as properties for other operations to use
    set_target_properties(${EXE_TARGET} PROPERTIES
        TARGET_BIN_FILE "${BIN_FILE_NAME}"
        TARGET_HEX_FILE "${HEX_FILE_NAME}"
        TARGET_MAP_FILE "${MAP_FILE_NAME}"
    )

endfunction()

function(enable_pylink_for_target EXE_TARGET)
    estp_parse_args("${ARGN}"
        VALUE_ARGS
            INTERFACE DEVICE FLASH_ADDR
        REQUIRED_ARGS
            DEVICE FLASH_ADDR)

    if(NOT ${PYLINK})
        message(STATUS "PYLINK not defined. Omitting pylink targets...")
        return()
    endif()

    if(NOT EXISTS "${PYLINK}")
        message(WARNING
            "PYLINK not found at specified location: ${PYLINK}\n"
            "Omitting pylink targets..."
        )
        return()
    endif()

    if(NOT ${ARG_INTERFACE})
        set(ARG_INTERFACE "swd")
    endif()

    add_custom_target("flash_${EXE_TARGET}" DEPENDS ${EXE_NAME}
        "${PYLINK} flash -t ${ARG_INTERFACE} -d ${ARG_DEVICE} -a ${ARG_FLASH_ADDR} \
        $<TARGET_PROPERTY:${EXE_TARGET},TARGET_BIN_FILE>"
    )

endfunction()
