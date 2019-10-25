
add_device_subdirectory(arm)
add_device_subdirectory(stm32l4)

string(TOLOWER "${CMAKE_HOST_SYSTEM_NAME}" HOST_SYSTEM_NAME)
add_host_subdirectory(${HOST_SYSTEM_NAME})
