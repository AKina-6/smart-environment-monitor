#ifndef TELEMETRY_H
#define TELEMETRY_H
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    float temperature_c;
    float humidity_pct;
    float light_lux;
    bool fan_on;
    bool light_on;
    bool alarm_on;
    const char *health;
    unsigned int uptime_ms;
    unsigned int fault_count;
} telemetry_snapshot_t;

int telemetry_format(const telemetry_snapshot_t *snapshot, char *out, size_t capacity);
#endif
