#include <stdio.h>
#include "config/config_store.h"
#include "host_flash.h"

static const char *slot_name(config_slot_id_t slot) { return slot == CONFIG_SLOT_A ? "A" : "B"; }

int main(void)
{
    host_flash_t flash;
    host_flash_init(&flash);
    config_flash_ops_t ops = { &flash, host_flash_read, host_flash_erase, host_flash_write };
    config_store_t store;
    if (!config_store_init(&store, &ops)) return 1;

    const bool first_load = config_store_load(&store);
    printf("boot1 load=%s source=DEFAULT hot_on=%.1f hold=%lu\n",
           first_load ? "flash" : "default", store.current.hot_on_c, (unsigned long)store.current.min_hold_ms);

    runtime_config_t cfg = store.current;
    cfg.hot_on_c = 31.5f;
    cfg.min_hold_ms = 1500U;
    printf("save1 ok=%s\n", config_store_save(&store, &cfg) ? "yes" : "no");
    printf("active=%s seq=%lu hot_on=%.1f hold=%lu\n",
           slot_name(store.active_slot), (unsigned long)store.current_sequence,
           store.current.hot_on_c, (unsigned long)store.current.min_hold_ms);

    cfg.hot_on_c = 32.0f;
    printf("save2 ok=%s\n", config_store_save(&store, &cfg) ? "yes" : "no");
    printf("active=%s seq=%lu hot_on=%.1f\n", slot_name(store.active_slot),
           (unsigned long)store.current_sequence, store.current.hot_on_c);

    config_store_t reboot;
    config_store_init(&reboot, &ops);
    printf("boot2 load=%s\n", config_store_load(&reboot) ? "flash" : "default");
    printf("recovered active=%s seq=%lu hot_on=%.1f hold=%lu\n",
           slot_name(reboot.active_slot), (unsigned long)reboot.current_sequence,
           reboot.current.hot_on_c, (unsigned long)reboot.current.min_hold_ms);

    host_flash_corrupt_crc(&flash, reboot.active_slot);

    config_store_t corrupted;
    config_store_init(&corrupted, &ops);
    printf("boot3_after_corruption load=%s\n", config_store_load(&corrupted) ? "flash" : "default");
    printf("fallback active=%s seq=%lu hot_on=%.1f fallback_count=%lu invalid_slots=%lu\n",
           slot_name(corrupted.active_slot), (unsigned long)corrupted.current_sequence,
           corrupted.current.hot_on_c, (unsigned long)corrupted.load_fallback_count,
           (unsigned long)corrupted.invalid_slot_count);

    runtime_config_t fail_cfg = corrupted.current;
    fail_cfg.hot_on_c = 33.0f;
    flash.fail_next_write = true;
    printf("write_failure save=%s preserved_seq=%lu preserved_hot_on=%.1f\n",
           config_store_save(&corrupted, &fail_cfg) ? "yes" : "no",
           (unsigned long)corrupted.current_sequence, corrupted.current.hot_on_c);

    printf("summary erases=%lu writes=%lu reads=%lu saves=%lu\n",
           (unsigned long)flash.erase_count, (unsigned long)flash.write_count,
           (unsigned long)flash.read_count, (unsigned long)store.save_count);
    return 0;
}
