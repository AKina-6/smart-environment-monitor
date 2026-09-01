#include "app/environment_app.h"
#include <stddef.h>

void environment_app_init(environment_app_t *app)
{
    if (app == NULL) return;
    environment_service_init(&app->service, 30.0f, 100.0f);
    app->last_command = (actuator_command_t){0};
    app->cycles = 0U;
}

actuator_command_t environment_app_process(environment_app_t *app, const sensor_snapshot_t *snapshot)
{
    actuator_command_t cmd = {0};
    if (app == NULL || snapshot == NULL) {
        cmd.alarm_on = true;
        cmd.display_warning = true;
        return cmd;
    }

    const environment_state_t state = environment_service_evaluate(&app->service, snapshot);

    switch (state) {
        case ENV_STATE_NORMAL:
            break;
        case ENV_STATE_DARK:
            cmd.light_on = true;
            break;
        case ENV_STATE_HOT:
            cmd.fan_on = true;
            break;
        case ENV_STATE_DEGRADED:
            cmd.display_warning = true;
            break;
        case ENV_STATE_FAULT:
        default:
            cmd.alarm_on = true;
            cmd.display_warning = true;
            break;
    }

    app->last_command = cmd;
    app->cycles++;
    return cmd;
}
