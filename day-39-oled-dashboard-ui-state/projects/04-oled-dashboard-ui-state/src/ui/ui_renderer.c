#include "ui/ui_renderer.h"
#include <stdio.h>
#include <stddef.h>

static const char *onoff(bool value)
{
    return value ? "ON" : "OFF";
}

static const char *valid_mark(bool value)
{
    return value ? "OK" : "ERR";
}

size_t ui_render_text(
    const ui_state_t *state,
    const ui_data_t *data,
    char *output,
    size_t capacity
) {
    if (state == NULL || data == NULL || output == NULL || capacity == 0U) {
        return 0U;
    }

    int n = 0;

    switch (state->page) {
        case UI_PAGE_OVERVIEW:
            n = snprintf(output, capacity,
                "[OVERVIEW] %s\n"
                "T:%.1fC H:%.1f%%\n"
                "L:%.0flux\n"
                "FAN:%s LIGHT:%s ALARM:%s\n",
                ui_health_name(data->health),
                data->temperature_c,
                data->humidity_pct,
                data->light_lux,
                onoff(data->fan_on),
                onoff(data->light_on),
                onoff(data->alarm_on));
            break;

        case UI_PAGE_SENSOR:
            n = snprintf(output, capacity,
                "[SENSOR]\n"
                "TEMP %.1f %s\n"
                "HUM  %.1f %s\n"
                "LUX  %.0f %s\n",
                data->temperature_c, valid_mark(data->temp_valid),
                data->humidity_pct, valid_mark(data->humidity_valid),
                data->light_lux, valid_mark(data->light_valid));
            break;

        case UI_PAGE_SYSTEM:
            n = snprintf(output, capacity,
                "[SYSTEM]\n"
                "UPTIME:%lums\n"
                "HEALTH:%s\n"
                "FAULTS:%lu\n"
                "PAGE_CHG:%lu\n",
                (unsigned long)data->uptime_ms,
                ui_health_name(data->health),
                (unsigned long)data->fault_count,
                (unsigned long)state->page_changes);
            break;

        case UI_PAGE_FAULT:
            n = snprintf(output, capacity,
                "[FAULT]\n"
                "ALARM:%s\n"
                "TEMP:%s HUM:%s LUX:%s\n"
                "FAULT_COUNT:%lu\n",
                onoff(data->alarm_on),
                valid_mark(data->temp_valid),
                valid_mark(data->humidity_valid),
                valid_mark(data->light_valid),
                (unsigned long)data->fault_count);
            break;

        default:
            return 0U;
    }

    if (n < 0) return 0U;
    if ((size_t)n >= capacity) return capacity - 1U;
    return (size_t)n;
}
