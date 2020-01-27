#include "estp/data/pseudorand.hh"

#include "catch2/catch.hpp"

using namespace estp;

TEST_CASE("Pseudorand: Constructor") {
    PseudoRand32 prA = PseudoRand32{};
    PseudoRand32 prB = PseudoRand32{8008};
    PseudoRand32 prC = PseudoRand32{1,2,3,4};

    // Check the first 100 numbers just to be sure
    for (uint32_t i=0; i<100; i++) {
        auto const a = prA.Next();
        auto const b = prB.Next();
        auto const c = prC.Next();
        REQUIRE(((a != b) && (b != c) && (c != a)));
    }
}

// This test case takes a *long* time, so only build and run it when desired
#if 0
TEST_CASE("Pseudorand: Period") {
    PseudoRand32 prA = PseudoRand32{};
    uint32_t const first = prA.Next();
    uint32_t const second = prA.Next();
    uint32_t next_first = prA.Next();
    uint32_t next_second = prA.Next();
    uint64_t count = 0;
    while (((next_first != first) || (next_second != second)) && (count != 0xFFFFFFFFFFFFFFFF)) {
        count += 2;
        next_first = prA.Next();
        next_second = prA.Next();
    }

    REQUIRE(count == 0xFFFFFFFFFFFFFFFF);
}
#endif
