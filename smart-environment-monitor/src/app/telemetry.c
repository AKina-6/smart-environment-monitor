#include "telemetry.h"
#include <stdio.h>

int telemetry_format_json(
    char *buffer,
    size_t buffer_size,
    const environment_data_t *data,
    uint32_t alarm_mask
) {
    if (buffer == 0 || buffer_size == 0U || data == 0) {
        return -1;
    }

    const int written = snprintf(
        buffer,
        buffer_size,
        "{\"timestamp_ms\":%lu,"
        "\"temperature_c\":%.1f,"
        "\"humidity_pct\":%.1f,"
        "\"light_lux\":%.1f,"
        "\"alarm_mask\":%lu}",
        (unsigned long)data->timestamp_ms,
        (double)data->temperature_c,
        (double)data->humidity_pct,
        (double)data->light_lux,
        (unsigned long)alarm_mask
    );

    if (written < 0 || (size_t)written >= buffer_size) {
        return -1;
    }

    return written;
}
