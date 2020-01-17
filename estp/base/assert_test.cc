#define ESTP_ASSERT_BASENAME 1

#include "estp/base/assert.hh"
#include "catch2/catch.hpp"

#include <iostream>
#include <string>

using namespace estp;
using namespace std;

static AssertionContext last_assertion{};

void TestHandler(AssertionContext const &f) {
	last_assertion = f;
}

void ClearLastAssertion() {
	last_assertion = AssertionContext{};
}

TEST_CASE( "Get and set ASSERT handler", "[assert]" ) {
	ClearLastAssertion();

    SECTION( "Get default handler" ) {
        auto h = GetAssertionHandler();
        REQUIRE( nullptr == h );
    }

    SECTION( "Set handler to valid function" ) {
    	auto h = SetAssertionHandler(&TestHandler);
        REQUIRE( nullptr == h );
        REQUIRE(&TestHandler == GetAssertionHandler());
    }

    SECTION( "Set handler to nothing" ) {
        auto h = SetAssertionHandler(nullptr);
        REQUIRE(&TestHandler == h);
        REQUIRE(nullptr == GetAssertionHandler());
    }
}

TEST_CASE( "Assertions handled by user-assigned handler" ) {

	ClearLastAssertion();
	SetAssertionHandler(TestHandler);

	REQUIRE(0 == last_assertion.line);
	REQUIRE('\0' == last_assertion.filename[0]);

	SECTION( "Call ASSERT" ) {
		Index line = __LINE__;
		ASSERT(false);

		REQUIRE(string(last_assertion.condition) == "false");
		REQUIRE(string(last_assertion.filename) == "assert_test.cc");
		REQUIRE(line+1 == last_assertion.line);
	}

	SECTION( "Call ASSERT again" ) {
		Index line = __LINE__;
		ASSERT(0 == 1);

		REQUIRE(string(last_assertion.condition) == "0 == 1");
		REQUIRE(string(last_assertion.filename) == "assert_test.cc");
		REQUIRE(line+1 == last_assertion.line);
	}

	SECTION( "Call ASSERT with commas" ) {
		Index line = __LINE__;
		ASSERT(((void)3,4) == 2);

		REQUIRE(string(last_assertion.condition) == "((void)3,4) == 2");
		REQUIRE(string(last_assertion.filename) == "assert_test.cc");
		REQUIRE(line+1 == last_assertion.line);
	}
}
