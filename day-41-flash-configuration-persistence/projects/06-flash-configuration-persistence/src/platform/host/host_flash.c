#include "host_flash.h"
#include <string.h>

void host_flash_init(host_flash_t *flash)
{
    memset(flash, 0, sizeof(*flash));
}

bool host_flash_read(void *context, config_slot_id_t slot, config_record_t *record)
{
    host_flash_t *f = (host_flash_t *)context;
    if (f == NULL || record == NULL || slot > CONFIG_SLOT_B) return false;
    f->read_count++;
    if (!f->programmed[slot]) return false;
    *record = f->slots[slot];
    return true;
}

bool host_flash_erase(void *context, config_slot_id_t slot)
{
    host_flash_t *f = (host_flash_t *)context;
    if (f == NULL || slot > CONFIG_SLOT_B) return false;
    memset(&f->slots[slot], 0xFF, sizeof(f->slots[slot]));
    f->programmed[slot] = false;
    f->erase_count++;
    return true;
}

bool host_flash_write(void *context, config_slot_id_t slot, const config_record_t *record)
{
    host_flash_t *f = (host_flash_t *)context;
    if (f == NULL || record == NULL || slot > CONFIG_SLOT_B) return false;
    if (f->fail_next_write) { f->fail_next_write = false; return false; }
    f->slots[slot] = *record;
    f->programmed[slot] = true;
    f->write_count++;
    return true;
}

void host_flash_corrupt_crc(host_flash_t *flash, config_slot_id_t slot)
{
    if (flash == NULL || slot > CONFIG_SLOT_B || !flash->programmed[slot]) return;
    flash->slots[slot].crc32 ^= 0x00000001U;
}
