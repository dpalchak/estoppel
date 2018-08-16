

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
            final_action_test.cc
            meta_list_test.cc
            meta_string_test.cc
            not_null_test.cc
            span_test.cc
        LIBRARIES PRIVATE
            base-${ARCH}
            data-${ARCH}
    )
endforeach()
