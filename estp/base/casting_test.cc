#include "estp/base/assert.h"
#include "estp/base/casting.h"
#include "estp/base/types.h"
#include "catch2/catch.hpp"

#include <iostream>
#include <string>
#include <utility>

using namespace estp;

static int assert_count{0};

static void HandleAssertion(AssertionContext const &) {
    ++assert_count;
}

TEST_CASE("narrow() asserts") {
    assert_count = 0;
    SetAssertionHandler(&HandleAssertion);

    SECTION( "narrow() asserts on value truncation" ){
    REQUIRE(0 == assert_count);
        unsigned a = 256;
        uint8_t b = narrow<uint8_t>(a);
        REQUIRE(1 == assert_count);
        REQUIRE(unsigned(b) != a);
    }

    SECTION( "narrow() asserts on overflow" ){
        REQUIRE(0 == assert_count);
        uint8_t a = 128;
        int8_t b = narrow<int8_t>(a);
        REQUIRE(1 == assert_count);
        REQUIRE(int(b) != int(a));
    }
}
