
#include "lib/base/macros.h"
#include <cstdint>

namespace estp {


extern "C" {
	extern uint32_t __stack_top;

	void NO_RETURN Default_Handler() {
		for(;;) {}
	}

	void Reset_Handler() NO_RETURN;
	void NMI_Handler() WEAK ALIAS("Default_Handler");
	void HardFault_Handler() WEAK ALIAS("Default_Handler");
	void MemManage_Handler() WEAK ALIAS("Default_Handler");
	void BusFault_Handler() WEAK ALIAS("Default_Handler");
	void UsageFault_Handler() WEAK ALIAS("Default_Handler");
	void SVC_Handler() WEAK ALIAS("Default_Handler");
	void DebugMon_Handler() WEAK ALIAS("Default_Handler");
	void PendSV_Handler() WEAK ALIAS("Default_Handler");
	void SysTick_Handler() WEAK ALIAS("Default_Handler");
}

// ARMv7x-M Exception Table
// Declare this extern "C" so the name does not get mangled
// This is so that we can reference this table directly in the linker script by name
using Vector = void (*)(void);

extern "C"
SECTION(".armcm4f_vector_table")
USED
Vector const kArmExceptionVectorTable[] = {
    // Initial vector is actually the initial stack pointer
	reinterpret_cast<Vector>(&__stack_top),
	Reset_Handler,
	NMI_Handler,
	HardFault_Handler,
	MemManage_Handler,
	BusFault_Handler,
	UsageFault_Handler,
	nullptr,
	nullptr,
	nullptr,
	nullptr,
	SVC_Handler,
	DebugMon_Handler,
	nullptr,
	PendSV_Handler,
	SysTick_Handler,
};


} // namespace estp
