/* STM32F103 IWDG integration sketch. Confirm LSI frequency on real hardware. */
#include "supervisor/supervisor.h"
#include "stm32f1xx_hal.h"

extern IWDG_HandleTypeDef hiwdg;
static fault_supervisor_t supervisor;

static reset_reason_t board_reset_reason(void)
{
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST)) return RESET_REASON_WATCHDOG;
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST)) return RESET_REASON_SOFTWARE;
    if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST)) return RESET_REASON_POWER_ON;
    return RESET_REASON_UNKNOWN;
}

void board_supervisor_init(void)
{
    reset_reason_t reason=board_reset_reason();
    __HAL_RCC_CLEAR_RESET_FLAGS();
    supervisor_init(&supervisor,reason);
    supervisor_configure_module(&supervisor,MODULE_SENSOR,600U,true);
    supervisor_configure_module(&supervisor,MODULE_CONTROL,600U,true);
    supervisor_configure_module(&supervisor,MODULE_UI,1500U,true);
    supervisor_configure_module(&supervisor,MODULE_TELEMETRY,1500U,false);
}

void board_supervisor_heartbeat(module_id_t module)
{
    supervisor_heartbeat(&supervisor,module,HAL_GetTick());
}

void board_supervisor_poll(void)
{
    if (supervisor_should_refresh_watchdog(&supervisor,HAL_GetTick())) {
        (void)HAL_IWDG_Refresh(&hiwdg);
    }
    /* When a required module misses its deadline, intentionally do not refresh.
       IWDG will reset the MCU if the fault persists. */
}
