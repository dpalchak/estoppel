#pragma once

#include "estp/base/meta.h"
#include "estp/base/types.h"

#include <array>

namespace estp {

template<char... Chars>
struct TypeString  {
    // These static members are intended for monostate usage (aka value usage)
    constexpr static Index kLength {sizeof...(Chars)};

    // Include a null terminator for compatibility with normal string-handling functions
    constexpr static std::array<char const, sizeof...(Chars)+1> kValue = {Chars..., '\0'};

    constexpr static CZString cbegin() {
        return kValue.cbegin();
    }

    constexpr static CZString cend() {
        return kValue.cend();
    }

    constexpr static CZString data() {
        return kValue.data();
    }

    constexpr static Index size() {
        return kLength;
    }

    constexpr static char at(Index i) {
        // Use direct indexing instead of the .at() method to avoid compiler warning about
        // signed vs unsigned value (Our Index type is signed)
        return data()[i];
    }
};

constexpr TypeString<> kEmptyTypeString{};

inline namespace literals {
template<typename T, T... C>
constexpr auto operator"" _type() -> std::enable_if_t<std::is_same_v<T,char>, TypeString<C...>> {
    return {};
}

} // namespace literals

// Return a string composed of the characters at the specified indicies
template<char... Chars, Index... Is>
constexpr auto At(TypeString<Chars...>, IndexSequence<Is...>) {
    if constexpr (0 == sizeof...(Is)) {
        return kEmptyTypeString;
    } else {
        constexpr auto kString = TypeString<Chars...>{};
        return TypeString<kString.at(Is)...>{};
    }
}

// Return the substring between indices [Start, End)
template<char... Chars, Index Start, Index End>
constexpr auto Substring(TypeString<Chars...>, IndexConstant<Start>, IndexConstant<End>) {
    if constexpr (Start == End) {
        return kEmptyTypeString;
    } else {
        static_assert((Start >= 0) && (Start < sizeof...(Chars)), "Start index out of range");
        static_assert((End >= Start) && (End <= sizeof...(Chars)), "End index out of range");
        return At(TypeString<Chars...>{}, MakeOffsetIndexSequence<Start, End-Start>{});
    }
}

// Return the first N characters as a TypeString
template<char... Chars, Index N>
constexpr auto First(TypeString<Chars...>, IndexConstant<N>) {
    if constexpr (0 == N) {
        return kEmptyTypeString;
    } else {
        return Substring(TypeString<Chars...>{}, IndexConstant<0>{}, IndexConstant<N>{});
    }
}

// Return the last N characters in a TypeString
template<char... Chars, Index N>
constexpr auto Last(TypeString<Chars...>, IndexConstant<N>) {
    if constexpr (0 == N) {
        return kEmptyTypeString;
    } else {
	    return Substring(TypeString<Chars...>{}, IndexConstant<sizeof...(Chars)-N>{},
            IndexConstant<sizeof...(Chars)>{});
    }
}

// Return the substring between indices [Start, end-of-string)
// This is sort of the complement to Last()
template<char... Chars, Index Start>
constexpr auto From(TypeString<Chars...>, IndexConstant<Start>) {
    constexpr Index End = sizeof...(Chars);
    return Substring(TypeString<Chars...>{}, Index_k<Start>, Index_k<End>);
}

// Join TypeStrings with separator TypeString
template<char... Sep, char... Chars>
constexpr auto Join(TypeString<Sep...>, TypeString<Chars...>) {
	return TypeString<Chars...>{};
}

template<char... Sep, char... First, char... Second, typename... Rest>
constexpr auto Join(TypeString<Sep...>, TypeString<First...>, TypeString<Second...>, Rest...) {
	return Join(TypeString<Sep...>{}, TypeString<First...,Sep...,Second...>{}, Rest{}...);
}

// Join TypeStrings with single char
template<char Sep, typename... Strings>
constexpr auto Join(CharConstant<Sep>, Strings...) {
	return Join(TypeString<Sep>{}, Strings{}...);
}

// Concatenate multiple TypeStrings
template<char... First, typename... Rest>
constexpr auto Concatenate(TypeString<First...>, Rest...) {
	return Join(kEmptyTypeString, TypeString<First...>{}, Rest{}...);
}

namespace _typestring {
// Find first instance of character
template<char C, char... Chars>
constexpr Index Find(TypeString<Chars...>, CharConstant<C>) {
    constexpr TypeString<Chars...> kStr{};
    constexpr Index kSize{sizeof...(Chars)};
    if constexpr (0 == kSize) {
        return -1;
    } else {
        for(Index i=0; i<kSize; i++) {
            if (C == kStr.at(i)) {
                return i;
            }
        }
        return -1;
    }
}

// Find first instance of character
template<char C, char... Chars>
constexpr Index ReverseFind(TypeString<Chars...>, CharConstant<C>) {
    constexpr TypeString<Chars...> kStr{};
    constexpr Index kSize{sizeof...(Chars)};
    if constexpr (0 == kSize) {
        return -1;
    } else {
        for(Index i=kSize-1; i>=0; i--) {
            if (C == kStr.at(i)) {
                return i;
            }
        }
        return -1;
    }
}

} //namespace _typestring

// Find the first instance of the character
template<char C, char... Chars>
constexpr auto Find(TypeString<Chars...>, CharConstant<C>) {
    return IndexConstant<_typestring::Find(TypeString<Chars...>{}, CharConstant<C>{})>{};
}

// Find the last instance of the character
template<char C, char... Chars>
constexpr auto ReverseFind(TypeString<Chars...>, CharConstant<C>) {
    return IndexConstant<_typestring::ReverseFind(TypeString<Chars...>{}, CharConstant<C>{})>{};
}

// Return all characters preceeding the first separator
template<char SEP, char... Chars>
constexpr auto Prefix(TypeString<Chars...>, CharConstant<SEP>) {
    constexpr auto kString = TypeString<Chars...>{};
    if constexpr (kEmptyTypeString == kString) {
        return kEmptyTypeString;
    } else {
        constexpr auto kSepIndex = Find(kString, Char_k<SEP>);
        if constexpr (Index_k<-1> == kSepIndex) {
            // Separator was not found, so the entire string is considered the prefix
            return kString;
        } else {
            return First(kString, kSepIndex);
        }
    }
}

// Return all characters following the last separator
template<char SEP, char... Chars>
constexpr auto Suffix(TypeString<Chars...>, CharConstant<SEP>) {
    constexpr auto kString = TypeString<Chars...>{};
    if constexpr (kEmptyTypeString == kString) {
        return kEmptyTypeString;
    } else {
        constexpr auto kSepIndex = ReverseFind(kString, Char_k<SEP>);
        if constexpr (Index_k<-1> == kSepIndex) {
            // Separator was not found, so the entire string is considered the suffix
            return kString;
        } else {
            return From(kString, Index_k<1 + kSepIndex.value>);
        }
    }
}

// Comparison operators
template<char... LHS, char... RHS>
constexpr bool operator==(TypeString<LHS...>, TypeString<RHS...>) {
	return false;
}

template<char... Chars>
constexpr bool operator==(TypeString<Chars...>, TypeString<Chars...>) {
	return true;
}

template<char... LHS, char... RHS>
constexpr bool operator!=(TypeString<LHS...>, TypeString<RHS...>) {
	return true;
}

template<char... Chars>
constexpr bool operator!=(TypeString<Chars...>, TypeString<Chars...>) {
	return false;
}


} // namespace estp
