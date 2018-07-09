
set(CMAKE_SYSTEM_PROCESSOR STM32L486JG)

include("${ESTOPPEL_ROOT}/cmake/device/stm32l4.cmake")

set(DEVICE_VARIANT "STM32L486JG")

add_definitions(
	" -DSTM32L486=1"
	" -DSTM32L486JG=1"
	" -DDEVICE_VARIANT=${DEVICE_VARIANT}"
)

