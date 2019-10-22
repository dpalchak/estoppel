#pragma once

#include "base/meta.h"
#include "base/types.h"
#include "data/meta_list.h"

#include <tuple>

namespace estp {

template<char... Chars>
struct MetaString  {
    constexpr static auto length {sizeof...(Chars)};

    // Include an implicit null terminator for compatibility with normal string-handling functions
    constexpr static char const value[sizeof...(Chars)+1] { Chars..., '\0'};

    constexpr static CZString cbegin() {
    	return &value[0];
    }

    constexpr static CZString cend() {
    	return &value[length];
    }

    constexpr operator StringLiteral<length+1>() const {
    	return value;
    }
};

template<char... C>
constexpr char const MetaString<C...>::value[sizeof...(C)+1];

template<>
struct MetaString<> {
    constexpr static auto length {0*sizeof(int)};

    // Include an implicit null terminator for compatibility with normal string-handling functions
    constexpr static char const value[] {'\0'};

    constexpr static CZString cbegin() {
    	return &value[0];
    }

    constexpr static CZString cend() {
    	return &value[length];
    }

    constexpr operator StringLiteral<length+1>() const {
    	return value;
    }
};

constexpr char const MetaString<>::value[1];

using NullMetaString = MetaString<>;

template<typename First, typename Second>
struct MetaStringPair {
	constexpr static First const first{};
	constexpr static Second const second{};
};


namespace _metastring {

struct StringLiteralTooLong {};

// Return the element at the specified index, or the element at index N-1 if
// the specified index is larger than the size of the StringLiteral
template<auto I, auto N>
constexpr char SaturatingGet(StringLiteral<N> str) {
	static_assert(I >= 0, "Index out of range");
	return str[(I < N) ? I : N-1];
}

// Used to check MetaString length
template<bool B, char... Chars>
constexpr auto CheckMetaStringMaxLen(MetaString<Chars...>) {
	if constexpr(Bool<B, MetaString<Chars...>>::value) {
		return MetaString<Chars...>{};
	} else {
		static_assert(Bool<B, MetaString<Chars...>>::value,
			"Length of string literal exceeds METASTRING_MAX_LEN");
		return StringLiteralTooLong{};
	}
}

template<auto N, char First, char... Rest>
constexpr char _Get(MetaString<First>, MetaString<Rest>...) {
	if constexpr(0 == N) {
		return First;
	} else {
		return _Get<N-1>(MetaString<Rest>{}...);
	}
}

template<auto N, char... Head>
constexpr auto _First(MetaString<Head...>, NullMetaString) {
	static_assert(sizeof...(Head) <= N);
	return MetaString<Head...>{};
}

template<auto N, char... Head, char Next, char... Rest>
constexpr auto _First(MetaString<Head...>, MetaString<Next, Rest...>) {
	if constexpr(sizeof...(Head) < N) {
		return _First<N>(MetaString<Head..., Next>{}, MetaString<Rest...>{});
	} else {
		return MetaString<Head...>{};
	}
}

template<auto N, char... Head>
constexpr auto _Last(MetaString<Head...>, NullMetaString) {
	return NullMetaString{};
}

template<auto N, char... Head, char Next, char... Rest>
constexpr auto _Last(MetaString<Head...>, MetaString<Next, Rest...>) {
	if constexpr(1+sizeof...(Rest) > N) {
		return _Last<N>(MetaString<Head..., Next>{}, MetaString<Rest...>{});
	} else {
		return MetaString<Next,Rest...>{};
	}
}

template<char... Rev>
constexpr auto _Reverse(NullMetaString, MetaString<Rev...>) {
	return MetaString<Rev...>{};
}

template<char First, char... Fwd, char... Rev>
constexpr auto _Reverse(MetaString<First, Fwd...>, MetaString<Rev...>) {
	return _Reverse(MetaString<Fwd...>{}, MetaString<First, Rev...>{});
}

constexpr auto _LStrip(NullMetaString) {
	return NullMetaString{};
}

template<char First, char... Rest>
constexpr auto _LStrip(MetaString<First, Rest...>) {
	if constexpr((' ' == First) || ('\t' == First)) {
		return _LStrip(MetaString<Rest...>{});
	} else {
		return MetaString<First, Rest...>{};
	}
}

template<char X, char... Buf, typename... Pieces>
constexpr auto _Split(NullMetaString, MetaString<Buf...>, MetaList<Pieces...>) {
	return Append(MetaList<Pieces...>{}, MetaString<Buf...>{});
}

template<char X, char First, char... Rest, char... Buf, typename... Pieces>
constexpr auto _Split(MetaString<First, Rest...>, MetaString<Buf...>, MetaList<Pieces...>) {
	if constexpr(First == X) {
		return _Split<X>(MetaString<Rest...>{}, NullMetaString{},
			Append(MetaList<Pieces...>{}, MetaString<Buf...>{}));
	} else {
		return _Split<X>(MetaString<Rest...>{}, MetaString<Buf..., First>{}, MetaList<Pieces...>{});
	}
}

} // namespace _metastring

template<auto N, char... Chars>
constexpr char Get(MetaString<Chars...>) {
	static_assert(N >= 0, "Index out of range");
	static_assert(N < sizeof...(Chars), "Index out of range");
	return _metastring::_Get<N>(MetaString<Chars>{}...);
}

template<auto N, char... Chars>
constexpr char RGet(MetaString<Chars...>) {
	static_assert(N >= 0, "Index out of range");
	static_assert(N < sizeof...(Chars), "Index out of range");
	return _metastring::_Get<sizeof...(Chars)-N-1>(MetaString<Chars>{}...);
}

// Return the first N characters as a MetaString
template<auto N, char... Chars>
constexpr auto First(MetaString<Chars...>) {
	static_assert(N >= 0, "Index out of range");
	return _metastring::_First<N>(NullMetaString{}, MetaString<Chars...>{});
}

// Return the last N characters in a MetaString
template<auto N, char... Chars>
constexpr auto Last(MetaString<Chars...>) {
	static_assert(N >= 0, "Index out of range");
	return _metastring::_Last<N>(NullMetaString{}, MetaString<Chars...>{});
}

// Return the substring between indices [Start, End)
template<auto Start, auto End, char... Chars>
constexpr auto Substring(MetaString<Chars...>) {
	static_assert((0 <= Start) && (Start <= End), "Invalid start index");
	static_assert(End <= sizeof...(Chars), "Invalid end index");
	return First<End-Start>(Last<sizeof...(Chars)-Start>(MetaString<Chars...>{}));
}

// Reverse a MetaString
template<char... Chars>
constexpr auto Reverse(MetaString<Chars...>) {
	return _metastring::_Reverse(MetaString<Chars...>{}, NullMetaString{});
}

// Removes leading whitespace and null characters
template<char... Chars>
constexpr auto LStrip(MetaString<Chars...>) {
	return _metastring::_LStrip(MetaString<Chars...>{});
}

// Remove trailing whitespace and null characters
template<char... Chars>
constexpr auto RStrip(MetaString<Chars...>) {
	return Reverse(LStrip(Reverse(MetaString<Chars...>{})));
}

// Remove leading and trailing whitespace and null characters
template<char... Chars>
constexpr auto Strip(MetaString<Chars...>) {
	return RStrip(LStrip(MetaString<Chars...>{}));
}

// Split string on char X and return a list of substrings
template<char X, char... Chars>
constexpr auto Split(MetaString<Chars...>) {
	return _metastring::_Split<X>(MetaString<Chars...>{}, NullMetaString{}, EmptyMetaList{});
}

// Join MetaStrings with separator MetaString
template<char... Sep, char... Chars>
constexpr auto Join(MetaString<Sep...>, MetaString<Chars...>) {
	return MetaString<Chars...>{};
}

template<char... Sep, char... First, char... Second, typename... Rest>
constexpr auto Join(MetaString<Sep...>, MetaString<First...>, MetaString<Second...>, Rest...) {
	return Join(MetaString<Sep...>{}, MetaString<First...,Sep...,Second...>{}, Rest{}...);
}

template<char... Sep, typename... Items>
constexpr auto Join(MetaString<Sep...>, MetaList<Items...>) {
	if constexpr(0 == sizeof...(Items)) {
		return NullMetaString{};
	} else {
		return Join(MetaString<Sep...>{}, Items{}...);
	}
}

// Join MetaStrings with single char
template<char Sep, typename... Strings>
constexpr auto Join(Strings...) {
	return Join(MetaString<Sep>{}, Strings{}...);
}

template<char Sep, typename... Items>
constexpr auto Join(MetaList<Items...>) {
	return Join(MetaString<Sep>{}, MetaList<Items...>{});
}


// Concatenate multiple MetaStrings
template<char... First, typename... Rest>
constexpr auto Concatenate(MetaString<First...>, Rest...) {
	return Join(NullMetaString{}, MetaString<First...>{}, Rest{}...);
}

template<typename... Items>
constexpr auto Concatenate(MetaList<Items...>) {
	if constexpr(0 == sizeof...(Items)) {
		return NullMetaString{};
	} else {
		return Concatenate(Items{}...);
	}
}

// Comparison operators
template<char... LHS, char... RHS>
constexpr bool operator==(MetaString<LHS...>, MetaString<RHS...>) {
	return false;
}

template<char... Chars>
constexpr bool operator==(MetaString<Chars...>, MetaString<Chars...>) {
	return true;
}

template<char... LHS, char... RHS>
constexpr bool operator!=(MetaString<LHS...>, MetaString<RHS...>) {
	return !(MetaString<LHS...>{} == MetaString<RHS...>{});
}



// Now we use to pre-processing hacks to generate long lists
// of calls to SaturatingGet. These tokens get concatenated and placed in the
// template parameter list of a MetaString class declaration

#define METASTRING_GET_CHAR_AT(_index, _literal) \
	::estp::_metastring::SaturatingGet<_index>(_literal)

#define METASTRING_GET_16_CHARS_AT(_base, _literal) \
    METASTRING_GET_CHAR_AT(_base+ 0, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 1, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 2, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 3, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 4, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 5, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 6, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 7, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 8, _literal), \
    METASTRING_GET_CHAR_AT(_base+ 9, _literal), \
    METASTRING_GET_CHAR_AT(_base+10, _literal), \
    METASTRING_GET_CHAR_AT(_base+11, _literal), \
    METASTRING_GET_CHAR_AT(_base+12, _literal), \
    METASTRING_GET_CHAR_AT(_base+13, _literal), \
    METASTRING_GET_CHAR_AT(_base+14, _literal), \
    METASTRING_GET_CHAR_AT(_base+15, _literal)

#define METASTRING_GET_64_CHARS_AT(_base, _literal) \
	METASTRING_GET_16_CHARS_AT(_base + 16* 0, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 1, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 2, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 3, _literal)

#define METASTRING_GET_256_CHARS_AT(_base, _literal) \
	METASTRING_GET_16_CHARS_AT(_base + 16* 0, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 1, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 2, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 3, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 4, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 5, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 6, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 7, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 8, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16* 9, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16*10, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16*11, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16*12, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16*13, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16*14, _literal), \
	METASTRING_GET_16_CHARS_AT(_base + 16*15, _literal)

// Subtract one from sizeof(...) to account for null terminator
#define MAKE_METASTRING_16(_literal) \
	First<sizeof(_literal)-1>(::estp::_metastring::CheckMetaStringMaxLen<sizeof(_literal)-1 <= 16>(\
		::estp::MetaString<METASTRING_GET_16_CHARS_AT(0,_literal)>{}))

// Subtract one from sizeof(...) to account for null terminator
#define MAKE_METASTRING_64(_literal) \
	First<sizeof(_literal)-1>(::estp::_metastring::CheckMetaStringMaxLen<sizeof(_literal)-1 <= 64>(\
		::estp::MetaString<METASTRING_GET_64_CHARS_AT(0,_literal)>{}))

// Subtract one from sizeof(...) to account for null terminator
#define MAKE_METASTRING_256(_literal) \
	First<sizeof(_literal)-1>(::estp::_metastring::CheckMetaStringMaxLen<sizeof(_literal)-1 <= 256>(\
		::estp::MetaString<METASTRING_GET_256_CHARS_AT(0,_literal)>{}))


// This can *really* slow down compilation times, so use sparingly
#ifdef ESTP_ENABLE_METASTRING_1024

#define METASTRING_CHARS_AT_1024(_base, _literal) \
	METASTRING_GET_256_CHARS_AT(_base + 256*0, _literal), \
	METASTRING_GET_256_CHARS_AT(_base + 256*1, _literal), \
	METASTRING_GET_256_CHARS_AT(_base + 256*2, _literal), \
	METASTRING_GET_256_CHARS_AT(_base + 256*3, _literal)

#define MAKE_METASTRING_1024(_literal) \
	Strip(::estp::_metastring::CheckMetaStringMaxLen<sizeof(_literal)-1 <= 1024>(\
		::estp::MetaString<METASTRING_GET_1024_CHARS_AT(0,_literal)>{}))

#endif

#ifndef METASTRING_DEFAULT_SIZE
#define METASTRING_DEFAULT_SIZE 64
#endif

#if METASTRING_DEFAULT_SIZE <= 16
#define MAKE_METASTRING(_literal) MAKE_METASTRING_16(_literal)
#elif METASTRING_DEFAULT_SIZE <= 64
#define MAKE_METASTRING(_literal) MAKE_METASTRING_64(_literal)
#else
#define MAKE_METASTRING(_literal) MAKE_METASTRING_256(_literal)
#endif

} // namespace estp

