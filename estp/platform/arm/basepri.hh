#pragma once

#include "estp/base/macros.hh"
#include <cstdint>

namespace estp {

// Get the current BASEPRI value
uint32_t INLINE LoadBasePriority() {
  uint32_t result;
  asm volatile ("MRS %0, basepri" : "=r" (result) );
  return(result);
}

// Unconditionally set the BASEPRI value
void INLINE StoreBasePriority(uint32_t value) {
  asm volatile ("MSR basepri, %0" : : "r" (value) : "memory");
}

// Set the BASEPRI_MAX value
// Only interrupts with a priority value below the BASEPPRI_MAX will run
// When writing to BASEPRI_MAX, the BASEPRI register is only affected if either:
// - The new priority is non-zero and the current BASEPRI value is 0
// - The new priority is non-zero and is smaller (higher priority) than the current BASEPRI value.
void INLINE StoreMaxBasePriority(uint32_t value) {
  asm volatile ("MSR basepri_max, %0" : : "r" (value) : "memory");
}

} // namespace
