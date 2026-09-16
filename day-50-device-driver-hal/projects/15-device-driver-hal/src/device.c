#include "device/device.h"
device_status_t device_init(device_t*d){if(!d||!d->init)return DEV_ERROR;device_status_t s=d->init(d);d->ready=(s==DEV_OK);return s;}
device_status_t device_read(device_t*d,uint8_t*b,uint32_t n){if(!d||!d->ready||!d->read)return DEV_NOT_READY;return d->read(d,b,n);}
device_status_t device_write(device_t*d,const uint8_t*b,uint32_t n){if(!d||!d->ready||!d->write)return DEV_NOT_READY;return d->write(d,b,n);}
