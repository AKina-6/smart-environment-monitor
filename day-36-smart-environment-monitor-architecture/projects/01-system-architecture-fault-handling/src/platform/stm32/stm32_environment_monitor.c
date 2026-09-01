/*
 * STM32 integration skeleton for the layered environment monitor.
 *
 * Sensor Layer:
 *   DHT11/BH1750 drivers -> sensor_snapshot_t
 * Service Layer:
 *   validation + stale check + environment state
 * Application Layer:
 *   actuator policy
 * BSP:
 *   OLED / UART / servo-fan / LED / buzzer
 */

#include "sensor/sensor_validation.h"
#include "app/environment_app.h"
#include "stm32f1xx_hal.h"

static environment_app_t app;
static uint32_t last_sensor_ms = 0U;

extern bool dht11_read(float *temperature_c, float *humidity_pct);
extern bool bh1750_read_lux(float *lux);
extern void board_set_fan(bool on);
extern void board_set_light(bool on);
extern void board_set_alarm(bool on);
extern void board_show_warning(bool on);

void environment_monitor_init(void)
{
    environment_app_init(&app);
}

void environment_monitor_poll(void)
{
    const uint32_t now = HAL_GetTick();
    if ((uint32_t)(now - last_sensor_ms) < 1000U) {
        return;
    }
    last_sensor_ms = now;

    sensor_snapshot_t snapshot = {
        .timestamp_ms = now,
        .temp_health = SENSOR_HEALTH_IO_ERROR,
        .humidity_health = SENSOR_HEALTH_IO_ERROR,
        .light_health = SENSOR_HEALTH_IO_ERROR
    };

    float t = 0.0f, h = 0.0f, l = 0.0f;

    if (dht11_read(&t, &h)) {
        snapshot.temperature_c = t;
        snapshot.humidity_pct = h;
        snapshot.temp_health = sensor_validate_temperature(t);
        snapshot.humidity_health = sensor_validate_humidity(h);
    }

    if (bh1750_read_lux(&l)) {
        snapshot.light_lux = l;
        snapshot.light_health = sensor_validate_light(l);
    }

    const actuator_command_t cmd = environment_app_process(&app, &snapshot);

    board_set_fan(cmd.fan_on);
    board_set_light(cmd.light_on);
    board_set_alarm(cmd.alarm_on);
    board_show_warning(cmd.display_warning);
}
