#pragma once

#include "estp/base/macros.hh"

#include <utility>

namespace estp {

template<typename F>
class FinalAction {
public:
    explicit FinalAction(F action) noexcept : _action(std::move(action)) {}

    FinalAction(FinalAction && other) noexcept
    	: _action(std::move(other._action)), _pending(other._pending) {
        other._pending = false;
    }

    ~FinalAction() noexcept {
        if (_pending) {
            _action();
        }
    }

    constexpr void dismiss() noexcept {
    	_pending = false;
    }

    // Disable move assignment (but not move construct)
    FinalAction& operator=(FinalAction &&) = delete;

private:
    F _action;
    bool _pending{true};

    DISABLE_COPY(FinalAction)
};

template<typename F>
inline FinalAction<F> finally(F const &action) noexcept {
    return FinalAction<F>(action);
}

template<typename F>
inline FinalAction<F> finally(F &&action) noexcept {
    return FinalAction<F>(std::forward<F>(action));
}


} // namespace estp
