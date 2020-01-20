
add_estp_library(estp_data INTERFACE)

if(ESTP_BUILD_TESTING)
    add_estp_unit_test(estp_data_test
        accumulator_test.cc
        atomic_flags_test.cc
        bitfield_test.cc
        final_action_test.cc
        flags_test.cc
        typestring_test.cc
        not_null_test.cc
        span_test.cc
    )

    target_link_libraries(estp_data_test PRIVATE
        estp_base
        estp_data
    )
endif()
