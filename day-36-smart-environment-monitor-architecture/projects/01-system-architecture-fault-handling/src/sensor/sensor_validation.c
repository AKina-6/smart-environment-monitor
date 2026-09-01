#include "sensor/sensor_validation.h"
#include <stddef.h>

sensor_health_t sensor_validate_temperature(float value)
{
    return (value >= -40.0f && value <= 80.0f) ? SENSOR_HEALTH_OK : SENSOR_HEALTH_RANGE_ERROR;
}

sensor_health_t sensor_validate_humidity(float value)
{
    return (value >= 0.0f && value <= 100.0f) ? SENSOR_HEALTH_OK : SENSOR_HEALTH_RANGE_ERROR;
}

sensor_health_t sensor_validate_light(float value)
{
    return (value >= 0.0f && value <= 100000.0f) ? SENSOR_HEALTH_OK : SENSOR_HEALTH_RANGE_ERROR;
}

void sensor_apply_stale_check(sensor_snapshot_t *snapshot, uint32_t now_ms, uint32_t stale_after_ms)
{
    if (snapshot == NULL) return;
    if ((uint32_t)(now_ms - snapshot->timestamp_ms) < stale_after_ms) return;

    if (snapshot->temp_health == SENSOR_HEALTH_OK) snapshot->temp_health = SENSOR_HEALTH_STALE;
    if (snapshot->humidity_health == SENSOR_HEALTH_OK) snapshot->humidity_health = SENSOR_HEALTH_STALE;
    if (snapshot->light_health == SENSOR_HEALTH_OK) snapshot->light_health = SENSOR_HEALTH_STALE;
}

bool sensor_snapshot_fully_healthy(const sensor_snapshot_t *snapshot)
{
    return snapshot != NULL &&
           snapshot->temp_health == SENSOR_HEALTH_OK &&
           snapshot->humidity_health == SENSOR_HEALTH_OK &&
           snapshot->light_health == SENSOR_HEALTH_OK;
}
