
# foreach(ARCH ${ESTP_ARCHS})
#     estp_add_static_library(
#         NAME
#             base-${ARCH}
#         ARCH
#             ${ARCH}
#         SOURCES
#             assert.cc
#         INCLUDE_DIRS PUBLIC
#             ${ESTP_ROOT}
#     )
# endforeach()
add_estp_library(estp_base STATIC
    assert.cc
)

# foreach(ARCH ${ESTP_HOST_ARCHS})
#     estp_add_host_tests(
#         NAME
#             base_test-${ARCH}
#         ARCH
#             ${ARCH}
#         SOURCES
#             assert_test.cc
#             bits_test.cc
#             casting_test.cc
#         LIBRARIES PRIVATE
#             base-${ARCH}
#     )
# endforeach()

if(ESTP_HOST_PLATFORM)
    add_estp_unit_test(estp_base_tests
        assert_test.cc
        bits_test.cc
        casting_test.cc
    )

    target_link_libraries(estp_base_tests PRIVATE
        estp_base
    )
endif()