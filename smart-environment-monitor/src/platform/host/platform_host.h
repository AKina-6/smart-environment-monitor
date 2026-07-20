#ifndef PLATFORM_HOST_H
#define PLATFORM_HOST_H

#include <stddef.h>
#include <stdint.h>
#include "environment_types.h"

environment_data_t host_read_simulated_environment(uint32_t sample_index);
void host_display_update(const environment_data_t *data, uint32_t alarm_mask);
void host_alarm_update(uint32_t alarm_mask);
void host_uart_write(const char *text);
void host_delay_ms(uint32_t delay_ms);

#endif
