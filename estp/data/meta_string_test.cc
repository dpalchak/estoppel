
#include "estp/data/meta_string.h"
#include "catch2/catch.hpp"

// MetStrings are meta-types, so manipulation of them all occurs at compile
// time. Thus, we don't use a standard run-time unit test framework
// If this test file compiles, then all the tests passed!

using namespace estp;

// Some test fodder
#define LETTERS "ABCDE"
using Letters = MetaString<'A','B','C','D','E'>;
constexpr auto kLetters = MAKE_METASTRING_16(LETTERS);

#define NUMBERS "1234"
using Numbers = MetaString<'1','2','3','4'>;
constexpr auto kNumbers = MAKE_METASTRING_16(NUMBERS);

#define ZIPPED "A1B2C3D4E"
using Zipped = MetaString<'A','1','B','2','C','3','D','4','E'>;
constexpr auto kZipped = MAKE_METASTRING_64(ZIPPED);

constexpr auto kEmptyString = MetaString<>{};


////////////////////////////////////////////////////////////
// Comparison operators
// We test these first because we rely on them extensively in later tests
TEST_CASE( "MetaString comparison", "[metastring]" ) {
	static_assert(Letters{} == Letters{}, "Test: Positive equality comparison");
	static_assert(!(Letters{} == Numbers{}), "Test: Negative equality comparison");

	static_assert(Letters{} != Numbers{}, "Test: Positive inequality comparison");
	static_assert(!(Numbers{} != Numbers{}), "Test: Negative inequality comparison");

	static_assert(MetaString<>{} == kEmptyString, "Test: Equality of empty string");
	static_assert(Letters{} != kEmptyString, "Test: Inequality of empty string");
	static_assert(kEmptyString != Numbers{}, "Test: Inequality of empty string (reverse)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Construction
TEST_CASE( "MetaString construction", "[metastring]" ) {
	static_assert(Letters{} == kLetters, "Test: MAKE_METASTRING(Letters)");
	static_assert(Numbers{} == kNumbers, "Test: MAKE_METASTRING(Numbers)");
	static_assert(Zipped{} == kZipped, "Test: MAKE_METASTRING(Zipped)");
	static_assert(kEmptyString == MAKE_METASTRING_16(""), "Test: MAKE_METASTRING(\"\")");
	static_assert(MetaString<0x00,0x32,0x64,char(0x96),char(0xC8),char(0xFA)>{} ==
		MAKE_METASTRING_16("\x00\x32\x64\x96\xC8\xFA"),
		"Test: MAKE_METASTRING('\x00\x32\x64\x96\xC8\xFA')");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Element Access
TEST_CASE( "MetaString indexing", "[metastring]" ) {
	static_assert('A' == Get<0>(kLetters), "Test: Get<0>(Letters)");
	static_assert('B' == Get<1>(kLetters), "Test: Get<1>(Letters)");
	static_assert('C' == Get<2>(kLetters), "Test: Get<2>(Letters)");
	static_assert('D' == Get<3>(kLetters), "Test: Get<3>(Letters)");
	static_assert('E' == Get<4>(kLetters), "Test: Get<4>(Letters)");

	static_assert('E' == RGet<0>(kLetters), "Test: RGet<0>(Letters)");
	static_assert('D' == RGet<1>(kLetters), "Test: RGet<1>(Letters)");
	static_assert('C' == RGet<2>(kLetters), "Test: RGet<2>(Letters)");
	static_assert('B' == RGet<3>(kLetters), "Test: RGet<3>(Letters)");
	static_assert('A' == RGet<4>(kLetters), "Test: RGet<4>(Letters)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// First N
TEST_CASE( "MetaString first N", "[metastring]" ) {
	static_assert(kEmptyString == First<0>(kNumbers), "Test: First<0>(Numbers)");
	static_assert(MetaString<'1'>{} == First<1>(kNumbers), "Test: First<1>(Numbers)");
	static_assert(MetaString<'1','2'>{} == First<2>(kNumbers), "Test: First<2>(Numbers)");
	static_assert(MetaString<'1','2','3'>{} == First<3>(kNumbers), "Test: First<3>(Numbers)");
	static_assert(MetaString<'1','2','3','4'>{} == First<4>(kNumbers), "Test: First<4>(Numbers)");
	static_assert(MetaString<'1','2','3','4'>{} == First<5>(kNumbers), "Test: First<5>(Numbers)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Last N
TEST_CASE( "MetaString last N", "[metastring]" ) {
	static_assert(kEmptyString == Last<0>(kNumbers), "Test: Last<0>(Numbers)");
	static_assert(MetaString<'4'>{} == Last<1>(kNumbers), "Test: Last<1>(Numbers)");
	static_assert(MetaString<'3','4'>{} == Last<2>(kNumbers), "Test: Last<2>(Numbers)");
	static_assert(MetaString<'2','3','4'>{} == Last<3>(kNumbers), "Test: Last<3>(Numbers)");
	static_assert(MetaString<'1','2','3','4'>{} == Last<4>(kNumbers), "Test: Last<4>(Numbers)");
	static_assert(MetaString<'1','2','3','4'>{} == Last<5>(kNumbers), "Test: Last<5>(Numbers)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Substring
TEST_CASE( "MetaString substring", "[metastring]" ) {
	static_assert(kEmptyString == Substring<0,0>(kEmptyString), "Test: Substring<0,0>(kEmptyString)");
	static_assert(kEmptyString == Substring<0,0>(kZipped), "Test: Substring<0,0>(kZipped)");
	static_assert(kZipped == Substring<0,9>(kZipped), "Test: Substring<0,9>(kZipped)");
	static_assert(MAKE_METASTRING("A1B") == Substring<0,3>(kZipped), "Test: Substring<0,3>(kZipped)");
	static_assert(MAKE_METASTRING("C3D4E") == Substring<4,9>(kZipped), "Test: Substring<4,9>(kZipped)");
	static_assert(MAKE_METASTRING("B2C3D") == Substring<2,7>(kZipped), "Test: Substring<2,7>(kZipped)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Reverse
TEST_CASE( "MetaString reverse", "[metastring]" ) {
	static_assert(MetaString<>{} == Reverse(kEmptyString), "Test: Reverse(EmptyString)");
	static_assert(MetaString<'A'>{} == Reverse(MetaString<'A'>{}), "Test: Reverse(MetaString<A>)");
	static_assert(MetaString<'E','D','C','B','A'>{} == Reverse(kLetters), "Test: Reverse(Letters)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// LStrip
TEST_CASE( "MetaString left strip", "[metastring]" ) {
	static_assert(kEmptyString == LStrip(kEmptyString), "Test: LStrip(kEmptyString)");
	static_assert(kEmptyString == LStrip(MetaString<' ','\t'>{}),
		"Test: LStrip(MetaString<SPACE,TAB>)");

	static_assert(kNumbers == LStrip(MetaString<' ','\t',' ','\t','1','2','3','4'>{}),
		"Test: LStrip(MetaString<SPACE,TAB,SPACE,TAB,Numbers>)");

	static_assert(MetaString<'1','2','3','4','\t'>{} ==
		LStrip(MetaString<' ','\t',' ','\t','1','2','3','4','\t'>{}),
		"Test: LStrip(MetaString<SPACE,TAB,SPACE,TAB,Numbers,TAB>)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// RStrip
TEST_CASE( "MetaString right strip", "[metastring]" ) {
	static_assert(kEmptyString == RStrip(kEmptyString), "Test: RStrip(kEmptyString)");
	static_assert(kEmptyString == RStrip(MetaString<' ','\t','\t'>{}),
		"Test: RStrip(MetaString<SPACE,TAB,TAB>)");

	static_assert(kNumbers == RStrip(MetaString<'1','2','3','4',' ','\t',' ','\t'>{}),
		"Test: RStrip(MetaString<Numbers,SPACE,TAB,SPACE,TAB>)");


	static_assert(MetaString<'\t','1','2','3','4'>{} ==
		RStrip(MetaString<'\t','1','2','3','4',' ','\t',' ','\t'>{}),
		"Test: RStrip(MetaString<TAB,Numbers,SPACE,TAB,SPACE,TAB>)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Strip
TEST_CASE( "MetaString combined strip", "[metastring]" ) {
	constexpr auto kPadded = MAKE_METASTRING("\t\t  CONTENT  \t\t");

	static_assert(kEmptyString == Strip(kEmptyString), "Test: Strip(kEmptyString)");
	static_assert(MAKE_METASTRING("CONTENT") == Strip(kPadded), "Test: Strip(Padded)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Split
TEST_CASE( "MetaString split and join", "[metastring]" ) {
	static_assert(MetaList<MetaString<>>{} == Split<'$'>(kEmptyString), "Test: Split<'$'>(kEmptyString)");
	static_assert(MetaList<Zipped>{} == Split<'$'>(kZipped), "Test: Split<'$'>(Zipped)");

	constexpr auto kCsv = MAKE_METASTRING("first,last,phone,email");
	constexpr auto kSplitCsv = MetaList<
		decltype(MAKE_METASTRING("first")),
		decltype(MAKE_METASTRING("last")),
		decltype(MAKE_METASTRING("phone")),
		decltype(MAKE_METASTRING("email"))>{};

	static_assert(kSplitCsv== Split<','>(kCsv), "Test: Split(CSV)");

	constexpr auto kAbsPath = MAKE_METASTRING("/absolute/path/for/document.pdf");
	constexpr auto kSplitAbsPath = MetaList<
		NullMetaString,
		decltype(MAKE_METASTRING("absolute")),
		decltype(MAKE_METASTRING("path")),
		decltype(MAKE_METASTRING("for")),
		decltype(MAKE_METASTRING("document.pdf"))>{};

	static_assert(kSplitAbsPath== Split<'/'>(kAbsPath), "Test: Split(AbsPath)");

	constexpr auto kBoxes = MAKE_METASTRING("||Col 1||Col 2||Col 3||");
	constexpr auto kSplitBoxes = MetaList<
		NullMetaString,
		NullMetaString,
		decltype(MAKE_METASTRING("Col 1")),
		NullMetaString,
		decltype(MAKE_METASTRING("Col 2")),
		NullMetaString,
		decltype(MAKE_METASTRING("Col 3")),
		NullMetaString,
		NullMetaString>{};

	static_assert(kSplitBoxes == Split<'|'>(kBoxes), "Test: Split(Boxes)");

	////////////////////////////////////////////////////////////
	// Join
	static_assert(kEmptyString == Join<'$'>(kEmptyString), "Test: Join<'$'>(kEmptyString)");
	static_assert(kEmptyString == Join<'$'>(EmptyMetaList{}), "Test: Join<'$'>(EmptyList)");

	static_assert(kCsv == Join<','>(kSplitCsv), "Test: Join<','>(SplitCsv)");
	static_assert(kCsv == Join<','>(MAKE_METASTRING("first"), MAKE_METASTRING("last"),
		MAKE_METASTRING("phone"), MAKE_METASTRING("email")), "Test: Join<','>(CSV Parts)");

	static_assert(kBoxes == Join<'|'>(kSplitBoxes), "Test: Join<'|'>(kSplitBoxes)");

	static_assert(MAKE_METASTRING("red and blue and green") == Join(MAKE_METASTRING(" and "),
		MAKE_METASTRING("red"), MAKE_METASTRING("blue"), MAKE_METASTRING("green")),
		"Test: Join(' and ', 'red', 'blue', 'green')");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Concatenate
TEST_CASE( "MetaString concatenate", "[metastring]" ) {
	constexpr auto kSplitBoxes = MetaList<
		NullMetaString,
		NullMetaString,
		decltype(MAKE_METASTRING("Col 1")),
		NullMetaString,
		decltype(MAKE_METASTRING("Col 2")),
		NullMetaString,
		decltype(MAKE_METASTRING("Col 3")),
		NullMetaString,
		NullMetaString>{};

	static_assert(kEmptyString == Concatenate(kEmptyString,kEmptyString,kEmptyString),
		"Test: Concatenate(kEmptyString,kEmptyString,kEmptyString)");

	static_assert(MAKE_METASTRING("redbluegreen") == Concatenate(MAKE_METASTRING("red"),
		MAKE_METASTRING("blue"), MAKE_METASTRING("green")),
		"Test: Concatenate('red','blue','green')");

	static_assert(MAKE_METASTRING("Col 1Col 2Col 3") == Concatenate(kSplitBoxes),
		"Test: Concatenate(kSplitBoxes)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Pièce De Résistance
TEST_CASE( "MetaString get basename of _FILE_", "[metastring]" ) {
	static_assert(MAKE_METASTRING("meta_string_test.cc") ==
		RGet<0>(Split<'/'>(MAKE_METASTRING_256(__FILE__))),
		"Test: Get basename of current source file");
	REQUIRE(true);
}
