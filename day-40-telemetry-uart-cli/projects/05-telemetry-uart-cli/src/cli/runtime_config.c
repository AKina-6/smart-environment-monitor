#include "cli/runtime_config.h"
#include <stddef.h>

void runtime_config_set_defaults(runtime_config_t *cfg)
{
    if (cfg == NULL) return;
    cfg->hot_on_c = 30.0f;
    cfg->hot_off_c = 28.0f;
    cfg->dark_on_lux = 100.0f;
    cfg->dark_off_lux = 150.0f;
    cfg->min_hold_ms = 1000U;
}

bool runtime_config_is_valid(const runtime_config_t *cfg)
{
    if (cfg == NULL) return false;
    if (cfg->hot_off_c >= cfg->hot_on_c) return false;
    if (cfg->dark_on_lux >= cfg->dark_off_lux) return false;
    if (cfg->hot_off_c < -40.0f || cfg->hot_on_c > 100.0f) return false;
    if (cfg->dark_on_lux < 0.0f || cfg->dark_off_lux > 200000.0f) return false;
    if (cfg->min_hold_ms > 60000U) return false;
    return true;
}
