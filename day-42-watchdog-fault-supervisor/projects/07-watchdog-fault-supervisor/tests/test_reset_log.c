#include <assert.h>
#include "supervisor/reset_log.h"
int main(void){
    reset_log_t log; reset_log_init(&log);
    reset_log_record_boot(&log,RESET_REASON_POWER_ON);
    reset_log_record_boot(&log,RESET_REASON_WATCHDOG);
    reset_log_record_boot(&log,RESET_REASON_SOFTWARE);
    assert(log.boot_count==3U);
    assert(log.watchdog_reset_count==1U);
    assert(log.software_reset_count==1U);
    assert(log.last_reason==RESET_REASON_SOFTWARE);
    return 0;
}
