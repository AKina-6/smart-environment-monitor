#include <stdio.h>
#include "sensor/sensor_validation.h"
#include "app/environment_app.h"

static sensor_snapshot_t make_snapshot(float t, float h, float l, uint32_t ts)
{
    sensor_snapshot_t s = {
        .temperature_c = t,
        .humidity_pct = h,
        .light_lux = l,
        .timestamp_ms = ts,
        .temp_health = sensor_validate_temperature(t),
        .humidity_health = sensor_validate_humidity(h),
        .light_health = sensor_validate_light(l)
    };
    return s;
}

static void print_case(const char *name, environment_app_t *app, sensor_snapshot_t s)
{
    const actuator_command_t cmd = environment_app_process(app, &s);
    printf("case=%s state=%s T=%.1f H=%.1f L=%.1f fan=%s light=%s alarm=%s warning=%s\n",
           name,
           environment_state_name(app->service.last_state),
           s.temperature_c,
           s.humidity_pct,
           s.light_lux,
           cmd.fan_on ? "on" : "off",
           cmd.light_on ? "on" : "off",
           cmd.alarm_on ? "on" : "off",
           cmd.display_warning ? "yes" : "no");
}

int main(void)
{
    environment_app_t app;
    environment_app_init(&app);

    print_case("normal", &app, make_snapshot(24.0f, 45.0f, 500.0f, 1000U));
    print_case("dark", &app, make_snapshot(23.0f, 48.0f, 50.0f, 2000U));
    print_case("hot", &app, make_snapshot(33.0f, 40.0f, 600.0f, 3000U));

    sensor_snapshot_t degraded = make_snapshot(25.0f, 150.0f, 400.0f, 4000U);
    print_case("degraded", &app, degraded);

    sensor_snapshot_t fault = make_snapshot(95.0f, 150.0f, 400.0f, 5000U);
    print_case("fault", &app, fault);

    sensor_snapshot_t stale = make_snapshot(24.0f, 50.0f, 300.0f, 1000U);
    sensor_apply_stale_check(&stale, 4000U, 2000U);
    print_case("stale", &app, stale);

    printf("summary cycles=%lu degraded=%lu faults=%lu last=%s\n",
           (unsigned long)app.cycles,
           (unsigned long)app.service.degraded_count,
           (unsigned long)app.service.fault_count,
           environment_state_name(app.service.last_state));

    return 0;
}
