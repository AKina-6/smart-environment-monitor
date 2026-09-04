#include <assert.h>
#include <string.h>
#include "ui/ui_model.h"
#include "ui/ui_renderer.h"

int main(void)
{
    ui_state_t state;
    ui_state_init(&state);

    ui_data_t data = {
        .temperature_c = 31.0f,
        .humidity_pct = 45.0f,
        .light_lux = 80.0f,
        .fan_on = true,
        .light_on = true,
        .alarm_on = false,
        .temp_valid = true,
        .humidity_valid = true,
        .light_valid = true,
        .health = UI_HEALTH_NORMAL,
        .uptime_ms = 1000U,
        .fault_count = 0U
    };

    char text[UI_TEXT_BUFFER_SIZE];
    assert(ui_render_text(&state, &data, text, sizeof(text)) > 0U);
    assert(strstr(text, "OVERVIEW") != 0);
    assert(strstr(text, "FAN:ON") != 0);

    data.health = UI_HEALTH_FAULT;
    data.alarm_on = true;
    data.humidity_valid = false;
    data.fault_count = 2U;
    ui_apply_health(&state, data.health);

    assert(ui_render_text(&state, &data, text, sizeof(text)) > 0U);
    assert(strstr(text, "[FAULT]") != 0);
    assert(strstr(text, "HUM:ERR") != 0);
    assert(strstr(text, "FAULT_COUNT:2") != 0);

    return 0;
}
