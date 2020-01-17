#include "estp/base/assert.hh"
#include "estp/data/span.hh"
#include "estp/base/types.hh"

#include "catch2/catch.hpp"

#include <array>
#include <utility>
#include <vector>

using namespace estp;

static int assert_count { 0 };

static void HandleAssertion(AssertionContext const &) {
    ++assert_count;
}


static char const kNumbers[] = "0123456789"; // note that this includes a terminating null
static char letters[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };

template<typename T>
struct PrintType {};

TEST_CASE("Span<T> ctor") {
    assert_count = 0;
    SetAssertionHandler(&HandleAssertion);

    Span span_from_const_array {kNumbers};
    Span span_from_array {letters};
    Span span_from_pointer_size {&kNumbers[0], sizeof(kNumbers)};
    Span span_from_pointer_pointer {&letters[0], &letters[10]};

    REQUIRE(span_from_array.size() == 10);
    REQUIRE(span_from_const_array.size() == 11);

    REQUIRE(span_from_const_array == span_from_pointer_size);
    REQUIRE(span_from_array == span_from_pointer_pointer);

    std::array<char,10> std_array_letters { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
    Span span_from_std_array {std_array_letters};

    std::vector<char> vector_letters {letters, std::end(letters)};
    Span span_from_std_vector {vector_letters};

    REQUIRE(span_from_std_array == span_from_std_vector);
}

TEST_CASE("Span<T> accessors") {
    Span letters_span{letters};
    SECTION( "first()" ) {
        for(Index count=0; count<letters_span.size(); ++count) {
            auto prefix = letters_span.first(count);
            REQUIRE(prefix.size() == count);
            for (Index i=0; i<count; ++i) {
                REQUIRE(prefix[i] == letters_span[i]);
            }
        }
    }
    SECTION( "last()" ) {
        for(Index count=0; count<10; ++count) {
            auto suffix = letters_span.last(count);
            REQUIRE(suffix.size() == count);
            for (Index i=0; i<count; ++i) {
                REQUIRE(suffix[i] == letters_span[letters_span.size() - count + i]);
            }
        }
    }

    SECTION( "subspan(index)" ) {
        for(Index count=0; count<10; ++count) {
            auto last = letters_span.last(count);
            auto sub = letters_span.subspan(letters_span.size() - count);
            REQUIRE(last == sub);
        }
    }

    SECTION( "subspan(index, count)" ) {
        Span ac{&letters[0], 3};
        Span df{&letters[3], 3};
        Span gj{&letters[6], 4};

        REQUIRE(ac == letters_span.subspan(0,3));
        REQUIRE(df == letters_span.subspan(3,3));
        REQUIRE(gj == letters_span.subspan(6,4));
    }

    SECTION( "as_span()" ) {
        struct FiveLetters {
            char first;
            char second;
            char third;
            char fourth;
            char fifth;
        };

        Span<FiveLetters> spfl = letters_span.as_span<FiveLetters>();
        REQUIRE('a' == spfl[0].first);
        REQUIRE('b' == spfl[0].second);
        REQUIRE('c' == spfl[0].third);
        REQUIRE('d' == spfl[0].fourth);
        REQUIRE('e' == spfl[0].fifth);
        REQUIRE('f' == spfl[1].first);
        REQUIRE('g' == spfl[1].second);
        REQUIRE('h' == spfl[1].third);
        REQUIRE('i' == spfl[1].fourth);
        REQUIRE('j' == spfl[1].fifth);
    }

    SECTION( "View()" ) {
        Span<char const> kLetters{letters};
        REQUIRE(kLetters == letters_span);
    }
}
