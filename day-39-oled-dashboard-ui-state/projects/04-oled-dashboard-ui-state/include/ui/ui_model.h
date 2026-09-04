#ifndef UI_MODEL_H
#define UI_MODEL_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    UI_PAGE_OVERVIEW = 0,
    UI_PAGE_SENSOR,
    UI_PAGE_SYSTEM,
    UI_PAGE_FAULT,
    UI_PAGE_COUNT
} ui_page_t;

typedef enum {
    UI_HEALTH_NORMAL = 0,
    UI_HEALTH_DEGRADED,
    UI_HEALTH_FAULT
} ui_health_t;

typedef struct {
    float temperature_c;
    float humidity_pct;
    float light_lux;
    bool fan_on;
    bool light_on;
    bool alarm_on;
    bool temp_valid;
    bool humidity_valid;
    bool light_valid;
    ui_health_t health;
    uint32_t uptime_ms;
    uint32_t fault_count;
} ui_data_t;

typedef struct {
    ui_page_t page;
    ui_page_t previous_non_fault_page;
    uint32_t page_changes;
    uint32_t forced_fault_entries;
} ui_state_t;

void ui_state_init(ui_state_t *state);
void ui_next_page(ui_state_t *state);
void ui_previous_page(ui_state_t *state);
void ui_apply_health(ui_state_t *state, ui_health_t health);
const char *ui_page_name(ui_page_t page);
const char *ui_health_name(ui_health_t health);

#endif
