#ifndef TELEMETRY_H
#define TELEMETRY_H

#include <stddef.h>
#include <stdint.h>
#include "environment_types.h"

int telemetry_format_json(
    char *buffer,
    size_t buffer_size,
    const environment_data_t *data,
    uint32_t alarm_mask
);

#endif
