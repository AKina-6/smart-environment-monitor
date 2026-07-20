#include "environment_monitor.h"
#include "alarm_manager.h"
#include "telemetry.h"
#include "config.h"

void environment_monitor_init(environment_monitor_t *monitor) {
    if (monitor == 0) {
        return;
    }

    monitor->thresholds.temperature_high_c = MONITOR_TEMP_HIGH_C;
    monitor->thresholds.humidity_high_pct = MONITOR_HUMIDITY_HIGH_PCT;
    monitor->thresholds.light_low_lux = MONITOR_LIGHT_LOW_LUX;
    monitor->last_alarm_mask = ALARM_NONE;
}

uint32_t environment_monitor_process(
    environment_monitor_t *monitor,
    const environment_data_t *data,
    char *telemetry_buffer,
    size_t telemetry_buffer_size
) {
    if (monitor == 0 || data == 0) {
        return ALARM_SENSOR_FAULT;
    }

    monitor->last_alarm_mask = alarm_evaluate(data, &monitor->thresholds);

    if (telemetry_buffer != 0 && telemetry_buffer_size > 0U) {
        (void)telemetry_format_json(
            telemetry_buffer,
            telemetry_buffer_size,
            data,
            monitor->last_alarm_mask
        );
    }

    return monitor->last_alarm_mask;
}
