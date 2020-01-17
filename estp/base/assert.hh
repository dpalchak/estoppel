#pragma once

#include "estp/base/macros.hh"
#include "estp/base/types.hh"

#ifndef ASSERT_FILENAME
#  ifdef ESTP_ASSERT_BASENAME
#    include "estp/data/typestring.hh"
using namespace ::estp::literals;
namespace estp {

template<typename FILE>
static inline char const* GetBasenameAsCZString(FILE const) {
    constexpr static auto kBasename = ::estp::Suffix(FILE{}, ::estp::Char_k<'/'>);
    return kBasename.data();
}

} // namespace
#  define FILE_NAME __FILE__
#  define ASSERT_FILENAME ::estp::GetBasenameAsCZString(TOKEN_JOIN(FILE_NAME, _type))
#  else
#    define ASSERT_FILENAME __FILE__
#  endif
#endif

namespace estp {

struct AssertionContext {
	CZString condition = "";
	CZString filename = "";
	Index line = 0;
};

// Assertion handler
using AssertionHandler = void (*)(AssertionContext const &);

AssertionHandler SetAssertionHandler(AssertionHandler handler);
AssertionHandler GetAssertionHandler();

// Calls the configured assert handler callback.
void HandleFailedAssertion(AssertionContext failure);

#ifdef ASSERT
#undef ASSERT
COMPILE_MESSAGE("Redefining ASSERT()...")
#endif

#define ASSERT(...)                                                                   \
  do {                                                                                \
    if (!(__VA_ARGS__)) {                                                             \
      ::estp::HandleFailedAssertion({QUOTE(__VA_ARGS__), ASSERT_FILENAME, __LINE__}); \
    }                                                                                 \
  } while(false)

#define ASSERT_FAILURE() \
	::estp::HandleFailedAssertion({"ASSERT_FAILURE", ASSERT_FILENAME, __LINE__})


// These are identical in function to ASSERT(), but they express a different semantic meaning
// Specifically, these should be used for enforcing pre- and post-conditions
#define EXPECTS(...) ASSERT(__VA_ARGS__)
#define ENSURES(...) ASSERT(__VA_ARGS__)

// These are equivalent to EXPECTS and ENSURES, but only generate a conditional if DEBUG is defined
#ifdef DEBUG

#define ASSUMES(...) EXPECTS(__VA_ARGS__)
#define IMPLIES(...) ENSURES(__VA_ARGS__)

#else

#define ASSUMES(...) (void) __VA_ARGS__
#define IMPLIES(...) (void) __VA_ARGS__

#endif

} // namespace estp
