#include "service/environment_service.h"
#include <stddef.h>

void environment_service_init(environment_service_t *service, float hot_threshold_c, float dark_threshold_lux)
{
    if (service == NULL) return;
    service->hot_threshold_c = hot_threshold_c;
    service->dark_threshold_lux = dark_threshold_lux;
    service->degraded_count = 0U;
    service->fault_count = 0U;
    service->last_state = ENV_STATE_NORMAL;
}

static unsigned bad_sensor_count(const sensor_snapshot_t *s)
{
    unsigned bad = 0U;
    if (s->temp_health != SENSOR_HEALTH_OK) bad++;
    if (s->humidity_health != SENSOR_HEALTH_OK) bad++;
    if (s->light_health != SENSOR_HEALTH_OK) bad++;
    return bad;
}

environment_state_t environment_service_evaluate(environment_service_t *service, const sensor_snapshot_t *snapshot)
{
    if (service == NULL || snapshot == NULL) return ENV_STATE_FAULT;

    const unsigned bad = bad_sensor_count(snapshot);
    environment_state_t state;

    if (bad >= 2U) {
        state = ENV_STATE_FAULT;
        service->fault_count++;
    } else if (bad == 1U) {
        state = ENV_STATE_DEGRADED;
        service->degraded_count++;
    } else if (snapshot->temperature_c >= service->hot_threshold_c) {
        state = ENV_STATE_HOT;
    } else if (snapshot->light_lux <= service->dark_threshold_lux) {
        state = ENV_STATE_DARK;
    } else {
        state = ENV_STATE_NORMAL;
    }

    service->last_state = state;
    return state;
}

const char *environment_state_name(environment_state_t state)
{
    switch (state) {
        case ENV_STATE_NORMAL: return "NORMAL";
        case ENV_STATE_DARK: return "DARK";
        case ENV_STATE_HOT: return "HOT";
        case ENV_STATE_DEGRADED: return "DEGRADED";
        case ENV_STATE_FAULT: return "FAULT";
        default: return "UNKNOWN";
    }
}
