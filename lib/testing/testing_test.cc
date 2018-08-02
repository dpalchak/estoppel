
#include "catch2/catch.hpp"

// A trivial collection of test cases to test whether the Catch2 test framework
// is correctly configured and building properly

int next(int const i) {
	return i+1;
}

int previous(int const i) {
	return i-1;
}

TEST_CASE( "Catch2 is working correctly", "[catch2]" ) {

	int i = 0;
    REQUIRE( 0 == i );

    SECTION( "Increment integers" ) {
        i = next(i);
        REQUIRE( 1 == i );
    }
    SECTION( "Decrement integers" ) {
    	i = previous(previous(previous(i)));
        REQUIRE( -3 == i );
    }
}
