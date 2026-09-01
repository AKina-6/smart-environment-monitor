#include <assert.h>
#include "app/environment_app.h"

int main(void)
{
    environment_app_t app;
    environment_app_init(&app);

    sensor_snapshot_t normal = {24.0f, 50.0f, 500.0f, 0U, SENSOR_HEALTH_OK, SENSOR_HEALTH_OK, SENSOR_HEALTH_OK};
    actuator_command_t cmd = environment_app_process(&app, &normal);
    assert(!cmd.fan_on && !cmd.light_on && !cmd.alarm_on && !cmd.display_warning);

    sensor_snapshot_t hot = {35.0f, 50.0f, 500.0f, 0U, SENSOR_HEALTH_OK, SENSOR_HEALTH_OK, SENSOR_HEALTH_OK};
    cmd = environment_app_process(&app, &hot);
    assert(cmd.fan_on && !cmd.alarm_on);

    sensor_snapshot_t degraded = {25.0f, 50.0f, 500.0f, 0U, SENSOR_HEALTH_OK, SENSOR_HEALTH_IO_ERROR, SENSOR_HEALTH_OK};
    cmd = environment_app_process(&app, &degraded);
    assert(cmd.display_warning && !cmd.alarm_on);

    sensor_snapshot_t fault = {25.0f, 50.0f, 500.0f, 0U, SENSOR_HEALTH_IO_ERROR, SENSOR_HEALTH_IO_ERROR, SENSOR_HEALTH_OK};
    cmd = environment_app_process(&app, &fault);
    assert(cmd.display_warning && cmd.alarm_on);
    return 0;
}
