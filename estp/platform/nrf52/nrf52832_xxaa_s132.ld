/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x26000, LENGTH = 0x5a000
  RAM (rwx) :  ORIGIN = 0x200022f0, LENGTH = 0xdd10
}

INCLUDE "nrf5_sdk_libs.ld"
INCLUDE "nrf_common.ld"
