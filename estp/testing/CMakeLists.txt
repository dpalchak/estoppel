
add_estp_library(catch2_test_fixture STATIC
    catch2_test_fixture.cc
)

target_link_libraries(catch2_test_fixture PUBLIC
    Catch2::Catch2
)

# Add a very simple test just to confirm our test fixture is building correctly
add_estp_unit_test(test_fixture_test
    testing_test.cc
)
