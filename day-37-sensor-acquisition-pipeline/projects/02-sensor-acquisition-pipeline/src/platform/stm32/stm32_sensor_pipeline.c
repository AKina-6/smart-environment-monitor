/* Integration sketch: replace stubs with Day 13/14 sensor drivers. */
#include "sensor/acquisition.h"
#include "stm32f1xx_hal.h"
extern bool dht11_read(float *temperature_c,float *humidity_pct);
extern bool bh1750_read_lux(float *lux);
typedef struct { float cached_temperature; float cached_humidity; } stm32_sensor_context_t;
static bool read_temperature(void *ctx,float *v){ stm32_sensor_context_t*c=ctx; float t,h; if(!dht11_read(&t,&h))return false; c->cached_temperature=t; c->cached_humidity=h; *v=t; return true; }
static bool read_humidity(void *ctx,float *v){ stm32_sensor_context_t*c=ctx; *v=c->cached_humidity; return true; }
static bool read_light(void *ctx,float *v){ (void)ctx; return bh1750_read_lux(v); }
static stm32_sensor_context_t sensor_ctx;
static acquisition_pipeline_t pipeline;
void sensor_pipeline_start(void){ sensor_source_t s={&sensor_ctx,read_temperature,read_humidity,read_light}; (void)acquisition_pipeline_init(&pipeline,&s,HAL_GetTick()); }
void sensor_pipeline_poll(void){ acquisition_pipeline_poll(&pipeline,HAL_GetTick()); }
sensor_snapshot_t sensor_pipeline_get_snapshot(void){ return acquisition_pipeline_snapshot(&pipeline,HAL_GetTick()); }
