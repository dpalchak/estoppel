#pragma once

#include "base/meta.h"

namespace estp {

template<typename...>
struct MetaList {};

using EmptyMetaList = MetaList<>;

template<typename T>
using MetaListItem = Type<T>;

////////////////////////////////////////////////////////////
// Length (Size)
template<typename... TL>
constexpr size_t Length(MetaList<TL...>) {
	return sizeof...(TL);
}

template<typename... TL>
constexpr size_t Size(MetaList<TL...>) {
	return sizeof...(TL);
}

////////////////////////////////////////////////////////////
// Indexing
template<size_t N>
constexpr auto GetT(EmptyMetaList) {
	static_assert(False<SizeT<N>>::value, "Index out of range");
}

template<size_t N, typename First, typename... Rest>
constexpr auto Get(MetaList<First, Rest...>) {
	static_assert(N < (1+sizeof...(Rest)), "Index out of range");
	if constexpr(0 == N) {
		return First{};
	} else {
		return Get<N-1>(MetaList<Rest...>{});
	}
}

template<typename... Items>
constexpr auto GetT(MetaList<Items...>) {
	return Type<decltype(Get(MetaList<Items...>{}))>{};
}

// Reverse Get
// Indexes from end of list
template<size_t N, typename... TL>
constexpr auto RGet(MetaList<TL...>) {
	static_assert(N < sizeof...(TL), "Index out of range");
	return Get<sizeof...(TL)-N-1>(MetaList<TL...>{});
}


template<typename... Items>
constexpr auto RGetT(MetaList<Items...>) {
	return Type<decltype(RGet(MetaList<Items...>{}))>{};
}

////////////////////////////////////////////////////////////
// First N
template<size_t N, typename... Head>
constexpr auto _First(MetaList<Head...>, EmptyMetaList) {
	static_assert(sizeof...(Head) <= N, "Invalid argument");
	return MetaList<Head...>{};
}

template<size_t N, typename... Head, typename Body, typename... Tail>
constexpr auto _First(MetaList<Head...>, MetaList<Body, Tail...>) {
	if constexpr(sizeof...(Head) < N) {
		return _First<N>(MetaList<Head..., Body>{}, MetaList<Tail...>{});
	} else {
		return MetaList<Head...>{};
	}
}

template<size_t N, typename... TL>
constexpr auto First(MetaList<TL...>) {
	return _First<N>(EmptyMetaList{}, MetaList<TL...>{});
}

////////////////////////////////////////////////////////////
// Last N
template<size_t N, typename... Head>
constexpr auto _Last(MetaList<Head...>, EmptyMetaList) {
	return EmptyMetaList{};
}

template<size_t N, typename... Head, typename Body, typename... Tail>
constexpr auto _Last(MetaList<Head...>, MetaList<Body, Tail...>) {
	if constexpr(1+sizeof...(Tail) > N) {
		return _Last<N>(MetaList<Head..., Body>{}, MetaList<Tail...>{});
	} else {
		return MetaList<Body, Tail...>{};
	}
}

template<size_t N, typename... TL>
constexpr auto Last(MetaList<TL...>) {
	return _Last<N>(EmptyMetaList{}, MetaList<TL...>{});
}

////////////////////////////////////////////////////////////
// Concatenation, Append, Prepend
template<typename... First, typename... Second, typename... Rest>
constexpr auto Concatenate(MetaList<First...>, MetaList<Second...>, Rest...) {
	if constexpr(0 == sizeof...(Rest)) {
		return MetaList<First..., Second...>{};
	} else {
		return Concatenate(MetaList<First..., Second...>{}, Rest{}...);
	}
};

template<typename... Items, typename T>
constexpr auto Append(MetaList<Items...>, T const&) {
	return MetaList<Items..., T>{};
}

template<typename... Items, typename T>
constexpr auto Prepend(MetaList<Items...>, T const&) {
	return MetaList<T, Items...>{};
}

////////////////////////////////////////////////////////////
// Filter
template<template<typename...> class Trait>
constexpr auto Filter(EmptyMetaList) {
	return EmptyMetaList{};
};

template<template<typename...> class Trait, typename First, typename... Rest>
constexpr auto Filter(MetaList<First, Rest...>) {
	if constexpr(Trait<First>::value) {
		return Concatenate(MetaList<First>{}, Filter<Trait>(MetaList<Rest...>{}));
	} else {
		return Filter<Trait>(MetaList<Rest...>{});
	}
};

////////////////////////////////////////////////////////////
// Comparison operators
template<typename... LHS, typename... RHS>
constexpr bool operator==(MetaList<LHS...>, MetaList<RHS...>) {
	return false;
}

template<typename... TL>
constexpr bool operator==(MetaList<TL...>, MetaList<TL...>) {
	return true;
}

template<typename... LHS, typename... RHS>
constexpr bool operator!=(MetaList<LHS...>, MetaList<RHS...>) {
	return !(MetaList<LHS...>{} == MetaList<RHS...>{});
}

template<typename T, typename S>
constexpr bool operator==(Type<T>, Type<S>) {
	return false;
}

template<typename T>
constexpr bool operator==(Type<T>, Type<T>) {
	return true;
}

} // namespace estp

