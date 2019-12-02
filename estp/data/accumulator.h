#pragma once

#include "estp/base/assert.h"
#include "estp/base/macros.h"
#include "estp/base/types.h"
#include "estp/data/span.h"

#include <cstdint>
#include <type_traits>
#include <utility>

namespace estp {

template<typename T>
class Accumulator {
    static_assert(!std::is_const_v<T>, "Cannot accumulate const values");
public:
  using Value = T;
  using ConstValue = Value const;
  using Reference = Value&;
  using ConstReference = ConstValue&;

  constexpr Accumulator(Span<Value> storage) : _data(storage) {}

  constexpr INLINE Index fill_size() const { return _cursor; }
  constexpr INLINE Index empty_size() const { return _data.size() - _cursor; }
  constexpr INLINE bool full() const { return _data.size() == _cursor; }
  constexpr INLINE bool empty() const { return 0 == _cursor; }
  constexpr INLINE Index capacity() const { return _data.size(); }

  constexpr INLINE Span<Value> data() const {
    return Span<Value>{_data.begin(), _cursor};
  }

  INLINE void Reset() { _cursor = 0; }

  // Manipulators ASSUMES if buffer is empty/full as appropriate
  Reference Back();
  void PushBack(Value item);
  void PopBack();

  template<typename... Args>
  Reference EmplaceBack(Args&&... args);

private:
  Span<Value> _data;
  Index _cursor = 0;
};

template<typename T>
T& Accumulator<T>::Back() {
  ASSUMES(!empty());
  return _data[_cursor - 1];
}

template<typename T>
void Accumulator<T>::PopBack() {
  ASSUMES(!empty());
  _cursor--;
  _data[_cursor].~T();
}

template<typename T>
void Accumulator<T>::PushBack(Value item) {
  ASSUMES(!full());
  _data[_cursor++] = std::move(item);
}

template<typename T>
template<typename... Args>
T& Accumulator<T>::EmplaceBack(Args&&... args) {
  ASSUMES(!full());
  new (&_data[_cursor++]) T{std::forward<Args>(args)...};
  return Back();
}

template<typename T>
Accumulator(Span<T>) -> Accumulator<T>;


}  // Namespace
