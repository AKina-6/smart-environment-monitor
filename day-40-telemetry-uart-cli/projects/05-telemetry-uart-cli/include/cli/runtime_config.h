#ifndef RUNTIME_CONFIG_H
#define RUNTIME_CONFIG_H
#include <stdbool.h>

typedef struct {
    float hot_on_c;
    float hot_off_c;
    float dark_on_lux;
    float dark_off_lux;
    unsigned int min_hold_ms;
} runtime_config_t;

void runtime_config_set_defaults(runtime_config_t *cfg);
bool runtime_config_is_valid(const runtime_config_t *cfg);
#endif
