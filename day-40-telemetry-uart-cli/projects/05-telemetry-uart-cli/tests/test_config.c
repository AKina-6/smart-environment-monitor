#include <assert.h>
#include "cli/runtime_config.h"
int main(void){runtime_config_t c; runtime_config_set_defaults(&c); assert(runtime_config_is_valid(&c)); c.hot_off_c=31.0f; assert(!runtime_config_is_valid(&c)); c.hot_off_c=28.0f; c.dark_on_lux=200.0f; c.dark_off_lux=150.0f; assert(!runtime_config_is_valid(&c)); return 0;}
