function(add_embedded_executable EXE_TARGET)

    add_executable(${EXE_TARGET} ${ARGN})

    # Configure path to and name of generated artifacts
    set_target_properties(${EXE_TARGET} PROPERTIES
    	DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}"
    	RELEASE_POSTFIX "${CMAKE_RELEASE_POSTFIX}"
    	MINSIZEREL_POSTFIX "${CMAKE_MINSIZEREL_POSTFIX}"
    	RELWITHDEBINFO_POSTFIX "${CMAKE_RELWITHDEBINFO_POSTFIX}"
	)

	set(ELF_FILE_NAME $<TARGET_FILE:${EXE_TARGET}>)
  	string(REPLACE ".elf" ".map" MAP_FILE_NAME "${ELF_FILE_NAME}")
	string(REPLACE ".elf" ".hex" HEX_FILE_NAME "${ELF_FILE_NAME}")
	string(REPLACE ".elf" ".bin" BIN_FILE_NAME "${ELF_FILE_NAME}")

    # Generate map output file
    target_link_libraries(${EXE_TARGET} PRIVATE
    	" -Wl,-Map=${MAP_FILE_NAME}"
	)

    add_custom_command(TARGET_NAME ${EXE_TARGET}
        COMMAND "${CMAKE_OBJCOPY} -O binary ${ELF_FILE_NAME} ${BIN_FILE_NAME}"
        COMMENT "Create binary image: ${BIN_FILE_NAME}"
    )

    add_custom_command(TARGET ${EXE_TARGET}
        COMMAND "${CMAKE_OBJCOPY} -O ihex ${ELF_FILE_NAME} ${HEX_FILE_NAME}"
        COMMENT "Create ihex image: ${HEX_FILE_NAME}"
    )

    add_custom_command(TARGET ${EXE_TARGET}
        COMMAND "${CMAKE_SIZEINFO} ${ELF_FILE_NAME}"
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