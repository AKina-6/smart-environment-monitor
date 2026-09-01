#ifndef ENVIRONMENT_SERVICE_H
#define ENVIRONMENT_SERVICE_H
#include <stdbool.h>
#include <stdint.h>
#include "sensor/sensor_types.h"

typedef enum {
    ENV_STATE_NORMAL = 0,
    ENV_STATE_DARK,
    ENV_STATE_HOT,
    ENV_STATE_DEGRADED,
    ENV_STATE_FAULT
} environment_state_t;

typedef struct {
    float hot_threshold_c;
    float dark_threshold_lux;
    uint32_t degraded_count;
    uint32_t fault_count;
    environment_state_t last_state;
} environment_service_t;

void environment_service_init(environment_service_t *service, float hot_threshold_c, float dark_threshold_lux);
environment_state_t environment_service_evaluate(environment_service_t *service, const sensor_snapshot_t *snapshot);
const char *environment_state_name(environment_state_t state);

#endif
