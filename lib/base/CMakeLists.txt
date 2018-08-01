
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