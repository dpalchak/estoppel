
include("${ESTOPPEL_ROOT}/cmake/device/arm_cm4f.cmake")

set(DEVICE_FAMILY "STM32L4")

add_definitions(
	" -DSTM32L4=1"
	" -DDEVICE_FAMILY=${DEVICE_FAMILY}"
)

