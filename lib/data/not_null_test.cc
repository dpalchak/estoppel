#include "base/assert.h"
#include "base/types.h"
#include "data/not_null.h"

#include "catch2/catch.hpp"

#include <iostream>
#include <string>
#include <utility>

using namespace estp;

static int assert_count{0};

static void HandleAssertion(AssertionContext const &) {
    ++assert_count;
}


TEST_CASE("NotNull<T> ctor") {
    assert_count = 0;
    SetAssertionHandler(&HandleAssertion);

    SECTION( "Construction" ){
        int a = 42;
        NotNull aa{&a};
        REQUIRE(0 == assert_count);
    }

    SECTION( "Construction asserts for nullptr" ){
        int b = 42;
        NotNull<int*> bb{(int*)0};
        REQUIRE(1 == assert_count);

        int *c = (!b) ? &b : nullptr;
        NotNull cc{c};
        REQUIRE(2 == assert_count);
    }
}

TEST_CASE("NotNull<T> get()") {
	int d = 42;
	NotNull dd{&d};

	REQUIRE(dd.get() == &d);
	REQUIRE(42 == *dd);
	REQUIRE(static_cast<int*>(dd) == &d);
}
