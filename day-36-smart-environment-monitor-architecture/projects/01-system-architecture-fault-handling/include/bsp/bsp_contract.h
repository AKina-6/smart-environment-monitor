#ifndef BSP_CONTRACT_H
#define BSP_CONTRACT_H
#include <stdbool.h>
#include "sensor/sensor_types.h"
#include "app/environment_app.h"

typedef struct {
    void *context;
    bool (*read_sensors)(void *context, sensor_snapshot_t *snapshot);
    void (*apply_actuators)(void *context, const actuator_command_t *command);
    void (*log_line)(void *context, const char *line);
} bsp_contract_t;

#endif
