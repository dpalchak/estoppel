#pragma once

#include "base/types.h"
#include "data/meta_string.h"

namespace estp {

struct FailedAssertion {
	CZString condition = "";
	CZString filename = "";
	unsigned line = 0;
	void const *context = nullptr;
};

// Assertion handler
using AssertionHandler = void (*)(FailedAssertion const &);

AssertionHandler SetAssertionHandler(AssertionHandler handler);
AssertionHandler GetAssertionHandler();

// Calls the configured assert handler callback.
void HandleFailedAssertion(FailedAssertion failure);

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

#define ASSERT(condition)                                                         \
  do {                                                                            \
    if (!(condition)) {                                                           \
      ::estp::HandleFailedAssertion({#condition, ASSERT_FILENAME, __LINE__, ""}); \
    }                                                                             \
  } while(false)

#define ASSERT_LOG(condition, message)          		                                 \
  do {                                                                                   \
    if (!(condition)) {                                                                  \
    	::estp::HandleFailedAssertion({#condition, ASSERT_FILENAME, __LINE__, message}); \
    }                                                                                    \
  } while(false)

#define ASSERT_FAILURE(message) \
	::estp::HandleFailedAssertion({"ASSERT_FAILURE", ASSERT_FILENAME, __LINE__, message})

} // namespace estp
