/* STM32F103 integration sketch. Reserve two dedicated Flash pages in the linker layout. */
#include "config/config_store.h"
#include "stm32f1xx_hal.h"
#include <string.h>

#define CONFIG_SLOT_A_ADDR 0x0800F800UL
#define CONFIG_SLOT_B_ADDR 0x0800FC00UL

static uint32_t slot_address(config_slot_id_t slot)
{
    return slot == CONFIG_SLOT_A ? CONFIG_SLOT_A_ADDR : CONFIG_SLOT_B_ADDR;
}

static bool flash_read_slot(void *context, config_slot_id_t slot, config_record_t *record)
{
    (void)context;
    if (record == NULL) return false;
    memcpy(record, (const void *)slot_address(slot), sizeof(*record));
    return true;
}

static bool flash_erase_slot(void *context, config_slot_id_t slot)
{
    (void)context;
    FLASH_EraseInitTypeDef erase = {0};
    uint32_t page_error = 0U;
    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = slot_address(slot);
    erase.NbPages = 1U;

    if (HAL_FLASH_Unlock() != HAL_OK) return false;
    const HAL_StatusTypeDef st = HAL_FLASHEx_Erase(&erase, &page_error);
    (void)HAL_FLASH_Lock();
    return st == HAL_OK;
}

static bool flash_write_slot(void *context, config_slot_id_t slot, const config_record_t *record)
{
    (void)context;
    if (record == NULL) return false;
    const uint16_t *src = (const uint16_t *)record;
    uint32_t addr = slot_address(slot);
    const size_t halfwords = (sizeof(*record) + 1U) / 2U;

    if (HAL_FLASH_Unlock() != HAL_OK) return false;
    for (size_t i = 0U; i < halfwords; ++i) {
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr, src[i]) != HAL_OK) {
            (void)HAL_FLASH_Lock();
            return false;
        }
        addr += 2U;
    }
    (void)HAL_FLASH_Lock();
    return true;
}

bool stm32_config_store_init(config_store_t *store)
{
    const config_flash_ops_t ops = {
        .context = NULL,
        .read_slot = flash_read_slot,
        .erase_slot = flash_erase_slot,
        .write_slot = flash_write_slot
    };
    return config_store_init(store, &ops);
}
