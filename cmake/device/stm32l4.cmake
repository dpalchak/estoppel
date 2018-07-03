
include("${ESTOPPEL_ROOT}/cmake/device/cortex_m4f.cmake")

set(DEVICE_FAMILY "stm32l4")

add_definitions(
	"-DSTM32L4=1 "
	"-DDEVICE_FAMILY=${DEVICE_FAMILY} ")

