CMAKE_MINIMUM_REQUIRED(VERSION 3.13)
include_guard()

function(set_estp_platform_jlink_config PLATFORM JLINK_DEVICE JLINK_INTERFACE JLINK_SPEED)
    set(SOURCES_LIB "${PLATFORM}_platform_sources")
    set_target_properties(${SOURCES_LIB} PROPERTIES
        JLINK_DEVICE "${JLINK_DEVICE}"
        JLINK_INTERFACE "${JLINK_INTERFACE}"
        JLINK_SPEED "${JLINK_SPEED}"
    )
endfunction()

function(add_estp_jlink_targets EXE_TARGET)

    # The Generic system name is used for embedded targets (targets without OS) in Cmake
    string(TOLOWER "${CMAKE_HOST_SYSTEM_NAME}" HOST_SYSTEM_NAME)
    # Set path to J-Link Commander
    set(JLINK_COMMANDER_EXE
        "${ESTP_ROOT}/third_party/segger/jlink/${HOST_SYSTEM_NAME}/latest/JLinkExe"
    )

    if(NOT (EXISTS "${JLINK_COMMANDER_EXE}"))
        message(STATUS
            "Unable to locate J-Link Commander executable: '${JLINK_COMMANDER_EXE}'\n"
            "Skipping J-Link targets for target '${EXE_TARGET}'"
        )
        return()
    endif()

    set(JLINK_GDBSERVER_EXE
        "${ESTP_ROOT}/third_party/segger/jlink/${HOST_SYSTEM_NAME}/latest/JLinkGDBServer"
    )

    set(JLINK_RTTCLIENT_EXE
        "${ESTP_ROOT}/third_party/segger/jlink/${HOST_SYSTEM_NAME}/latest/JLinkRTTClientExe"
    )

    set(PLATFORM_SOURCES_LIB "${ESTP_PLATFORM}_platform_sources")
    get_target_property(JLINK_DEVICE ${PLATFORM_SOURCES_LIB} JLINK_DEVICE)
    if(JLINK_DEVICE MATCHES "NOTFOUND")
        # Platform wasn't configured for J-Link
        message(STATUS
            "Platform '${ESTP_PLATFORM}' does not specify a J-Link configuration. "
            "Skipping J-Link targets for target '${EXE_TARGET}'"
        )
        return()
    endif()

    get_target_property(JLINK_INTERFACE ${PLATFORM_SOURCES_LIB} JLINK_INTERFACE)
    get_target_property(JLINK_SPEED ${PLATFORM_SOURCES_LIB} JLINK_SPEED)

    set(FIRMWARE_HEXFILE "${EXE_TARGET}.hex")

    message(STATUS "Adding J-Link targets for '${EXE_TARGET}'")
    set(WRAPPER_SCRIPT_TEMPLATE "${ESTP_ROOT}/tools/jlink/jlink.sh.in")
    set(WRAPPER_SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/jlink.sh")

    configure_file(
        "${WRAPPER_SCRIPT_TEMPLATE}"
        "${WRAPPER_SCRIPT}"
        @ONLY NEWLINE_STYLE UNIX
    )

    add_custom_command(TARGET ${EXE_TARGET} POST_BUILD
        COMMAND chmod +x "${WRAPPER_SCRIPT}"
    )

    foreach(CMD reset erase load)
        add_custom_target(${CMD} ${WRAPPER_SCRIPT} ${CMD} USES_TERMINAL)
        add_dependencies(${CMD} ${EXE_TARGET})
    endforeach()
endfunction(add_estp_jlink_targets)
