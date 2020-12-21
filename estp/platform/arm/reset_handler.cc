
#include <cstdint>

#include "estp/base/macros.hh"

namespace estp {

extern "C" {

using InitFunction = void (*)(void);

extern uint32_t const __data_load_start;
extern uint32_t __data_start;
extern uint32_t __data_end;

extern uint32_t __bss_start;
extern uint32_t __bss_end;

extern InitFunction __preinit_array_start, __preinit_array_end;
extern InitFunction __init_array_start, __init_array_end;

int main(void);

// Provide a weak implementation of the CMSIS SystemInit function
// in case the user does not provide one.
// Separate the definition from the declaration so that the symbol can be WEAK
WEAK void SystemInit(void);
void SystemInit() {}

void Reset_Handler() {
	// Copy DATA section
	{
		uint32_t const *src = &__data_load_start;
		uint32_t *dest = &__data_start;
		while (dest != &__data_end) {
			*dest++ = *src++;
		}
	}

	// Zero-fill BSS
	for (uint32_t *dest = &__bss_start; dest != &__bss_end;) {
		*dest++ = 0;
	}

	// Modern GCC uses init_array (and fini_array) constructs
	// instead of the old-style _init() function
	// These replace a call to __libc_init_array()
	for (InitFunction *f = &__preinit_array_start; f != &__preinit_array_end; ++f) {
		(*f)();
	}

	for (InitFunction *f = &__init_array_start; f != &__init_array_end; ++f) {
		(*f)();
	}

    // For CMSIS compliance
    SystemInit();

	// Let 'er rip
	(void) main();

	// Nothing else to do
	for(;;) {}
}

} // extern "C"
} // namespace estp
