#pragma once

#include "base/macros.h"
#include "base/types.h"
#include "data/meta_string.h"

namespace estp {

struct AssertionContext {
	CZString condition = "";
	CZString filename = "";
	unsigned line = 0;
};

// Assertion handler
using AssertionHandler = void (*)(AssertionContext const &);

AssertionHandler SetAssertionHandler(AssertionHandler handler);
AssertionHandler GetAssertionHandler();

// Calls the configured assert handler callback.
void HandleFailedAssertion(AssertionContext failure);

#ifndef FILE_NAME
#define FILE_NAME __FILE__
#endif

#ifndef ESTP_ASSERT_FULL_NAME
#define ESTP_ASSERT_FULL_NAME 0
#endif

#if ESTP_ASSERT_FULL_NAME
#  define ASSERT_FILENAME FILE_NAME
#else
#  define ASSERT_FILENAME ::estp::RGet<0>(::estp::Split<'/'>(MAKE_METASTRING_256(FILE_NAME)))
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
