
foreach(ARCH ${ESTP_ARCHS})
    estp_add_static_library(
        NAME
            base-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            assert.cc
        INCLUDE_DIRS PUBLIC
            ${ESTP_ROOT}/lib
    )
endforeach()

foreach(ARCH ${ESTP_HOST_ARCHS})
    estp_add_test_executable(
        NAME
            base_test-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            assert_test.cc
            bits_test.cc
            casting_test.cc
        LIBRARIES PRIVATE
            base-${ARCH}
    )
endforeach()
