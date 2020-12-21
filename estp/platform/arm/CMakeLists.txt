
# ARM Cortex-M4F
set(ARMCM4F_ARCH_FLAGS
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

# ARM Cortex-M4 (no FPU)
set(ARMCM4_ARCH_FLAGS
    "-mcpu=cortex-m4"
    "-mlittle-endian"
    "-mfloat-abi=soft"
    "-mthumb"
    "-mthumb-interwork"
    "-mabi=aapcs"
)

# ARM Cortex-M3
set(ARMCM3_ARCH_FLAGS
   "-mcpu=cortex-m3"
   "-mlittle-endian"
   "-mfloat-abi=soft"
   "-mthumb"
   "-mthumb-interwork"
   "-mabi=aapcs"
)

# ARM Cortex-M0
set(ARMCM0P_ARCH_FLAGS
   "-mcpu=cortex-m0plus"
   "-mlittle-endian"
   "-mfloat-abi=soft"
   "-mthumb"
   "-mthumb-interwork"
   "-mabi=aapcs"
)

foreach(ARCH armcm4f armcm4 armcm3 armcm0p)
    string(TOUPPER ${ARCH} uARCH)

    add_estp_platform_libraries(${ARCH})

    target_compile_options(${ARCH}_platform_build INTERFACE
        ${${uARCH}_ARCH_FLAGS}
    )

    target_link_options(${ARCH}_platform_build INTERFACE
        ${${uARCH}_ARCH_FLAGS}
    )

    target_link_options(${ARCH}_platform_build INTERFACE
        "-L${CMAKE_CURRENT_LIST_DIR}"
    )

    target_link_options(${ARCH}_platform_link INTERFACE
        -nostartfiles
    )
endforeach()


target_sources(armcm4f_platform_sources PRIVATE
    reset_handler.cc
    armv7m_vector_table.cc
)

target_sources(armcm4_platform_sources PRIVATE
    reset_handler.cc
    armv7m_vector_table.cc
)

target_sources(armcm3_platform_sources PRIVATE
    reset_handler.cc
    armv7m_vector_table.cc
)

#target_sources(armcm0p_platform_sources PRIVATE
#    reset_handler.cc
#    armv6m_vector_table.cc
#)
