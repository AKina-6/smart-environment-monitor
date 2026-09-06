#ifndef HOST_FLASH_H
#define HOST_FLASH_H
#include <stdbool.h>
#include "config/config_store.h"

typedef struct {
    config_record_t slots[2];
    bool programmed[2];
    bool fail_next_write;
    uint32_t erase_count;
    uint32_t write_count;
    uint32_t read_count;
} host_flash_t;

void host_flash_init(host_flash_t *flash);
bool host_flash_read(void *context, config_slot_id_t slot, config_record_t *record);
bool host_flash_erase(void *context, config_slot_id_t slot);
bool host_flash_write(void *context, config_slot_id_t slot, const config_record_t *record);
void host_flash_corrupt_crc(host_flash_t *flash, config_slot_id_t slot);

#endif
