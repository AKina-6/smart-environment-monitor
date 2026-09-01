#ifndef ENVIRONMENT_APP_H
#define ENVIRONMENT_APP_H
#include <stdbool.h>
#include <stdint.h>
#include "sensor/sensor_types.h"
#include "service/environment_service.h"

typedef struct {
    bool fan_on;
    bool light_on;
    bool alarm_on;
    bool display_warning;
} actuator_command_t;

typedef struct {
    environment_service_t service;
    actuator_command_t last_command;
    uint32_t cycles;
} environment_app_t;

void environment_app_init(environment_app_t *app);
actuator_command_t environment_app_process(environment_app_t *app, const sensor_snapshot_t *snapshot);

#endif
