#ifndef CONFIG_STORE_H
#define CONFIG_STORE_H
#include <stdbool.h>
#include <stdint.h>
#include "config/config_record.h"

typedef enum {
    CONFIG_SLOT_A = 0,
    CONFIG_SLOT_B = 1
} config_slot_id_t;

typedef struct {
    void *context;
    bool (*read_slot)(void *context, config_slot_id_t slot, config_record_t *record);
    bool (*erase_slot)(void *context, config_slot_id_t slot);
    bool (*write_slot)(void *context, config_slot_id_t slot, const config_record_t *record);
} config_flash_ops_t;

typedef struct {
    config_flash_ops_t flash;
    runtime_config_t current;
    uint32_t current_sequence;
    config_slot_id_t active_slot;
    bool loaded_from_flash;
    uint32_t save_count;
    uint32_t load_fallback_count;
    uint32_t invalid_slot_count;
} config_store_t;

bool config_store_init(config_store_t *store, const config_flash_ops_t *ops);
bool config_store_load(config_store_t *store);
bool config_store_save(config_store_t *store, const runtime_config_t *cfg);

#endif
