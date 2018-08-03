
#include "data/meta_list.h"
#include "base/meta.h"
#include "catch2/catch.hpp"

// MetaLists are meta-types, so manipulation of them all occurs at compile
// time. Thus, we don't use a standard run-time unit test framework
// If this test file compiles, then all the tests passed!

using namespace estp;


using A = Char<'A'>;
using B = Char<'B'>;
using C = Char<'C'>;
using D = Char<'D'>;
using E = Char<'E'>;
using Letters = MetaList<A,B,C,D,E>;

using Zero = Int<0>;
using One = Int<1>;
using Two = Int<2>;
using Three = Int<3>;
using Four = Int<4>;
using Numbers = MetaList<Zero, One, Two, Three, Four>;

using Zipped = MetaList<A, Zero, B, One, C, Two, D, Three, E, Four >;

template<typename T>
using IsEvenNumber = Bool<(T::value % 2) == 0>;

template<typename T>
using IsOddLetter = Bool<((T::value - 'A') % 2) == 0>;

////////////////////////////////////////////////////////////
// Length
TEST_CASE( "MetaList length", "[metalist]" ) {
	static_assert(0 == Length(EmptyMetaList{}), "Test: length of empty list");
	static_assert(1 == Length(MetaList<A>{}), "Test: length of one element list");
	static_assert(2 == Length(MetaList<A,B>{}), "Test: length of two element list");
	static_assert(5 == Length(Letters{}), "Test: length of letter list");
	static_assert(5 == Length(Numbers{}), "Test: length of numbers list");
	static_assert(10 == Length(Zipped{}), "Test: length of zipped list");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Indexing
TEST_CASE( "MetaList index", "[metalist]" ) {
	static_assert(A{} == Get<0>(Letters{}), "Test: Get<0>(Letters)");
	static_assert(B{} == Get<1>(Letters{}), "Test: Get<1>(Letters)");
	static_assert(C{} == Get<2>(Letters{}), "Test: Get<2>(Letters)");
	static_assert(Four{} == Get<4>(Numbers{}), "Test: Get<4>(Numbers)");
	static_assert(D{} == Get<0>(MetaList<D>{}), "Test: Get<D>(List<D>)");
	REQUIRE(true);
}


// Reverse Get
TEST_CASE( "MetaList reverse-index", "[metalist]" ) {
	static_assert(Four{} == RGet<0>(Numbers{}), "Test: RGet<0>(Numbers)");
	static_assert(Three{} == RGet<1>(Numbers{}), "Test: RGet<1>(Numbers)");
	static_assert(Two{} == RGet<2>(Numbers{}), "Test: RGet<2>(Numbers)");
	static_assert(One{} == RGet<3>(Numbers{}), "Test: RGet<3>(Numbers)");
	static_assert(Zero{} == RGet<4>(Numbers{}), "Test: RGet<4>(Numbers)");
	static_assert(D{} == RGet<0>(MetaList<D>{}), "Test: RGet<D>(List<D>)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// First N
TEST_CASE( "MetaList first N items", "[metalist]" ) {

	static_assert(EmptyMetaList{} == First<0>(Zipped{}), "Test: First<0>(Zipped)");
	static_assert(MetaList<A>{} == First<1>(Zipped{}), "Test: First<1>(Zipped)");
	static_assert(MetaList<A,Zero>{} == First<2>(Zipped{}),
			"Test: First<2>(Zipped)");
	static_assert(MetaList<A,Zero,B>{} == First<3>(Zipped{}),
			"Test: First<3>(Zipped)");
	static_assert(MetaList<A,Zero,B,One>{} == First<4>(Zipped{}),
			"Test: First<4>(Zipped)");

	static_assert(Zipped{} == First<10>(Zipped{}), "Test: First<10>(Zipped)");
	static_assert(Zipped{} == First<11>(Zipped{}), "Test: First<11>(Zipped)");
	static_assert(Zipped{} == First<12>(Zipped{}), "Test: First<12>(Zipped)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Last N
TEST_CASE( "MetaList last N items", "[metalist]" ) {

	static_assert(EmptyMetaList{} == Last<0>(Zipped{}), "Test: Last<0>(Zipped)");
	static_assert(MetaList<Four>{} == Last<1>(Zipped{}), "Test: Last<1>(Zipped)");
	static_assert(MetaList<E, Four>{} == Last<2>(Zipped{}),
			"Test: Last<2>(Zipped)");
	static_assert(MetaList<Three, E, Four>{} == Last<3>(Zipped{}),
			"Test: Last<3>(Zipped)");
	static_assert(MetaList<D, Three, E, Four>{} == Last<4>(Zipped{}),
			"Test: Last<4>(Zipped)");

	static_assert(Zipped{} == Last<10>(Zipped{}), "Test: Last<10>(Zipped)");
	static_assert(Zipped{} == Last<11>(Zipped{}), "Test: Last<11>(Zipped)");
	static_assert(Zipped{} == Last<12>(Zipped{}), "Test: Last<12>(Zipped)");
	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Concatenation
TEST_CASE( "MetaList concatenate", "[metalist]" ) {

	static_assert(EmptyMetaList{} == Concatenate(EmptyMetaList{}, EmptyMetaList{}),
			"Test: Concatenate(Empty, Empty)");

	static_assert(MetaList<A>{} == Concatenate(EmptyMetaList{}, MetaList<A>{}),
			"Test: Concatenate(Empty, List<A>)");

	static_assert(MetaList<A>{} == Concatenate(MetaList<A>{}, EmptyMetaList{}),
			"Test: Concatenate(List<A>, Empty)");

	static_assert(Numbers{} == Concatenate(EmptyMetaList{}, Numbers{}),
			"Test: Concatenate(Empty, Numbers)");

	static_assert(Numbers{} == Concatenate(Numbers{}, EmptyMetaList{}),
			"Test: Concatenate(Numbers, Empty)");

	static_assert(MetaList<Zero,A,B,C,D,E>{} == Concatenate(MetaList<Zero>{}, Letters{}),
			"Test: Concatenate(List<Zero>, Letters)");

	static_assert(MetaList<A,B,C,D,E,Zero>{} == Concatenate(Letters{}, MetaList<Zero>{}),
			"Test: Concatenate(Letters, List<Zero>)");

	static_assert(MetaList<A,B,C,D,E,Zero,One,Two,Three,Four>{} ==
			Concatenate(Letters{}, Numbers{}),
			"Test: Concatenate(Letters, Numbers)");

	static_assert(MetaList<Zero,One,Two,Three,Four,A,B,C,D,E>{} ==
			Concatenate(Numbers{}, Letters{}),
			"Test: Concatenate(Numbers, Letters)");

	static_assert(MetaList<Zero,One,Two,Three,Four,A,B,C,D,E>{} ==
			Concatenate(EmptyMetaList{}, Numbers{}, Letters{}),
			"Test: Concatenate(Numbers, Letters, Numbers)");

	static_assert(MetaList<Zero,One,Two,Three,Four,A,B,C,D,E>{} ==
			Concatenate(Numbers{}, EmptyMetaList{}, Letters{}),
			"Test: Concatenate(Numbers, Letters, Numbers)");

	static_assert(MetaList<Zero,One,Two,Three,Four,A,B,C,D,E,Zero,One,Two,Three,Four>{} ==
			Concatenate(Numbers{}, Letters{}, Numbers{}),
			"Test: Concatenate(Numbers, Letters, Numbers)");

	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Append
TEST_CASE( "MetaList append", "[metalist]" ) {

	static_assert(MetaList<A>{} == Append(EmptyMetaList{}, A{}),
			"Test: Append(Empty, A)");

	static_assert(MetaList<A,B,C,D,E,Zero>{} == Append(Letters{}, Zero{}),
			"Test: Append(Letters, Zero)");

	REQUIRE(true);
}


////////////////////////////////////////////////////////////
// Prepend
TEST_CASE( "MetaList prepend", "[metalist]" ) {

	static_assert(MetaList<A>{} == Prepend(EmptyMetaList{}, A{}),
			"Test: Prepend(Empty, A)");

	static_assert(MetaList<Zero,A,B,C,D,E>{} == Prepend(Letters{}, Zero{}),
			"Test: Prepend(Letters, Zero)");

	REQUIRE(true);
}

////////////////////////////////////////////////////////////
// Filter
TEST_CASE( "MetaList filter", "[metalist]" ) {

	static_assert(EmptyMetaList{} == Filter<IsEvenNumber>(EmptyMetaList{}),
			"Test: Filter<IsEvenNumber>(EmptyList)");

	static_assert(MetaList<Zero>{} == Filter<IsEvenNumber>(MetaList<Zero>{}),
			"Test: Filter<IsEvenNumber>(List<Zero>)");

	static_assert(EmptyMetaList{} == Filter<IsEvenNumber>(MetaList<One>{}),
			"Test: Filter<IsEvenNumber>(List<One>)");

	static_assert(MetaList<Zero, Two, Four>{} == Filter<IsEvenNumber>(Numbers{}),
			"Test: Filter<IsEvenNumber>(Numbers)");

	static_assert(MetaList<B,D>{} == Filter<IsEvenNumber>(Letters{}),
			"Test: Filter<IsOddLetter>(Letters)");

	static_assert(Zipped{} == Filter<True>(Zipped{}),
			"Test: Filter<True>(Zipped)");

	static_assert(EmptyMetaList{} == Filter<False>(Zipped{}),
			"Test: Filter<False>(Zipped)");

	REQUIRE(true);
}



