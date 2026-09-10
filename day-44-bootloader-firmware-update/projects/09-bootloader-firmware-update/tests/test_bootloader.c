#include <assert.h>
#include "boot/bootloader.h"
int main(void){bootloader_t b;bootloader_init(&b);assert(b.active.version==1);assert(bootloader_begin_update(&b,2,4096));assert(bootloader_finish_download(&b,0x12345678));assert(bootloader_validate_candidate(&b,0x12345678));assert(bootloader_confirm_candidate(&b));assert(b.active.version==2);assert(bootloader_begin_update(&b,3,8192));assert(bootloader_finish_download(&b,0xAA));assert(!bootloader_validate_candidate(&b,0xBB));assert(b.active.version==2);assert(bootloader_select_mode(&b)==BOOT_RECOVERY);return 0;}
