#ifndef RESET_LOG_H
#define RESET_LOG_H
#include <stdint.h>
#include "supervisor/supervisor.h"

typedef struct {
    uint32_t boot_count;
    uint32_t watchdog_reset_count;
    uint32_t software_reset_count;
    reset_reason_t last_reason;
} reset_log_t;

void reset_log_init(reset_log_t *log);
void reset_log_record_boot(reset_log_t *log, reset_reason_t reason);
#endif
