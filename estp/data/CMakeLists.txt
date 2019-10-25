

# foreach(ARCH ${ESTP_ARCHS})
#     estp_add_interface_library(
#         NAME
#             data-${ARCH}
#         ARCH
#             ${ARCH}
#         INCLUDE_DIRS
#             ${ESTP_ROOT}/lib
#     )
# endforeach()
add_estp_library(estp_data INTERFACE)

# foreach(ARCH ${ESTP_HOST_ARCHS})
#     estp_add_host_tests(
#         NAME
#             libdata_test-${ARCH}
#         ARCH
#             ${ARCH}
#         SOURCES
#             final_action_test.cc
#             meta_list_test.cc
#             meta_string_test.cc
#             not_null_test.cc
#             span_test.cc
#         LIBRARIES PRIVATE
#             base-${ARCH}
#             data-${ARCH}
#     )
# endforeach()

if(ESTP_HOST_PLATFORM)
    add_estp_unit_test(estp_data_test
        final_action_test.cc
        meta_list_test.cc
        meta_string_test.cc
        not_null_test.cc
        span_test.cc
    )

    target_link_libraries(estp_data_test PRIVATE
        estp_base
        estp_data
    )
endif()
