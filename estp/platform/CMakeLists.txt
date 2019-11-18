
add_device_subdirectory(arm EXCLUDE_FROM_ALL)
add_device_subdirectory(nrf52 EXCLUDE_FROM_ALL)
add_device_subdirectory(stm32l4 EXCLUDE_FROM_ALL)

string(TOLOWER "${CMAKE_HOST_SYSTEM_NAME}" HOST_SYSTEM_NAME)
add_host_subdirectory(${HOST_SYSTEM_NAME} EXCLUDE_FROM_ALL)
