
if(NOT ${ARCH} STREQUAL "ARM_CM4F")
    return()
endif()

add_embedded_executable(cm4f_sandbox
	main.cc
)

target_link_libraries(cm4f_sandbox PRIVATE
    stm32l4_sdk_hal
	stm32l4x6xg	 
)

