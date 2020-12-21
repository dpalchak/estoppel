
include("${ESTP_ROOT}/cmake/estp_jlink.cmake")

function(get_nrf5_sdk_root VAR_NAME)
    set("${VAR_NAME}" "${ESTP_ROOT}/third_party/nordic/nrf5_sdk/latest" PARENT_SCOPE)
endfunction()

get_nrf5_sdk_root(NRF5_SDK_ROOT)
message(STATUS "Using NRF5 SDK: '${NRF5_SDK_ROOT}'")

add_library(nrf5_sdk_warnings_hack INTERFACE)

target_compile_options(nrf5_sdk_warnings_hack INTERFACE
    "-Wno-conversion"
    "-Wno-undef"
    "-Wno-sign-conversion"
    "-Wno-expansion-to-defined"
    "-Wno-unused-parameter"
    "-Wno-switch-default"
    "-Wno-switch-enum"
    "-Wno-missing-field-initializers"
    $<$<COMPILE_LANGUAGE:C>:-Wno-discarded-qualifiers>
)

add_estp_platform_libraries(nrf52_common EXTENDS armcm4f)

target_link_libraries(nrf52_common_platform_link INTERFACE
    "-L${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(nrf52_common_platform_build INTERFACE
    ${NRF5_SDK_ROOT}/components
    ${NRF5_SDK_ROOT}/components/boards
    ${NRF5_SDK_ROOT}/components/libraries/atomic
    ${NRF5_SDK_ROOT}/components/libraries/atomic_fifo
    ${NRF5_SDK_ROOT}/components/libraries/atomic_flags
    ${NRF5_SDK_ROOT}/components/libraries/balloc
    ${NRF5_SDK_ROOT}/components/libraries/bootloader/ble_dfu
    ${NRF5_SDK_ROOT}/components/libraries/bsp
    ${NRF5_SDK_ROOT}/components/libraries/button
    ${NRF5_SDK_ROOT}/components/libraries/cli
    ${NRF5_SDK_ROOT}/components/libraries/crc16
    ${NRF5_SDK_ROOT}/components/libraries/crc32
    ${NRF5_SDK_ROOT}/components/libraries/crypto
    ${NRF5_SDK_ROOT}/components/libraries/csense
    ${NRF5_SDK_ROOT}/components/libraries/csense_drv
    ${NRF5_SDK_ROOT}/components/libraries/delay
    ${NRF5_SDK_ROOT}/components/libraries/ecc
    ${NRF5_SDK_ROOT}/components/libraries/experimental_section_vars
    ${NRF5_SDK_ROOT}/components/libraries/experimental_task_manager
    ${NRF5_SDK_ROOT}/components/libraries/fds
    ${NRF5_SDK_ROOT}/components/libraries/fstorage
    ${NRF5_SDK_ROOT}/components/libraries/gfx
    ${NRF5_SDK_ROOT}/components/libraries/gpiote
    ${NRF5_SDK_ROOT}/components/libraries/hardfault
    ${NRF5_SDK_ROOT}/components/libraries/hci
    ${NRF5_SDK_ROOT}/components/libraries/led_softblink
    ${NRF5_SDK_ROOT}/components/libraries/log
    ${NRF5_SDK_ROOT}/components/libraries/log/src
    ${NRF5_SDK_ROOT}/components/libraries/low_power_pwm
    ${NRF5_SDK_ROOT}/components/libraries/mem_manager
    ${NRF5_SDK_ROOT}/components/libraries/memobj
    ${NRF5_SDK_ROOT}/components/libraries/mpu
    ${NRF5_SDK_ROOT}/components/libraries/mutex
    ${NRF5_SDK_ROOT}/components/libraries/pwm
    ${NRF5_SDK_ROOT}/components/libraries/pwr_mgmt
    ${NRF5_SDK_ROOT}/components/libraries/queue
    ${NRF5_SDK_ROOT}/components/libraries/ringbuf
    ${NRF5_SDK_ROOT}/components/libraries/scheduler
    ${NRF5_SDK_ROOT}/components/libraries/sdcard
    ${NRF5_SDK_ROOT}/components/libraries/slip
    ${NRF5_SDK_ROOT}/components/libraries/sortlist
    ${NRF5_SDK_ROOT}/components/libraries/spi_mngr
    ${NRF5_SDK_ROOT}/components/libraries/stack_guard
    ${NRF5_SDK_ROOT}/components/libraries/strerror
    ${NRF5_SDK_ROOT}/components/libraries/svc
    ${NRF5_SDK_ROOT}/components/libraries/timer
    ${NRF5_SDK_ROOT}/components/libraries/twi_mngr
    ${NRF5_SDK_ROOT}/components/libraries/twi_sensor
    ${NRF5_SDK_ROOT}/components/libraries/usbd
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/audio
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/cdc
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/cdc/acm
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/hid
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/hid/generic
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/hid/kbd
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/hid/mouse
    ${NRF5_SDK_ROOT}/components/libraries/usbd/class/msc
    ${NRF5_SDK_ROOT}/components/libraries/util
    ${NRF5_SDK_ROOT}/components/nfc/ndef/conn_hand_parser
    ${NRF5_SDK_ROOT}/components/nfc/ndef/conn_hand_parser/ac_rec_parser
    ${NRF5_SDK_ROOT}/components/nfc/ndef/conn_hand_parser/ble_oob_advdata_parser
    ${NRF5_SDK_ROOT}/components/nfc/ndef/conn_hand_parser/le_oob_rec_parser
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/ac_rec
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/ble_oob_advdata
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/ble_pair_lib
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/ble_pair_msg
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/common
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/ep_oob_rec
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/hs_rec
    ${NRF5_SDK_ROOT}/components/nfc/ndef/connection_handover/le_oob_rec
    ${NRF5_SDK_ROOT}/components/nfc/ndef/generic/message
    ${NRF5_SDK_ROOT}/components/nfc/ndef/generic/record
    ${NRF5_SDK_ROOT}/components/nfc/ndef/launchapp
    ${NRF5_SDK_ROOT}/components/nfc/ndef/parser/message
    ${NRF5_SDK_ROOT}/components/nfc/ndef/parser/record
    ${NRF5_SDK_ROOT}/components/nfc/ndef/text
    ${NRF5_SDK_ROOT}/components/nfc/ndef/uri
    ${NRF5_SDK_ROOT}/components/nfc/platform
    ${NRF5_SDK_ROOT}/components/nfc/t2t_lib
    ${NRF5_SDK_ROOT}/components/nfc/t2t_parser
    ${NRF5_SDK_ROOT}/components/nfc/t4t_lib
    ${NRF5_SDK_ROOT}/components/nfc/t4t_parser/apdu
    ${NRF5_SDK_ROOT}/components/nfc/t4t_parser/cc_file
    ${NRF5_SDK_ROOT}/components/nfc/t4t_parser/hl_detection_procedure
    ${NRF5_SDK_ROOT}/components/nfc/t4t_parser/tlv
    ${NRF5_SDK_ROOT}/components/toolchain/cmsis/include
    ${NRF5_SDK_ROOT}/external/fprintf
    ${NRF5_SDK_ROOT}/external/segger_rtt
    ${NRF5_SDK_ROOT}/external/utf_converter
    ${NRF5_SDK_ROOT}/integration/nrfx
    ${NRF5_SDK_ROOT}/integration/nrfx/legacy
    ${NRF5_SDK_ROOT}/modules/nrfx
    ${NRF5_SDK_ROOT}/modules/nrfx/drivers/include
    ${NRF5_SDK_ROOT}/modules/nrfx/hal
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk
)


