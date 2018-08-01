
#include "base/assert.h"
#include "base/macros.h"

namespace estp {

static AssertionHandler user_assertion_handler{nullptr};

AssertionHandler SetAssertionHandler(AssertionHandler handler) {
	auto old_handler = user_assertion_handler;
	user_assertion_handler = handler;
	return old_handler;
}

AssertionHandler GetAssertionHandler() {
	return user_assertion_handler;
}

// Calls the configured assert handler callback.
void HandleFailedAssertion(FailedAssertion info) {
	// We use this flag to catch assertion failures that may occur while executing the
	// user-installed insertion handler
	static bool handling_assertion = false;

	// We've recursed into this function (via a nested assertion failure)
	if(handling_assertion) {
		return;
	}

	handling_assertion = true;
	if (user_assertion_handler) {
		(*user_assertion_handler)(info);
	}
	// If we get here there either is no user_assertion_handler set or it returned for some reason
	// The only safe thing to do is hang
	for(;;)
		;
}



} // namespace estp
