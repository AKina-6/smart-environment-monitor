#ifndef SUPERVISOR_H
#define SUPERVISOR_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    RESET_REASON_POWER_ON = 0,
    RESET_REASON_SOFTWARE,
    RESET_REASON_WATCHDOG,
    RESET_REASON_BROWNOUT,
    RESET_REASON_UNKNOWN
} reset_reason_t;

typedef enum {
    MODULE_SENSOR = 0,
    MODULE_CONTROL,
    MODULE_UI,
    MODULE_TELEMETRY,
    MODULE_COUNT
} module_id_t;

typedef struct {
    uint32_t deadline_ms;
    uint32_t last_heartbeat_ms;
    bool required;
    bool seen_once;
    uint32_t miss_count;
} module_watch_t;

typedef struct {
    module_watch_t modules[MODULE_COUNT];
    uint32_t watchdog_refresh_count;
    uint32_t blocked_refresh_count;
    uint32_t fault_count;
    bool fault_active;
    module_id_t last_fault_module;
    reset_reason_t boot_reason;
} fault_supervisor_t;

void supervisor_init(fault_supervisor_t *s, reset_reason_t reason);
void supervisor_configure_module(fault_supervisor_t *s, module_id_t id, uint32_t deadline_ms, bool required);
void supervisor_heartbeat(fault_supervisor_t *s, module_id_t id, uint32_t now_ms);
bool supervisor_check(fault_supervisor_t *s, uint32_t now_ms);
bool supervisor_should_refresh_watchdog(fault_supervisor_t *s, uint32_t now_ms);
const char *reset_reason_name(reset_reason_t reason);
const char *module_name(module_id_t id);
#endif
