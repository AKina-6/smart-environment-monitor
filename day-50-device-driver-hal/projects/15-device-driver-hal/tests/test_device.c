#include <assert.h>
#include "device/device.h"
typedef struct { unsigned char value; } sensor_ctx_t;
void virtual_sensor_create(device_t*,sensor_ctx_t*);
int main(){device_t d;sensor_ctx_t c;unsigned char r,w=77;virtual_sensor_create(&d,&c);
assert(device_read(&d,&r,1)==DEV_NOT_READY);assert(device_init(&d)==DEV_OK);
assert(device_read(&d,&r,1)==DEV_OK&&r==42);assert(device_write(&d,&w,1)==DEV_OK);
assert(device_read(&d,&r,1)==DEV_OK&&r==77);return 0;}
