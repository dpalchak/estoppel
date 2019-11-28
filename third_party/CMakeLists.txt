
project(estoppel_third_party)

add_device_subdirectory("st/stm32l4_sdk/latest" EXCLUDE_FROM_ALL)
add_subdirectory("expected-lite")
add_subdirectory("catch2" EXCLUDE_FROM_ALL)
