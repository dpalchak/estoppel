
#TODO(palchak): setup as unit test
foreach(ARCH host host32 armcm4f)
    estp_add_static_library(
        NAME
            data_test-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            meta_list_test.cc
        INCLUDE_DIRS PUBLIC
            ${ESTP_ROOT}/lib
    )
endforeach()
