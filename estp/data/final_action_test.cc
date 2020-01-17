#include "estp/data/final_action.hh"
#include "catch2/catch.hpp"

#include <iostream>
#include <string>
#include <utility>

using namespace estp;

static int obj{0};

static void SetObjToFive() {
	obj = 5;
}

TEST_CASE("FinalAction fires") {
	obj = 0;

    SECTION( "FinalAction calls lambda function" ) {
    	REQUIRE(0 == obj);
    	{
    		auto act = FinalAction{[](){ obj = 1; }};
    	}
        REQUIRE(1 == obj);
    }

    SECTION( "finally() calls lambda function" ) {
    	REQUIRE(0 == obj);
    	{
    		auto act = finally( [](){ obj = 1; } );
    	}
        REQUIRE(1 == obj);
    }

    SECTION( "FinalAction calls static function" ) {
    	REQUIRE(0 == obj);
    	{
    		auto act = FinalAction{&SetObjToFive};
    	}
        REQUIRE(5 == obj);
    }

    SECTION( "finally() calls static function" ) {
    	REQUIRE(0 == obj);
    	{
    		auto act = finally(&SetObjToFive);
    	}
        REQUIRE(5 == obj);
    }
}

TEST_CASE("FinalAction can be dismissed") {
	obj = 0;

    SECTION( "FinalAction calls lambda function" ) {
    	REQUIRE(0 == obj);
    	{
    		auto act = FinalAction{[](){ obj = 3; }};
    		act.dismiss();
    	}
        REQUIRE(0 == obj);
    }
}

TEST_CASE("FinalAction can be moved") {
	obj = 0;

    SECTION( "FinalAction move construction" ) {
    	REQUIRE(0 == obj);
    	{
    		auto act = FinalAction{&SetObjToFive};
    		auto act2 = std::move(act);
    		act2.dismiss();
    	}
        REQUIRE(0 == obj);
    }
}
