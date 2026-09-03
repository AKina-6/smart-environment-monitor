#ifndef ACTUATOR_POLICY_H
#define ACTUATOR_POLICY_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    SYSTEM_NORMAL = 0,
    SYSTEM_DEGRADED,
    SYSTEM_FAULT
} system_health_t;

typedef struct {
    float fan_on_c;
    float fan_off_c;
    float light_on_lux;
    float light_off_lux;
    uint32_t min_hold_ms;
} actuator_thresholds_t;

typedef struct {
    bool fan_on;
    bool light_on;
    bool alarm_on;
    uint32_t fan_last_change_ms;
    uint32_t light_last_change_ms;
    uint32_t fan_switch_count;
    uint32_t light_switch_count;
    uint32_t blocked_switch_count;
} actuator_state_t;

void actuator_state_init(actuator_state_t *state, uint32_t now_ms);
void actuator_policy_update(
    actuator_state_t *state,
    const actuator_thresholds_t *cfg,
    system_health_t health,
    float temperature_c,
    float light_lux,
    uint32_t now_ms
);

#endif
