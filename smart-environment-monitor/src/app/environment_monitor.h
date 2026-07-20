#ifndef ENVIRONMENT_MONITOR_H
#define ENVIRONMENT_MONITOR_H

#include <stddef.h>
#include <stdint.h>
#include "environment_types.h"

typedef struct {
    alarm_thresholds_t thresholds;
    uint32_t last_alarm_mask;
} environment_monitor_t;

void environment_monitor_init(environment_monitor_t *monitor);

uint32_t environment_monitor_process(
    environment_monitor_t *monitor,
    const environment_data_t *data,
    char *telemetry_buffer,
    size_t telemetry_buffer_size
);

#endif
