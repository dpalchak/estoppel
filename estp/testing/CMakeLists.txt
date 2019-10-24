
foreach(ARCH ${ESTP_HOST_ARCHS})
    estp_add_static_library(
        NAME
            catch2_test_main-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            catch2_test_main.cc
        LIBRARIES PUBLIC
            Catch2::Catch2
    )
    
    estp_add_test_executable(
        NAME
            testing_test-${ARCH}
        ARCH
            ${ARCH}
        SOURCES
            testing_test.cc
    )
endforeach()
