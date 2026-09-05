#include "cli/telemetry.h"
#include <stdio.h>

int telemetry_format(const telemetry_snapshot_t *s, char *out, size_t cap)
{
    if (s == NULL || out == NULL || cap == 0U) return -1;
    return snprintf(out, cap,
        "T=%.1fC H=%.1f%% L=%.0flux FAN=%s LIGHT=%s ALARM=%s HEALTH=%s UPTIME=%ums FAULTS=%u",
        s->temperature_c, s->humidity_pct, s->light_lux,
        s->fan_on ? "ON" : "OFF",
        s->light_on ? "ON" : "OFF",
        s->alarm_on ? "ON" : "OFF",
        s->health ? s->health : "UNKNOWN",
        s->uptime_ms, s->fault_count);
}
