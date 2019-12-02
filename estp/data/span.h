#pragma once

#include "estp/base/assert.h"
#include "estp/base/casting.h"
#include "estp/base/meta.h"
#include "estp/base/types.h"

#include <algorithm>
#include <array>
#include <iterator>
#include <memory>
#include <utility>

namespace estp {

namespace _span {

template<typename C, typename T>
struct IsContainerConvertible : IsConvertible< ElementType<C>(*)[], T(*)[] > {};

template<typename Container, typename Element>
struct IsSpannable : And< HasSize<Container>, HasData<Container>,
    IsContainerConvertible<Container, Element> > {};

} // namespace _span

// Implementation of std::span<T>
template<typename T>
class Span {
public:
    using Element = T;
    using Value = Unqualified<T>;
    using Reference = T&;
    using Pointer = T*;
    using ConstPointer = T const *;
    using ConstReference = T const &;

    using Iterator = Pointer;
    using ConstIterator = ConstPointer;

    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

    using DifferenceType = typename std::iterator_traits<Iterator>::difference_type;

    using View = Span<AddConst<Element>>;

    constexpr Span(Pointer begin_, Index size_) : _begin{begin_}, _size{size_} {
        EXPECTS(begin_ && (size_ >= 0));
    }

    constexpr Span(Pointer begin_, Pointer end_) : Span{begin_, end_ - begin_} {}

    template<typename U, Index N>
    constexpr Span(U (&arr)[N]) : _begin{arr}, _size{N} {}

    template<typename U>
    constexpr Span(U (&arr)[0]) : _begin{arr}, _size{0} {}

    template<typename C, typename = EnableIf< _span::IsSpannable<C, Element> > >
    constexpr Span(C &c) : Span{std::data(c), narrow_cast<Index>(std::size(c))} {}

    template<typename C, typename = EnableIf< And< IsConst<Element>, _span::IsSpannable<C, Element> > > >
    constexpr Span(C const &c) : Span{std::data(c), narrow_cast<Index>(std::size(c))} {}

    template<typename U>
    constexpr Span(Span<U> const &other) : Span{other.begin(), other.size()} {}

    constexpr Span first(Index count) const {
        EXPECTS((0 <= count) && (count <= _size));
        return Span(kPrivate, _begin, count);
    }

    constexpr Span last(Index count) const {
        EXPECTS((0 <= count) && (count <= _size));
        return Span(kPrivate, _begin + _size - count, count);
    }

    constexpr Span subspan(Index offset) const {
        EXPECTS((0 <= offset) && (offset <= _size));
        return Span(kPrivate, _begin + offset, _size - offset);
    }

    constexpr Span subspan(Index offset, Index count) const {
        EXPECTS((0 <= offset) && (offset <= _size));
        EXPECTS((0 <= count)  && (offset + count <= _size));
        return Span(kPrivate, _begin + offset, count);
    }
    constexpr Index size() const {
        return _size;
    }

    constexpr Index size_bytes() const {
        return _size * narrow_cast<Index>(sizeof(Element));
    }

    constexpr bool empty() const {
        return 0 == _size;
    }

    constexpr Reference operator[](Index index) const {
       return at(index);
    }

    constexpr Reference operator()(Index index) const {
       return at(index);
    }

    // Allow negative indices as in Python
    constexpr Reference at(Index index) const {
       EXPECTS((0 <= index) && (index < _size));
       return _begin[index];
    }

    constexpr Pointer data() const noexcept {
        return _begin;
    }

    constexpr Iterator begin() const noexcept{
        return {_begin};
    }

    constexpr Iterator end() const noexcept {
        return {_begin + _size};
    }

    constexpr ConstIterator cbegin() const noexcept {
        return {begin()};
    }

    constexpr ConstIterator cend() const noexcept {
        return {end()};
    }

    constexpr ReverseIterator rbegin() const noexcept {
        return ReverseIterator(end());
    }

    constexpr ReverseIterator rend() const noexcept {
        return ReverseIterator(begin());
    }

    constexpr ConstReverseIterator crbegin() const noexcept {
        return ConstReverseIterator(cend());
    }

    constexpr ConstReverseIterator crend() const noexcept {
        return ConstReverseIterator(cbegin());
    }

    void swap(Span &other) noexcept {
        using std::swap;
        swap( _begin, other._begin);
        swap( _size , other._size );
    }

    template<typename U>
    Span<U> as_span() const noexcept {
        EXPECTS(( this->size_bytes() % narrow_cast<Index>(sizeof(U)) ) == 0);
        return Span<U>{reinterpret_cast<U*>(_begin),
            this->size_bytes() / range_cast<Index>(sizeof(U))};
    }

    constexpr operator View() const {
        return View{View::kPrivate, ConstPointer{_begin}, _size};
    }

    constexpr View view() const {
        return static_cast<View>(*this);
    }

private:
    struct PrivateTag {};
    constexpr static PrivateTag kPrivate{};

    // Constructors that don't check arguments
    // This is used by member functions only
    constexpr Span(PrivateTag, Pointer begin_, Index size_) : _begin(begin_), _size(size_) {}
    constexpr Span(PrivateTag, Pointer begin_, Pointer end_)
        : _begin(begin_), _size(end_ - begin_) {}

    template<typename U>
    friend class Span;

    Pointer _begin;
    Index _size;
};

// Type deduction helpers
template<typename Container>
Span(Container&) -> Span<ElementType<Container>>;

template<typename Container>
Span(Container const &) -> Span<ElementType<Container> const>;

template<typename T, auto N>
Span(T(&)[N]) -> Span<T>;

template<typename T, auto N>
Span(T const (&)[N]) -> Span<T const>;


template<typename T>
constexpr decltype(auto) at(Span<T> sp, Index index) {
    return sp.at(index);
}

template<typename T, typename U>
constexpr bool operator==(Span<T> const &lhs, Span<U> const &rhs) {
    return lhs.size() == rhs.size()
        && (lhs.begin() == rhs.begin() || std::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

// Comparison operators
template<typename T, typename U>
constexpr bool operator!=(Span<T> const &lhs, Span<U> const &rhs) {
    return !(lhs == rhs);
}

template<typename T, typename U>
constexpr bool operator<(Span<T> const &lhs, Span<U> const &rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, typename U>
constexpr bool operator>(Span<T> const &lhs, Span<U> const &rhs) {
    return (rhs < lhs);
}

template<typename T, typename U>
constexpr bool operator>=(Span<T> const &lhs, Span<U> const &rhs) {
    return !(lhs < rhs);
}

template<typename T, typename U>
constexpr bool operator<=(Span<T> const &lhs, Span<U> const &rhs) {
    return !(lhs > rhs);
}

// Algorithm support
template<typename T, typename U>
inline void copy(Span<T> src, Span<U> dest) noexcept {
    static_assert(std::is_assignable<U&, T const &>::value, "Incompatible element types");
    EXPECTS(dest.size() >= src.size());
    std::copy_n(src.data(), src.size(), dest.data());
}

template<typename T>
inline Span<std::byte const> as_bytes(Span<T> sp) noexcept {
    return Span<std::byte const>(reinterpret_cast<std::byte const *>(sp.data()), sp.size_bytes());
}

template<typename T>
inline Span<std::byte> as_writeable_bytes(Span<T> sp) noexcept {
    return Span<std::byte>(reinterpret_cast<std::byte*>(sp.data()), sp.size_bytes());
}

} //namespace estp
