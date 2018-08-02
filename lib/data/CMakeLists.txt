
#TODO(palchak): setup as unit test executable
foreach(ARCH ${ESTP_ARCHS})
    estp_add_static_library(
        NAME
            data_test-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            meta_list_test.cc
            meta_string_test.cc
        INCLUDE_DIRS PUBLIC
            ${ESTP_ROOT}/lib
    )
endforeach()
