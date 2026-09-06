#include "config/config_record.h"
#include "config/crc32.h"
#include <stddef.h>
#include <string.h>

static uint32_t record_crc(const config_record_t *record)
{
    return crc32_ieee(record, offsetof(config_record_t, crc32));
}

void config_record_build(config_record_t *record, const runtime_config_t *cfg, uint32_t sequence)
{
    if (record == NULL || cfg == NULL) return;
    memset(record, 0, sizeof(*record));
    record->magic = CONFIG_MAGIC;
    record->version = CONFIG_VERSION;
    record->payload_size = (uint16_t)sizeof(runtime_config_t);
    record->sequence = sequence;
    record->config = *cfg;
    record->crc32 = record_crc(record);
}

bool config_record_validate(const config_record_t *record)
{
    if (record == NULL) return false;
    if (record->magic != CONFIG_MAGIC) return false;
    if (record->version != CONFIG_VERSION) return false;
    if (record->payload_size != sizeof(runtime_config_t)) return false;
    if (!runtime_config_validate(&record->config)) return false;
    return record->crc32 == record_crc(record);
}
