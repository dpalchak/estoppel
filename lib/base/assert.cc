
#include "base/assert.h"
#include "base/macros.h"

namespace estp {

static AssertionHandler user_assertion_handler{nullptr};

// This is a weak symbol so that it can be replaced at link time
// if desired
WEAK void DefaultAssertionHandler(AssertionContext const &) {
	for(;;) {}
}

AssertionHandler SetAssertionHandler(AssertionHandler handler) {
	auto old_handler = user_assertion_handler;
	user_assertion_handler = handler;
	return old_handler;
}

AssertionHandler GetAssertionHandler() {
	return user_assertion_handler;
}

// Calls the configured assert handler callback.
void HandleFailedAssertion(AssertionContext const info) {
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
	} else {
		DefaultAssertionHandler(info);
	}
	// If we get here it's because the assertion handler returned
	// This typically shouldn't happen (except during unit testing)
	// So let's assume the best
	handling_assertion = false;
}



} // namespace estp
