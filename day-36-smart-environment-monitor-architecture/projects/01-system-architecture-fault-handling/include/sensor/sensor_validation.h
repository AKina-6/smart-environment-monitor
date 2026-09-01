#ifndef SENSOR_VALIDATION_H
#define SENSOR_VALIDATION_H
#include <stdbool.h>
#include <stdint.h>
#include "sensor/sensor_types.h"

sensor_health_t sensor_validate_temperature(float value);
sensor_health_t sensor_validate_humidity(float value);
sensor_health_t sensor_validate_light(float value);
void sensor_apply_stale_check(sensor_snapshot_t *snapshot, uint32_t now_ms, uint32_t stale_after_ms);
bool sensor_snapshot_fully_healthy(const sensor_snapshot_t *snapshot);

#endif
