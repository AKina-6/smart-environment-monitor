#ifndef SENSOR_TYPES_H
#define SENSOR_TYPES_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SENSOR_HEALTH_OK = 0,
    SENSOR_HEALTH_STALE,
    SENSOR_HEALTH_RANGE_ERROR,
    SENSOR_HEALTH_IO_ERROR
} sensor_health_t;

typedef struct {
    float temperature_c;
    float humidity_pct;
    float light_lux;
    uint32_t timestamp_ms;
    sensor_health_t temp_health;
    sensor_health_t humidity_health;
    sensor_health_t light_health;
} sensor_snapshot_t;

#endif
