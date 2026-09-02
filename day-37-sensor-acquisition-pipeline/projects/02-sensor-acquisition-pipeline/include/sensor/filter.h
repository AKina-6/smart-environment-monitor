#ifndef SENSOR_FILTER_H
#define SENSOR_FILTER_H
#include <stdbool.h>
#include <stddef.h>

typedef struct {
    float buffer[8];
    size_t count;
    size_t index;
    float sum;
} moving_average_t;

typedef struct {
    bool initialized;
    float alpha;
    float value;
} ema_filter_t;

void moving_average_init(moving_average_t *f);
float moving_average_update(moving_average_t *f, float sample);
void ema_filter_init(ema_filter_t *f, float alpha);
float ema_filter_update(ema_filter_t *f, float sample);
#endif
