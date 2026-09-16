#include "device/device.h"
typedef struct { uint8_t value; } sensor_ctx_t;
static device_status_t init(device_t*d){return d&&d->context?DEV_OK:DEV_ERROR;}
static device_status_t read(device_t*d,uint8_t*b,uint32_t n){if(!b||n<1)return DEV_ERROR;b[0]=((sensor_ctx_t*)d->context)->value;return DEV_OK;}
static device_status_t write(device_t*d,const uint8_t*b,uint32_t n){if(!b||n<1)return DEV_ERROR;((sensor_ctx_t*)d->context)->value=b[0];return DEV_OK;}
void virtual_sensor_create(device_t*d,sensor_ctx_t*c){c->value=42;d->name="virtual_sensor";d->context=c;d->init=init;d->read=read;d->write=write;d->ready=false;}
