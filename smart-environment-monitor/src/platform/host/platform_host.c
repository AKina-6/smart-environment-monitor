#include "platform_host.h"
#include <stdio.h>

environment_data_t host_read_simulated_environment(uint32_t sample_index) {
    static const environment_data_t samples[] = {
        {25.4F, 61.0F, 420.0F, 0U, true},
        {36.2F, 65.0F, 380.0F, 0U, true},
        {29.0F, 84.0F, 300.0F, 0U, true},
        {27.5F, 70.0F, 32.0F,  0U, true},
        {0.0F,  0.0F,  0.0F,   0U, false}
    };

    const size_t count = sizeof(samples) / sizeof(samples[0]);
    environment_data_t data = samples[sample_index % count];
    data.timestamp_ms = sample_index * 1000U;
    return data;
}

void host_display_update(const environment_data_t *data, uint32_t alarm_mask) {
    printf(
        "[OLED] T=%.1fC H=%.1f%% L=%.1flux Alarm=0x%02lX\n",
        (double)data->temperature_c,
        (double)data->humidity_pct,
        (double)data->light_lux,
        (unsigned long)alarm_mask
    );
}

void host_alarm_update(uint32_t alarm_mask) {
    printf("[ALARM] LED=%s BUZZER=%s\n",
           alarm_mask ? "ON" : "OFF",
           alarm_mask ? "ON" : "OFF");
}

void host_uart_write(const char *text) {
    printf("[UART] %s\n", text);
}

void host_delay_ms(uint32_t delay_ms) {
    (void)delay_ms;
}
