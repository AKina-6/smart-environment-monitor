#include <stdio.h>
#include "boot/bootloader.h"
int main(void){bootloader_t b;bootloader_init(&b);printf("boot active=1 mode=APP\n");bootloader_begin_update(&b,2,4096);bootloader_finish_download(&b,0x12345678);printf("image READY\n");printf("validation=%s\n",bootloader_validate_candidate(&b,0x12345678)?"PASS":"FAIL");int confirmed = bootloader_confirm_candidate(&b);
printf("confirm=%s active_version=%u\n", confirmed ? "yes" : "no", b.active.version);bootloader_begin_update(&b,3,8192);bootloader_finish_download(&b,0xAA);printf("bad_validation=%s mode=%s active_version=%u\n",bootloader_validate_candidate(&b,0xBB)?"PASS":"FAIL",bootloader_select_mode(&b)==BOOT_RECOVERY?"RECOVERY":"APP",b.active.version);return 0;}
