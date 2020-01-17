#include "estp/data/accumulator.hh"

#include "catch2/catch.hpp"

#include <array>
#include <utility>

using namespace estp;

static char letters[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

TEST_CASE("Accumulator constructor") {
    SECTION("Basic Construction") {
        char buf[15];
        Accumulator acc{Span{buf,15}};
        REQUIRE(acc.data().begin() == buf);
        REQUIRE(acc.data().size() == 0);
        REQUIRE(acc.capacity() == 15);
    }

    SECTION("Tricky Construction") {
        char buf[0];
        // The +0 forces the compiler to treat the literal as an integer and not a null pointer
        Accumulator acc{Span{buf,+0}};
        REQUIRE(acc.data().begin() == buf);
        REQUIRE(acc.data().size() == 0);
        REQUIRE(acc.capacity() == 0);
    }
}

char buf[8];
Accumulator acc{Span{buf,8}};

TEST_CASE("Accumulator accumulates") {

    SECTION("Starts empty with full capacity") {
        REQUIRE(acc.empty());
        REQUIRE(acc.capacity() == 8);
    }

    SECTION("Fill and empty sizes change") {
        for(int i=0; i<8; i++) {
            REQUIRE(acc.fill_size() == i);
            REQUIRE(acc.empty_size() == 8-i);
            REQUIRE(acc.capacity() == 8);
            acc.PushBack(letters[i]);
            REQUIRE(acc.Back() == letters[i]);

        }
        REQUIRE(acc.fill_size() == 8);
        REQUIRE(acc.empty_size() == 0);
        REQUIRE(acc.full());
    }

    SECTION("Data is retained") {
        REQUIRE(acc.fill_size() == 8);
        REQUIRE(acc.data().begin() != nullptr);
        //REQUIRE(acc.data() == Span{letters, 8});
    }
    return;

    SECTION("Data can be removed") {
        for(int i=7; i>3; i--) {
            acc.PopBack();
            REQUIRE(acc.fill_size() == i);
            REQUIRE(acc.capacity() == 8);
            REQUIRE(acc.data() == Span{letters, acc.fill_size()});
        }
    }

    SECTION("Reset empties all data") {
        REQUIRE(!acc.empty());
        acc.Reset();
        REQUIRE(acc.empty());
        REQUIRE(acc.data().begin() == buf);
        REQUIRE(acc.capacity() == 8);
    }

    SECTION("Data can be emplaced") {
        acc.EmplaceBack('D');
        acc.EmplaceBack('O');
        acc.EmplaceBack('N');
        acc.EmplaceBack('E');
        REQUIRE(acc.fill_size() == 4);
        REQUIRE(acc.data().view() == Span{"DONE"});
    }
}
