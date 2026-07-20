#ifndef ALARM_MANAGER_H
#define ALARM_MANAGER_H

#include <stdint.h>
#include "environment_types.h"

uint32_t alarm_evaluate(
    const environment_data_t *data,
    const alarm_thresholds_t *thresholds
);

#endif
