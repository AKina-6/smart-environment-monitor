#include <assert.h>
#include "supervisor/supervisor.h"
int main(void){
    fault_supervisor_t s; supervisor_init(&s,RESET_REASON_POWER_ON);
    supervisor_configure_module(&s,MODULE_SENSOR,100U,true);
    supervisor_configure_module(&s,MODULE_CONTROL,100U,true);
    supervisor_heartbeat(&s,MODULE_SENSOR,0U);
    supervisor_heartbeat(&s,MODULE_CONTROL,0U);
    assert(supervisor_should_refresh_watchdog(&s,50U));
    supervisor_heartbeat(&s,MODULE_SENSOR,120U);
    assert(!supervisor_should_refresh_watchdog(&s,120U));
    assert(s.fault_active);
    assert(s.last_fault_module==MODULE_CONTROL);
    assert(s.blocked_refresh_count==1U);
    return 0;
}
