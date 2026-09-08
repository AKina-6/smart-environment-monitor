#include "supervisor/supervisor.h"
#include <stddef.h>

void supervisor_init(fault_supervisor_t *s, reset_reason_t reason)
{
    if (!s) return;
    for (unsigned i=0;i<MODULE_COUNT;i++) {
        s->modules[i].deadline_ms=0U;
        s->modules[i].last_heartbeat_ms=0U;
        s->modules[i].required=false;
        s->modules[i].seen_once=false;
        s->modules[i].miss_count=0U;
    }
    s->watchdog_refresh_count=0U;
    s->blocked_refresh_count=0U;
    s->fault_count=0U;
    s->fault_active=false;
    s->last_fault_module=MODULE_SENSOR;
    s->boot_reason=reason;
}

void supervisor_configure_module(fault_supervisor_t *s, module_id_t id, uint32_t deadline_ms, bool required)
{
    if (!s || id>=MODULE_COUNT) return;
    s->modules[id].deadline_ms=deadline_ms;
    s->modules[id].required=required;
}

void supervisor_heartbeat(fault_supervisor_t *s, module_id_t id, uint32_t now_ms)
{
    if (!s || id>=MODULE_COUNT) return;
    s->modules[id].last_heartbeat_ms=now_ms;
    s->modules[id].seen_once=true;
}

bool supervisor_check(fault_supervisor_t *s, uint32_t now_ms)
{
    if (!s) return false;
    s->fault_active=false;
    for (unsigned i=0;i<MODULE_COUNT;i++) {
        module_watch_t *m=&s->modules[i];
        if (!m->required || m->deadline_ms==0U) continue;
        bool missed = !m->seen_once || (uint32_t)(now_ms-m->last_heartbeat_ms) > m->deadline_ms;
        if (missed) {
            m->miss_count++;
            s->fault_count++;
            s->fault_active=true;
            s->last_fault_module=(module_id_t)i;
            return false;
        }
    }
    return true;
}

bool supervisor_should_refresh_watchdog(fault_supervisor_t *s, uint32_t now_ms)
{
    if (!s) return false;
    if (supervisor_check(s, now_ms)) {
        s->watchdog_refresh_count++;
        return true;
    }
    s->blocked_refresh_count++;
    return false;
}

const char *reset_reason_name(reset_reason_t r)
{
    switch(r){
        case RESET_REASON_POWER_ON:return "POWER_ON";
        case RESET_REASON_SOFTWARE:return "SOFTWARE";
        case RESET_REASON_WATCHDOG:return "WATCHDOG";
        case RESET_REASON_BROWNOUT:return "BROWNOUT";
        default:return "UNKNOWN";
    }
}

const char *module_name(module_id_t id)
{
    switch(id){
        case MODULE_SENSOR:return "SENSOR";
        case MODULE_CONTROL:return "CONTROL";
        case MODULE_UI:return "UI";
        case MODULE_TELEMETRY:return "TELEMETRY";
        default:return "UNKNOWN";
    }
}
