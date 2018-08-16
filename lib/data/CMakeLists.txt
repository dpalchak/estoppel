

foreach(ARCH ${ESTP_ARCHS})
    estp_add_interface_library(
        NAME
            data-${ARCH}
        ARCH
            ${ARCH}
        INCLUDE_DIRS
            ${ESTP_ROOT}/lib
    )
endforeach()

foreach(ARCH ${ESTP_HOST_ARCHS})
    estp_add_test_executable(
        NAME
            libdata_test-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            meta_list_test.cc
            meta_string_test.cc
            final_action_test.cc
        LIBRARIES PRIVATE
            data-${ARCH}
    )
endforeach()
