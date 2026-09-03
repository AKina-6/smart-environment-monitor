#include "control/actuator_policy.h"
#include <stddef.h>

static bool hold_elapsed(uint32_t now, uint32_t last, uint32_t hold)
{
    return (uint32_t)(now - last) >= hold;
}

void actuator_state_init(actuator_state_t *state, uint32_t now_ms)
{
    if (!state) return;
    state->fan_on=false;
    state->light_on=false;
    state->alarm_on=false;
    state->fan_last_change_ms=now_ms;
    state->light_last_change_ms=now_ms;
    state->fan_switch_count=0U;
    state->light_switch_count=0U;
    state->blocked_switch_count=0U;
}

void actuator_policy_update(
    actuator_state_t *state,
    const actuator_thresholds_t *cfg,
    system_health_t health,
    float temperature_c,
    float light_lux,
    uint32_t now_ms)
{
    if (!state || !cfg) return;

    if (health == SYSTEM_FAULT) {
        state->alarm_on = true;
        if (state->fan_on) {
            state->fan_on = false;
            state->fan_last_change_ms = now_ms;
            state->fan_switch_count++;
        }
        if (state->light_on) {
            state->light_on = false;
            state->light_last_change_ms = now_ms;
            state->light_switch_count++;
        }
        return;
    }

    state->alarm_on = (health == SYSTEM_DEGRADED);

    bool want_fan = state->fan_on;
    if (!state->fan_on && temperature_c >= cfg->fan_on_c) want_fan = true;
    else if (state->fan_on && temperature_c <= cfg->fan_off_c) want_fan = false;

    if (want_fan != state->fan_on) {
        if (hold_elapsed(now_ms, state->fan_last_change_ms, cfg->min_hold_ms)) {
            state->fan_on = want_fan;
            state->fan_last_change_ms = now_ms;
            state->fan_switch_count++;
        } else {
            state->blocked_switch_count++;
        }
    }

    bool want_light = state->light_on;
    if (!state->light_on && light_lux <= cfg->light_on_lux) want_light = true;
    else if (state->light_on && light_lux >= cfg->light_off_lux) want_light = false;

    if (want_light != state->light_on) {
        if (hold_elapsed(now_ms, state->light_last_change_ms, cfg->min_hold_ms)) {
            state->light_on = want_light;
            state->light_last_change_ms = now_ms;
            state->light_switch_count++;
        } else {
            state->blocked_switch_count++;
        }
    }
}
