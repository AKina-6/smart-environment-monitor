#include <stdio.h>
#include "supervisor/supervisor.h"
#include "supervisor/reset_log.h"

static void beat_all(fault_supervisor_t *s, uint32_t now)
{
    supervisor_heartbeat(s,MODULE_SENSOR,now);
    supervisor_heartbeat(s,MODULE_CONTROL,now);
    supervisor_heartbeat(s,MODULE_UI,now);
    supervisor_heartbeat(s,MODULE_TELEMETRY,now);
}

int main(void)
{
    reset_log_t log; reset_log_init(&log); reset_log_record_boot(&log, RESET_REASON_POWER_ON);
    fault_supervisor_t s; supervisor_init(&s, log.last_reason);
    supervisor_configure_module(&s,MODULE_SENSOR,600U,true);
    supervisor_configure_module(&s,MODULE_CONTROL,600U,true);
    supervisor_configure_module(&s,MODULE_UI,1500U,true);
    supervisor_configure_module(&s,MODULE_TELEMETRY,1500U,false);

    beat_all(&s,0U);
    printf("boot reason=%s boot_count=%lu\n", reset_reason_name(s.boot_reason),(unsigned long)log.boot_count);

    for(uint32_t now=500U; now<=1500U; now+=500U){
        supervisor_heartbeat(&s,MODULE_SENSOR,now);
        supervisor_heartbeat(&s,MODULE_CONTROL,now);
        if(now==1000U) supervisor_heartbeat(&s,MODULE_UI,now);
        bool refresh=supervisor_should_refresh_watchdog(&s,now);
        printf("t=%lu refresh=%s fault=%s refresh_count=%lu\n",(unsigned long)now,refresh?"yes":"no",s.fault_active?module_name(s.last_fault_module):"none",(unsigned long)s.watchdog_refresh_count);
    }

    /* Freeze CONTROL after 1500 ms, but keep SENSOR alive. */
    for(uint32_t now=1800U; now<=2400U; now+=300U){
        supervisor_heartbeat(&s,MODULE_SENSOR,now);
        bool refresh=supervisor_should_refresh_watchdog(&s,now);
        printf("t=%lu refresh=%s fault=%s blocked=%lu\n",(unsigned long)now,refresh?"yes":"no",s.fault_active?module_name(s.last_fault_module):"none",(unsigned long)s.blocked_refresh_count);
    }

    const uint32_t refresh_before_reset = s.watchdog_refresh_count;
    const uint32_t blocked_before_reset = s.blocked_refresh_count;
    const uint32_t faults_before_reset = s.fault_count;

    /* Simulated reset after watchdog expires. */
    reset_log_record_boot(&log, RESET_REASON_WATCHDOG);
    supervisor_init(&s, log.last_reason);
    printf("reboot reason=%s boot_count=%lu watchdog_resets=%lu\n", reset_reason_name(s.boot_reason),(unsigned long)log.boot_count,(unsigned long)log.watchdog_reset_count);
    printf("summary refresh=%lu blocked=%lu faults=%lu last_reason=%s\n",
           (unsigned long)refresh_before_reset,
           (unsigned long)blocked_before_reset,
           (unsigned long)faults_before_reset,
           reset_reason_name(log.last_reason));
    return 0;
}
