#include "ui/ui_model.h"
#include <stddef.h>

void ui_state_init(ui_state_t *state)
{
    if (state == NULL) return;
    state->page = UI_PAGE_OVERVIEW;
    state->previous_non_fault_page = UI_PAGE_OVERVIEW;
    state->page_changes = 0U;
    state->forced_fault_entries = 0U;
}

void ui_next_page(ui_state_t *state)
{
    if (state == NULL || state->page == UI_PAGE_FAULT) return;
    state->page = (ui_page_t)(((unsigned)state->page + 1U) % UI_PAGE_FAULT);
    state->previous_non_fault_page = state->page;
    state->page_changes++;
}

void ui_previous_page(ui_state_t *state)
{
    if (state == NULL || state->page == UI_PAGE_FAULT) return;
    state->page = state->page == UI_PAGE_OVERVIEW
        ? UI_PAGE_SYSTEM
        : (ui_page_t)((unsigned)state->page - 1U);
    state->previous_non_fault_page = state->page;
    state->page_changes++;
}

void ui_apply_health(ui_state_t *state, ui_health_t health)
{
    if (state == NULL) return;

    if (health == UI_HEALTH_FAULT) {
        if (state->page != UI_PAGE_FAULT) {
            state->previous_non_fault_page = state->page;
            state->page = UI_PAGE_FAULT;
            state->forced_fault_entries++;
        }
        return;
    }

    if (state->page == UI_PAGE_FAULT) {
        state->page = state->previous_non_fault_page;
        state->page_changes++;
    }
}

const char *ui_page_name(ui_page_t page)
{
    switch (page) {
        case UI_PAGE_OVERVIEW: return "OVERVIEW";
        case UI_PAGE_SENSOR: return "SENSOR";
        case UI_PAGE_SYSTEM: return "SYSTEM";
        case UI_PAGE_FAULT: return "FAULT";
        default: return "UNKNOWN";
    }
}

const char *ui_health_name(ui_health_t health)
{
    switch (health) {
        case UI_HEALTH_NORMAL: return "NORMAL";
        case UI_HEALTH_DEGRADED: return "DEGRADED";
        case UI_HEALTH_FAULT: return "FAULT";
        default: return "UNKNOWN";
    }
}
