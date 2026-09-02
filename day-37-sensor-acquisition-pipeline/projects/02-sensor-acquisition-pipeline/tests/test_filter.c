#include <assert.h>
#include <math.h>
#include "sensor/filter.h"
int main(void){ moving_average_t m; moving_average_init(&m); assert(fabsf(moving_average_update(&m,10.0f)-10.0f)<0.001f); assert(fabsf(moving_average_update(&m,20.0f)-15.0f)<0.001f); ema_filter_t e; ema_filter_init(&e,0.25f); assert(fabsf(ema_filter_update(&e,100.0f)-100.0f)<0.001f); assert(fabsf(ema_filter_update(&e,900.0f)-300.0f)<0.001f); return 0; }
