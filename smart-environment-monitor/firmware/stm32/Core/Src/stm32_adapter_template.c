/*
 * STM32 HAL adapter template.
 *
 * Copy this file into a CubeMX-generated project and replace every TODO
 * with the corresponding hardware operation.
 */

#include "environment_monitor.h"
#include "config.h"

/* Include CubeMX headers here, for example:
 * #include "main.h"
 * #include "i2c.h"
 * #include "usart.h"
 */

void smart_environment_monitor_run_once(void) {
    environment_data_t data = {0};
    char telemetry[MONITOR_JSON_BUFFER_SIZE];
    static environment_monitor_t monitor;
    static int initialized = 0;

    if (!initialized) {
        environment_monitor_init(&monitor);
        initialized = 1;
    }

    /* TODO: read DHT11 and BH1750. */
    data.temperature_c = 0.0F;
    data.humidity_pct = 0.0F;
    data.light_lux = 0.0F;
    data.timestamp_ms = 0U;
    data.valid = false;

    const uint32_t alarm_mask = environment_monitor_process(
        &monitor,
        &data,
        telemetry,
        sizeof(telemetry)
    );

    /* TODO: update OLED, LED, buzzer and UART. */
    (void)alarm_mask;
    (void)telemetry;
}
