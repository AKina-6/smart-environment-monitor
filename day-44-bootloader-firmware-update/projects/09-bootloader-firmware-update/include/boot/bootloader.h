#ifndef BOOTLOADER_H
#define BOOTLOADER_H
#include <stdbool.h>
#include <stdint.h>
typedef enum { BOOT_APP, BOOT_UPDATE, BOOT_RECOVERY } boot_mode_t;
typedef enum { IMAGE_EMPTY, IMAGE_DOWNLOADING, IMAGE_READY, IMAGE_VALID, IMAGE_INVALID } image_state_t;
typedef struct { uint32_t version,size,crc32; image_state_t state; } firmware_image_t;
typedef struct { boot_mode_t mode; firmware_image_t candidate,active; uint32_t boot_attempts; } bootloader_t;
void bootloader_init(bootloader_t*);
bool bootloader_begin_update(bootloader_t*,uint32_t,uint32_t);
bool bootloader_finish_download(bootloader_t*,uint32_t);
bool bootloader_validate_candidate(bootloader_t*,uint32_t);
bool bootloader_confirm_candidate(bootloader_t*);
boot_mode_t bootloader_select_mode(const bootloader_t*);
#endif
