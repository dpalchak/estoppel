
function(add_pylink_commands_for_target TARGET_NAME)
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
        message(WARNING "PYLINK not found at specified location: ${PYLINK}\nOmitting pylink targets...")
        return()
    endif()

    if(NOT ${ARG_INTERFACE})
        set(${ARG_INTERFACE} "swd")
    endif()

    add_custom_target("erase"
        "${PYLINK} erase -t ${ARG_INTERFACE} -d ${ARG_DEVICE}")

    add_custom_target("flash_${TARGET_NAME}"
        "${PYLINK} flash -t ${ARG_INTERFACE} -d ${ARG_DEVICE} -a ${ARG_FLASH_ADDR} ${CMAKE_BINARY_DIR}/${TARGET_NAME}.bin"
        DEPENDS ${TARGET_NAME})

endfunction()