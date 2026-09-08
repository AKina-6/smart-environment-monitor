#include "supervisor/reset_log.h"
#include <stddef.h>
void reset_log_init(reset_log_t *log){ if(!log)return; log->boot_count=0;log->watchdog_reset_count=0;log->software_reset_count=0;log->last_reason=RESET_REASON_UNKNOWN; }
void reset_log_record_boot(reset_log_t *log, reset_reason_t reason){ if(!log)return; log->boot_count++;log->last_reason=reason; if(reason==RESET_REASON_WATCHDOG)log->watchdog_reset_count++; if(reason==RESET_REASON_SOFTWARE)log->software_reset_count++; }
