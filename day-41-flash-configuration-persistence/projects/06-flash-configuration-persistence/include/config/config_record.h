#ifndef CONFIG_RECORD_H
#define CONFIG_RECORD_H
#include <stdbool.h>
#include <stdint.h>
#include "config/runtime_config.h"

#define CONFIG_MAGIC 0x43464731UL
#define CONFIG_VERSION 1U

typedef struct {
    uint32_t magic;
    uint16_t version;
    uint16_t payload_size;
    uint32_t sequence;
    runtime_config_t config;
    uint32_t crc32;
} config_record_t;

void config_record_build(config_record_t *record, const runtime_config_t *cfg, uint32_t sequence);
bool config_record_validate(const config_record_t *record);

#endif
