#ifndef SMART_ENV_MONITOR_TYPES_H
#define SMART_ENV_MONITOR_TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    float temperature_c;
    float humidity_pct;
    float light_lux;
    uint32_t timestamp_ms;
    bool valid;
} environment_data_t;

typedef struct {
    float temperature_high_c;
    float humidity_high_pct;
    float light_low_lux;
} alarm_thresholds_t;

typedef enum {
    ALARM_NONE          = 0U,
    ALARM_TEMP_HIGH     = 1U << 0,
    ALARM_HUMIDITY_HIGH = 1U << 1,
    ALARM_LIGHT_LOW     = 1U << 2,
    ALARM_SENSOR_FAULT  = 1U << 3
} alarm_flag_t;

#endif
