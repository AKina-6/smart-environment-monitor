#include "config/config_store.h"
#include <stddef.h>

bool config_store_init(config_store_t *store, const config_flash_ops_t *ops)
{
    if (store == NULL || ops == NULL || ops->read_slot == NULL || ops->erase_slot == NULL || ops->write_slot == NULL)
        return false;
    store->flash = *ops;
    runtime_config_default(&store->current);
    store->current_sequence = 0U;
    store->active_slot = CONFIG_SLOT_A;
    store->loaded_from_flash = false;
    store->save_count = 0U;
    store->load_fallback_count = 0U;
    store->invalid_slot_count = 0U;
    return true;
}

bool config_store_load(config_store_t *store)
{
    if (store == NULL) return false;
    config_record_t a, b;
    const bool read_a = store->flash.read_slot(store->flash.context, CONFIG_SLOT_A, &a);
    const bool read_b = store->flash.read_slot(store->flash.context, CONFIG_SLOT_B, &b);
    const bool valid_a = read_a && config_record_validate(&a);
    const bool valid_b = read_b && config_record_validate(&b);

    if (!valid_a) store->invalid_slot_count++;
    if (!valid_b) store->invalid_slot_count++;

    const config_record_t *best = NULL;
    config_slot_id_t slot = CONFIG_SLOT_A;

    if (valid_a && valid_b) {
        if ((int32_t)(b.sequence - a.sequence) > 0) { best = &b; slot = CONFIG_SLOT_B; }
        else { best = &a; slot = CONFIG_SLOT_A; }
    } else if (valid_a) {
        best = &a; slot = CONFIG_SLOT_A;
        store->load_fallback_count++;
    } else if (valid_b) {
        best = &b; slot = CONFIG_SLOT_B;
        store->load_fallback_count++;
    } else {
        runtime_config_default(&store->current);
        store->current_sequence = 0U;
        store->active_slot = CONFIG_SLOT_A;
        store->loaded_from_flash = false;
        return false;
    }

    store->current = best->config;
    store->current_sequence = best->sequence;
    store->active_slot = slot;
    store->loaded_from_flash = true;
    return true;
}

bool config_store_save(config_store_t *store, const runtime_config_t *cfg)
{
    if (store == NULL || !runtime_config_validate(cfg)) return false;

    const config_slot_id_t target = store->active_slot == CONFIG_SLOT_A ? CONFIG_SLOT_B : CONFIG_SLOT_A;
    config_record_t record;
    config_record_build(&record, cfg, store->current_sequence + 1U);

    if (!store->flash.erase_slot(store->flash.context, target)) return false;
    if (!store->flash.write_slot(store->flash.context, target, &record)) return false;

    config_record_t verify;
    if (!store->flash.read_slot(store->flash.context, target, &verify)) return false;
    if (!config_record_validate(&verify)) return false;
    if (verify.sequence != record.sequence) return false;

    store->current = *cfg;
    store->current_sequence = record.sequence;
    store->active_slot = target;
    store->loaded_from_flash = true;
    store->save_count++;
    return true;
}
