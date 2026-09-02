#ifndef SENSOR_ACQUISITION_H
#define SENSOR_ACQUISITION_H
#include <stdbool.h>
#include <stdint.h>
#include "sensor/filter.h"

typedef bool (*sensor_read_fn)(void *ctx, float *value);

typedef struct {
    void *context;
    sensor_read_fn read_temperature;
    sensor_read_fn read_humidity;
    sensor_read_fn read_light;
} sensor_source_t;

typedef struct {
    float temperature_c;
    float humidity_pct;
    float light_lux;
    uint32_t temperature_ms;
    uint32_t humidity_ms;
    uint32_t light_ms;
    uint32_t snapshot_ms;
    bool temperature_valid;
    bool humidity_valid;
    bool light_valid;
    bool coherent;
} sensor_snapshot_t;

typedef struct {
    sensor_source_t source;
    moving_average_t temperature_ma;
    moving_average_t humidity_ma;
    ema_filter_t light_ema;
    sensor_snapshot_t latest;
    uint32_t temperature_period_ms;
    uint32_t humidity_period_ms;
    uint32_t light_period_ms;
    uint32_t next_temperature_ms;
    uint32_t next_humidity_ms;
    uint32_t next_light_ms;
    uint32_t coherence_window_ms;
    uint32_t temperature_reads;
    uint32_t humidity_reads;
    uint32_t light_reads;
    uint32_t read_failures;
} acquisition_pipeline_t;

bool acquisition_pipeline_init(acquisition_pipeline_t *p,const sensor_source_t *src,uint32_t now_ms);
void acquisition_pipeline_poll(acquisition_pipeline_t *p,uint32_t now_ms);
sensor_snapshot_t acquisition_pipeline_snapshot(acquisition_pipeline_t *p,uint32_t now_ms);
#endif
