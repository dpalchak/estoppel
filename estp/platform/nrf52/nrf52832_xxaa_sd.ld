/* Linker script to configure memory regions. */

SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

MEMORY
{
  FLASH (rx) : ORIGIN = 0x00030000, LENGTH = 0x50000
  RAM (rwx) :  ORIGIN = 0x20002000, LENGTH = 0x0E000
}

INCLUDE "nrf5_sdk_libs.ld"
INCLUDE "nrf_common.ld"
