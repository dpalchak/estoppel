
#include "estp/data/typestring.h"
#include "estp/base/macros.h"
#include "catch2/catch.hpp"

// TypeStrings are actually types not values so manipulation of them
// can occur at compile time. Thus, we don't use a standard run-time
// unit test framework. If this test file compiles, then all the tests passed!

using namespace estp;

////////////////////////////////////////////////////////////
// Comparison operators
// We test these first because we rely on them extensively in later tests
TEST_CASE( "TypeString comparison", "[TypeString]" ) {
    using Letters = TypeString<'A','B','C','D','E'>;
    using Numbers = TypeString<'1','2','3','4'>;

	static_assert(Letters{} == Letters{}, "Test: Positive equality comparison");
	static_assert(!(Letters{} == Numbers{}), "Test: Negative equality comparison");

	static_assert(Letters{} != Numbers{}, "Test: Positive inequality comparison");
	static_assert(!(Numbers{} != Numbers{}), "Test: Negative inequality comparison");

	static_assert(TypeString<>{} == kEmptyTypeString, "Test: Equality of empty string");
	static_assert(Letters{} != kEmptyTypeString, "Test: Inequality of empty string");
	static_assert(kEmptyTypeString != Numbers{}, "Test: Inequality of empty string (reverse)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Construction
TEST_CASE( "TypeString construction", "[TypeString]" ) {
    using Letters = TypeString<'A','B','C','D','E'>;
    constexpr auto kLetters = "ABCDE"_type;

    using Numbers = TypeString<'1','2','3','4'>;
    constexpr auto kNumbers = "1234"_type;

    using Zipped = TypeString<'A','1','B','2','C','3','D','4','E'>;
    constexpr auto kZipped = "A1B2C3D4E"_type;

	static_assert(Letters{} == kLetters, "Test: kLetters construction");
	static_assert(Numbers{} == kNumbers, "Test: kNumbers construction");
	static_assert(Zipped{} == kZipped, "Test: kZipped construction");
	static_assert(kEmptyTypeString == ""_type, "Test: empty TypeString construction");
	static_assert(TypeString<0x00,0x32,0x64,char(0x96),char(0xC8),char(0xFA)>{} ==
		"\x00\x32\x64\x96\xC8\xFA"_type,
		"Test: \"\x00\x32\x64\x96\xC8\xFA\"_type construction");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Element Access
TEST_CASE( "TypeString indexing", "[TypeString]" ) {
    constexpr auto kLetters = "ABCDE"_type;

	static_assert("A"_type == At(kLetters, IndexSequence<0>{}), "Test At(Letters, <0>)");
	static_assert("AB"_type == At(kLetters, IndexSequence<0,1>{}), "Test At(Letters, <0,1>)");
	static_assert("ABC"_type == At(kLetters, IndexSequence<0,1,2>{}), "Test At(Letters, <0,1,2>)");
	static_assert("ACE"_type == At(kLetters, IndexSequence<0,2,4>{}), "Test At(Letters, <0,2,4>)");
	static_assert("EDA"_type == At(kLetters, IndexSequence<4,3,0>{}), "Test At(Letters, <4,3,0>)");

	REQUIRE(true);
}
////////////////////////////////////////////////////////////
// First N
TEST_CASE( "TypeString first N", "[TypeString]" ) {
    constexpr auto kNumbers = "1234"_type;

	static_assert(kEmptyTypeString == First(kNumbers, Index_k<0>),
        "Test: First<0>(Numbers)");
	static_assert("1"_type == First(kNumbers, Index_k<1>),
        "Test: First<1>(Numbers)");
	static_assert("12"_type == First(kNumbers, Index_k<2>),
        "Test: First<2>(Numbers)");
	static_assert("123"_type == First(kNumbers, Index_k<3>),
        "Test: First<3>(Numbers)");
	static_assert("1234"_type == First(kNumbers, Index_k<4>),
        "Test: First<4>(Numbers)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Last N
TEST_CASE( "TypeString last N", "[TypeString]" ) {
    constexpr auto kNumbers = "1234"_type;

	static_assert(kEmptyTypeString == Last(kNumbers, Index_k<0>), "Test: Last<0>(Numbers)");
	static_assert("4"_type == Last(kNumbers, Index_k<1>), "Test: Last<1>(Numbers)");
	static_assert("34"_type == Last(kNumbers, Index_k<2>), "Test: Last<2>(Numbers)");
	static_assert("234"_type == Last(kNumbers, Index_k<3>), "Test: Last<3>(Numbers)");
	static_assert("1234"_type == Last(kNumbers, Index_k<4>), "Test: Last<4>(Numbers)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// From
TEST_CASE( "TypeString from I", "[TypeString]" ) {
    constexpr auto kNumbers = "1234"_type;

	static_assert(kEmptyTypeString == From(kNumbers, Index_k<4>), "Test: From<4>(Numbers)");
	static_assert("4"_type == From(kNumbers, Index_k<3>), "Test: From<3>(Numbers)");
	static_assert("34"_type == From(kNumbers, Index_k<2>), "Test: From<2>(Numbers)");
	static_assert("234"_type == From(kNumbers, Index_k<1>), "Test: From<1>(Numbers)");
	static_assert("1234"_type == From(kNumbers, Index_k<0>), "Test: From<0>(Numbers)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Substring
TEST_CASE( "TypeString substring", "[TypeString]" ) {
    constexpr auto kZipped = "A1B2C3D4E"_type;

	static_assert(kEmptyTypeString == Substring(kEmptyTypeString, Index_k<0>, Index_k<0>),
        "Test: Substring<0,0>(kEmptyTypeString)");

	static_assert(kEmptyTypeString == Substring(kEmptyTypeString, Index_k<1000>, Index_k<1000>),
        "Test: Substring<0,0>(kEmptyTypeString)");

	static_assert(kEmptyTypeString == Substring(kZipped, Index_k<0>, Index_k<0>),
        "Test: Substring<0,0>(kZipped)");

	static_assert(kZipped == Substring(kZipped, Index_k<0>, Index_k<9>),
        "Test: Substring<0,9>(kZipped)");

	static_assert("A1B"_type == Substring(kZipped, Index_k<0>, Index_k<3>),
        "Test: Substring<0,3>(kZipped)");

	static_assert("C3D4E"_type == Substring(kZipped, Index_k<4>, Index_k<9>),
        "Test: Substring<4,9>(kZipped)");

	static_assert("B2C3D"_type == Substring(kZipped, Index_k<2>, Index_k<7>),
        "Test: Substring<2,7>(kZipped)");

	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Join
TEST_CASE( "TypeString join", "[TypeString]" ) {
	static_assert(kEmptyTypeString == Join(Char_k<'$'>, kEmptyTypeString),
        "Test: Join('$', kEmptyTypeString)");

	static_assert(kEmptyTypeString == Join("###"_type, kEmptyTypeString),
        "Test: Join(\"###\", kEmptyTypeString)");

	static_assert("first,last,phone,email"_type ==
        Join(Char_k<','>, "first"_type, "last"_type, "phone"_type, "email"_type),
        "Test: Join(',', first, last, phone, email)");

	static_assert("lions and tigers and bears oh my"_type ==
        Join(" and "_type, "lions"_type, "tigers"_type, "bears oh my"_type),
		"Test: Join(' and ', lions, tigers, bears oh my)");

	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Concatenate
TEST_CASE( "TypeString concatenate", "[TypeString]" ) {
	static_assert(kEmptyTypeString ==
        Concatenate(kEmptyTypeString,kEmptyTypeString,kEmptyTypeString),
		"Test: Concatenate(kEmptyTypeString,kEmptyTypeString,kEmptyTypeString)");

	static_assert("redbluegreen"_type == Concatenate("red"_type, "blue"_type, "green"_type),
		"Test: Concatenate('red','blue','green')");

	static_assert("Col 1Col 2Col 3"_type ==
        Concatenate(
            kEmptyTypeString,
		    kEmptyTypeString,
		    "Col 1"_type,
		    kEmptyTypeString,
            "Col 2"_type,
            kEmptyTypeString,
            "Col 3"_type,
            kEmptyTypeString,
            kEmptyTypeString),
		"Test: Concatenate(<a bunch of type strings>)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Find and ReverseFind
TEST_CASE( "Typestring find, reverse find", "[TypeString]" ) {
    constexpr auto kString = "002244678"_type;

    // Forward find
    static_assert(Index_k<-1> == Find(kEmptyTypeString, Char_k<'!'>),
        "Test: Find(emptyString, !)");

    static_assert(Index_k<-1> == Find(kString, Char_k<'X'>),
        "Test: Find(\"002244678\", 'X')");

    static_assert(Index_k<0> == Find(kString, Char_k<'0'>),
        "Test: Find(\"002244678\", '0')");

    static_assert(Index_k<2> == Find(kString, Char_k<'2'>),
        "Test: Find(\"002244678\", '2')");

    static_assert(Index_k<4> == Find(kString, Char_k<'4'>),
        "Test: Find(\"002244678\", '4')");

    static_assert(Index_k<6> == Find(kString, Char_k<'6'>),
        "Test: Find(\"002244678\", '8')");

    static_assert(Index_k<8> == Find(kString, Char_k<'8'>),
        "Test: Find(\"002244678\", '8')");

    // Reverse find
    constexpr auto kString2 = "012446688"_type;

    static_assert(Index_k<-1> == ReverseFind(kEmptyTypeString, Char_k<'!'>),
        "Test: ReverseFind(emptyString, !)");

    static_assert(Index_k<-1> == ReverseFind(kString2, Char_k<'X'>),
        "Test: ReverseFind(\"012446688\", 'X')");

    static_assert(Index_k<0> == ReverseFind(kString2, Char_k<'0'>),
        "Test: ReverseFind(\"012446688\", '0')");

    static_assert(Index_k<2> == ReverseFind(kString2, Char_k<'2'>),
        "Test: ReverseFind(\"012446688\", '2')");

    static_assert(Index_k<4> == ReverseFind(kString2, Char_k<'4'>),
        "Test: ReverseFind(\"012446688\", '4')");

    static_assert(Index_k<6> == ReverseFind(kString2, Char_k<'6'>),
        "Test: ReverseFind(\"012446688\", '8')");

    static_assert(Index_k<8> == ReverseFind(kString2, Char_k<'8'>),
        "Test: ReverseFind(\"012446688\", '8')");

    REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Prefix
TEST_CASE( "TypeString prefix", "[TypeString]" ) {
    constexpr auto kZipped = "A1B2C3D4E"_type;

    static_assert(kEmptyTypeString == Prefix(kEmptyTypeString, Char_k<'#'>),
        "Test: Prefix(\"\", '#'");

    static_assert(""_type == Prefix(kZipped, Char_k<'A'>),
        "Test: Prefix(\"A1B2C3D4E\", '2')");

    static_assert("A1B"_type == Prefix(kZipped, Char_k<'2'>),
        "Test: Prefix(\"A1B2C3D4E\", '2')");

    static_assert("A1B2C3D4"_type == Prefix(kZipped, Char_k<'E'>),
        "Test: Prefix(\"A1B2C3D4E\", 'E')");

    static_assert("A1B2C3D4E"_type == Prefix(kZipped, Char_k<'$'>),
        "Test: Prefix(\"A1B2C3D4E\", '$')");

}

////////////////////////////////////////////////////////////
// Suffix
TEST_CASE( "TypeString suffix", "[TypeString]" ) {
    constexpr auto kZipped = "A1B2C3D4E"_type;

    static_assert(kEmptyTypeString == Suffix(kEmptyTypeString, Char_k<'#'>),
        "Test: Suffix(\"\", '#'");

    static_assert(""_type == Suffix(kZipped, Char_k<'E'>),
        "Test: Suffix(\"A1B2C3D4E\", 'E')");

    static_assert("3D4E"_type == Suffix(kZipped, Char_k<'C'>),
        "Test: Suffix(\"A1B2C3D4E\", 'C')");

    static_assert("1B2C3D4E"_type == Suffix(kZipped, Char_k<'A'>),
        "Test: Suffix(\"A1B2C3D4E\", 'A')");

    static_assert("A1B2C3D4E"_type == Suffix(kZipped, Char_k<'$'>),
        "Test: Suffix(\"A1B2C3D4E\", '$')");

}

////////////////////////////////////////////////////////////
// Pièce De Résistance

#define __BASENAME__ Suffix( TOKEN_JOIN(__FILE__, _type), Char_k<'/'>)

TEST_CASE( "TypeString get basename of __FILE__", "[TypeString]" ) {
    constexpr auto kAbsFilename = "/absolute/path/to/a/source_file.cc"_type;
    constexpr auto kRelFilename = "../some_header.h"_type;
    constexpr auto kImmFilename = "NoSeparatorsHere.bin"_type;

    static_assert("source_file.cc"_type == Suffix(kAbsFilename, Char_k<'/'>),
        "Test: Suffix(\"/absolute/path/to/a/source_file.cc\", '/'");

    static_assert("cc"_type == Suffix(kAbsFilename, Char_k<'.'>),
        "Test: Suffix(\"/absolute/path/to/a/source_file.cc\", '.'");

    static_assert("some_header.h"_type == Suffix(kRelFilename, Char_k<'/'>),
        "Test: Suffix(\"../some_header.h\", '/')");

    static_assert("h"_type == Suffix(kRelFilename, Char_k<'.'>),
        "Test: Suffix(\"../some_header.h\", '.')");

    static_assert(kImmFilename == Suffix(kImmFilename, Char_k<'/'>),
        "Test: Suffix(\"NoSeparatorsHere.bin\", '/')");

    static_assert("typestring_test.cc"_type == __BASENAME__,
        "Test: __BASENAME__ macro");

	REQUIRE(true);
}