target_compile_definitions(nrf52_common_platform_build INTERFACE
    "FLOAT_ABI_HARD"
    "NRF52"
    "APP_TIMER_V2"
    "NRF52_PAN_74"
)

target_compile_options(nrf52_common_platform_build INTERFACE
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

target_link_options(nrf52_common_platform_build INTERFACE
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

target_sources(nrf52_common_platform_sources PRIVATE
    #${NRF5_SDK_ROOT}/modules/nrfx/mdk/gcc_startup_nrf52.S
    nrf52_vector_table.cc
    ${NRF5_SDK_ROOT}/modules/nrfx/mdk/system_nrf52.c
)

add_estp_platform_libraries(nrf52_nosd EXTENDS nrf52_common)

target_include_directories(nrf52_nosd_platform_build INTERFACE
    ${NRF5_SDK_ROOT}/components/drivers_nrf/nrf_soc_nosd
)

target_link_libraries(nrf52_nosd_platform_sources PRIVATE
    nrf5_sdk_warnings_hack
)


add_estp_platform_libraries(nrf52_s132 EXTENDS nrf52_common)

target_compile_definitions(nrf52_s132_platform_build INTERFACE
    "SOFTDEVICE_PRESENT"
    "NRF_SD_BLE_API_VERSION=7"
    "S132"
)

target_include_directories(nrf52_s132_platform_build INTERFACE
    ${NRF5_SDK_ROOT}/components/ble/ble_advertising
    ${NRF5_SDK_ROOT}/components/ble/ble_dtm
    ${NRF5_SDK_ROOT}/components/ble/ble_racp
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_ancs_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_ans_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_bas
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_bas_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_cscs
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_cts_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_dfu
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_dis
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_gls
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_hids
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_hrs
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_hrs_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_hts
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_ias
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_ias_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_lbs
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_lbs_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_lls
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_nus
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_nus_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_rscs
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_rscs_c
    ${NRF5_SDK_ROOT}/components/ble/ble_services/ble_tps
    ${NRF5_SDK_ROOT}/components/ble/common
    ${NRF5_SDK_ROOT}/components/ble/nrf_ble_gatt
    ${NRF5_SDK_ROOT}/components/ble/nrf_ble_qwr
    ${NRF5_SDK_ROOT}/components/ble/peer_manager
    ${NRF5_SDK_ROOT}/components/softdevice/common
    ${NRF5_SDK_ROOT}/components/softdevice/s132/headers
    ${NRF5_SDK_ROOT}/components/softdevice/s132/headers/nrf52
)


add_estp_platform_libraries(nrf52dk_nosd EXTENDS nrf52_nosd)

target_compile_definitions(nrf52dk_nosd_platform_build INTERFACE
    "NRF52832_XXAA"
    "BOARD_PCA10040"
)

target_link_libraries(nrf52dk_nosd_platform_sources PRIVATE
    nrf5_sdk_warnings_hack
)

# TODO(palchak): wrap this in a function that provides a means to
# configure link script options

# Use the C preprocessor to generate a linker script
add_custom_command(
    OUTPUT "nrf52832_xxaa_nosd.ld"
    COMMAND
        ${CMAKE_CPP} -P -CC
        "${CMAKE_CURRENT_SOURCE_DIR}/nrf52.ld.in"
        -o "nrf52832_xxaa_nosd.ld"
        "-DMEMORY_LDI_FILE=\"nrf52832_xxaa_nosd_memory.ldi\""
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/nrf52.ld.in"
    COMMENT "Generating NRF52_XXAA_NOSD linker script"
    VERBATIM
)

# Create a custom target that generates a linker script
add_custom_target(gen_nrf52_xxaa_nosd_link_script DEPENDS "nrf52832_xxaa_nosd.ld")

add_dependencies(nrf52dk_nosd_platform_link gen_nrf52_xxaa_nosd_link_script)

target_link_libraries(nrf52dk_nosd_platform_link INTERFACE
    "-T${CMAKE_CURRENT_BINARY_DIR}/nrf52832_xxaa_nosd.ld"
)

set_estp_platform_jlink_config(nrf52dk_nosd NRF52832_XXAA SWD 4000)



add_estp_platform_libraries(nrf52dk_s132 EXTENDS nrf52_s132)

target_compile_definitions(nrf52dk_s132_platform_build INTERFACE
    "NRF52832_XXAA"
    "BOARD_PCA10040"
)

target_link_libraries(nrf52dk_s132_platform_sources PRIVATE
    nrf5_sdk_warnings_hack
)

# Use the C preprocessor to generate a linker script
add_custom_command(
    OUTPUT "nrf52832_xxaa_s132.ld"
    COMMAND
        ${CMAKE_CPP} -P -CC
        "${CMAKE_CURRENT_SOURCE_DIR}/nrf52.ld.in"
        -o "nrf52832_xxaa_s132.ld"
        "-DMEMORY_LDI_FILE=\"nrf52832_xxaa_s132_memory.ldi\""
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/nrf52.ld.in"
    COMMENT "Generating NRF52_XXAA_NOSD linker script"
    VERBATIM
)

# Create a custom target that generates a linker script
add_custom_target(gen_nrf52_xxaa_s132_link_script DEPENDS "nrf52832_xxaa_s132.ld")

add_dependencies(nrf52dk_s132_platform_link gen_nrf52_xxaa_s132_link_script)

target_link_libraries(nrf52dk_s132_platform_link INTERFACE
    "-T${CMAKE_CURRENT_BINARY_DIR}/nrf52832_xxaa_s132.ld"
)

set_estp_platform_jlink_config(nrf52dk_s132 NRF52832_XXAA SWD 4000)
