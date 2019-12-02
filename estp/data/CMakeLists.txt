
add_estp_library(estp_data INTERFACE)

if(ESTP_HOST_PLATFORM)
    add_estp_unit_test(estp_data_test
        accumulator_test.cc
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
