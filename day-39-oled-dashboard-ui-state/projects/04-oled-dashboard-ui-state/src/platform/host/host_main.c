#include <stdio.h>
#include "ui/ui_model.h"
#include "ui/ui_renderer.h"

static void show(const ui_state_t *state, const ui_data_t *data)
{
    char text[UI_TEXT_BUFFER_SIZE];
    ui_render_text(state, data, text, sizeof(text));
    printf("page=%s\n%s", ui_page_name(state->page), text);
}

int main(void)
{
    ui_state_t state;
    ui_state_init(&state);

    ui_data_t data = {
        .temperature_c = 24.5f,
        .humidity_pct = 46.0f,
        .light_lux = 520.0f,
        .fan_on = false,
        .light_on = false,
        .alarm_on = false,
        .temp_valid = true,
        .humidity_valid = true,
        .light_valid = true,
        .health = UI_HEALTH_NORMAL,
        .uptime_ms = 12500U,
        .fault_count = 0U
    };

    show(&state, &data);

    ui_next_page(&state);
    show(&state, &data);

    data.humidity_valid = false;
    data.health = UI_HEALTH_DEGRADED;
    data.fault_count = 1U;
    ui_apply_health(&state, data.health);
    show(&state, &data);

    ui_next_page(&state);
    data.uptime_ms = 20000U;
    show(&state, &data);

    data.temp_valid = false;
    data.alarm_on = true;
    data.health = UI_HEALTH_FAULT;
    data.fault_count = 2U;
    ui_apply_health(&state, data.health);
    show(&state, &data);

    data.temp_valid = true;
    data.humidity_valid = true;
    data.alarm_on = false;
    data.health = UI_HEALTH_NORMAL;
    ui_apply_health(&state, data.health);
    show(&state, &data);

    printf(
        "summary page_changes=%lu forced_fault=%lu final_page=%s\n",
        (unsigned long)state.page_changes,
        (unsigned long)state.forced_fault_entries,
        ui_page_name(state.page)
    );

    return 0;
}
