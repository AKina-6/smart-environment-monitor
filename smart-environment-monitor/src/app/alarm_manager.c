#include "alarm_manager.h"

uint32_t alarm_evaluate(
    const environment_data_t *data,
    const alarm_thresholds_t *thresholds
) {
    uint32_t alarm_mask = ALARM_NONE;

    if (data == 0 || thresholds == 0 || !data->valid) {
        return ALARM_SENSOR_FAULT;
    }

    if (data->temperature_c > thresholds->temperature_high_c) {
        alarm_mask |= ALARM_TEMP_HIGH;
    }

    if (data->humidity_pct > thresholds->humidity_high_pct) {
        alarm_mask |= ALARM_HUMIDITY_HIGH;
    }

    if (data->light_lux < thresholds->light_low_lux) {
        alarm_mask |= ALARM_LIGHT_LOW;
    }

    return alarm_mask;
}
