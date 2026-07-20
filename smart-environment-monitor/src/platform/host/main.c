#include <stdio.h>
#include "config.h"
#include "environment_monitor.h"
#include "platform_host.h"

int main(void) {
    environment_monitor_t monitor;
    char telemetry[MONITOR_JSON_BUFFER_SIZE];

    environment_monitor_init(&monitor);

    for (uint32_t i = 1U; i <= 10U; ++i) {
        const environment_data_t data = host_read_simulated_environment(i);
        const uint32_t alarm_mask = environment_monitor_process(
            &monitor,
            &data,
            telemetry,
            sizeof(telemetry)
        );

        host_display_update(&data, alarm_mask);
        host_alarm_update(alarm_mask);
        host_uart_write(telemetry);
        host_delay_ms(MONITOR_SAMPLE_PERIOD_MS);
    }

    puts("Simulation finished.");
    return 0;
}
