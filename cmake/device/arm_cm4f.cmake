
set(DEVICE_ARCH "ARM_CM4F")

set(DEVICE_ARCH_FLAGS
    " -mcpu=cortex-m4"
    " -mlittle-endian"
    " -mfpu=fpv4-sp-d16"
    " -mfloat-abi=hard"
    " -mthumb"
    " -mthumb-interwork"
    " -mabi=aapcs"
    )

string(APPEND CMAKE_C_FLAGS ${DEVICE_ARCH_FLAGS})
string(APPEND CMAKE_CXX_FLAGS ${DEVICE_ARCH_FLAGS})
string(APPEND CMAKE_ASM_FLAGS ${DEVICE_ARCH_FLAGS})
string(APPEND CMAKE_EXE_LINKER_FLAGS ${DEVICE_ARCH_FLAGS})

add_definitions(
	" -DDEVICE_ARCH=${DEVICE_ARCH}"
)