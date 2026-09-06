#include <assert.h>
#include "config/config_store.h"
#include "host_flash.h"

int main(void)
{
    host_flash_t flash;
    host_flash_init(&flash);
    config_flash_ops_t ops = { &flash, host_flash_read, host_flash_erase, host_flash_write };
    config_store_t store;
    assert(config_store_init(&store, &ops));
    assert(!config_store_load(&store));
    assert(store.current.hot_on_c == 30.0f);

    runtime_config_t cfg = store.current;
    cfg.hot_on_c = 31.0f;
    assert(config_store_save(&store, &cfg));
    assert(store.current_sequence == 1U);
    assert(store.active_slot == CONFIG_SLOT_B);

    cfg.hot_on_c = 32.0f;
    assert(config_store_save(&store, &cfg));
    assert(store.current_sequence == 2U);
    assert(store.active_slot == CONFIG_SLOT_A);

    config_store_t reboot;
    assert(config_store_init(&reboot, &ops));
    assert(config_store_load(&reboot));
    assert(reboot.current_sequence == 2U);
    assert(reboot.current.hot_on_c == 32.0f);

    host_flash_corrupt_crc(&flash, CONFIG_SLOT_A);
    config_store_t fallback;
    assert(config_store_init(&fallback, &ops));
    assert(config_store_load(&fallback));
    assert(fallback.active_slot == CONFIG_SLOT_B);
    assert(fallback.current_sequence == 1U);
    assert(fallback.current.hot_on_c == 31.0f);
    return 0;
}
