#include "boot/bootloader.h"
void bootloader_init(bootloader_t*b){if(!b)return;b->mode=BOOT_APP;b->candidate.state=IMAGE_EMPTY;b->active.version=1;b->active.state=IMAGE_VALID;b->boot_attempts=0;}
bool bootloader_begin_update(bootloader_t*b,uint32_t v,uint32_t s){if(!b||v<=b->active.version||!s)return false;b->candidate=(firmware_image_t){v,s,0,IMAGE_DOWNLOADING};b->mode=BOOT_UPDATE;return true;}
bool bootloader_finish_download(bootloader_t*b,uint32_t c){if(!b||b->candidate.state!=IMAGE_DOWNLOADING)return false;b->candidate.crc32=c;b->candidate.state=IMAGE_READY;return true;}
bool bootloader_validate_candidate(bootloader_t*b,uint32_t c){if(!b||b->candidate.state!=IMAGE_READY)return false;if(c!=b->candidate.crc32){b->candidate.state=IMAGE_INVALID;b->mode=BOOT_RECOVERY;return false;}b->candidate.state=IMAGE_VALID;return true;}
bool bootloader_confirm_candidate(bootloader_t*b){if(!b||b->candidate.state!=IMAGE_VALID)return false;b->active=b->candidate;b->candidate.state=IMAGE_EMPTY;b->mode=BOOT_APP;b->boot_attempts=0;return true;}
boot_mode_t bootloader_select_mode(const bootloader_t*b){if(!b)return BOOT_RECOVERY;if(b->candidate.state==IMAGE_INVALID)return BOOT_RECOVERY;if(b->candidate.state==IMAGE_READY)return BOOT_UPDATE;return BOOT_APP;}
