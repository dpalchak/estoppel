#undef ESTP_ASSERT_FULL_NAME

#include "base/assert.h"
#include "catch2/catch.hpp"

#include <iostream>
#include <string>

using namespace estp;
using namespace std;

static FailedAssertion last_assertion{};

void TestHandler(FailedAssertion const &f) {
	last_assertion = f;
}

void ClearLastAssertion() {
	last_assertion = FailedAssertion{};
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

    SECTION( "Set handler to nulltpr" ) {
        auto h = SetAssertionHandler(nullptr);
        REQUIRE(&TestHandler == h);
        REQUIRE(nullptr == GetAssertionHandler());
    }
}

TEST_CASE( "Assertions handled by user-assigned handler" ) {

	ClearLastAssertion();
	SetAssertionHandler(TestHandler);

	REQUIRE(0 == last_assertion.line);
	REQUIRE(nullptr == last_assertion.context);
	REQUIRE('\0' == last_assertion.filename[0]);

	SECTION( "Call ASSERT" ) {
		int line = __LINE__;
		ASSERT(false);

		REQUIRE(string{last_assertion.filename} == "assert_test.cc");
		REQUIRE(line+1 == last_assertion.line);
		REQUIRE(nullptr == last_assertion.context);
	}

	SECTION( "Call ASSERT again" ) {
		int line = __LINE__;
		ASSERT(false);

		REQUIRE(string{last_assertion.filename} == "assert_test.cc");
		REQUIRE(line+1 == last_assertion.line);
		REQUIRE(nullptr == last_assertion.context);
	}

	SECTION( "Call ASSERT_LOG" ) {
		char const *log_message = "BOOM! goes the dynamite";
		ASSERT_LOG(false, log_message);

		REQUIRE(log_message == last_assertion.context);
	}
}
