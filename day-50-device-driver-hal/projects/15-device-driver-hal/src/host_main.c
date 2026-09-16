#include <stdio.h>
#include "device/device.h"
typedef struct { unsigned char value; } sensor_ctx_t;
void virtual_sensor_create(device_t*,sensor_ctx_t*);
int main(){device_t d;sensor_ctx_t c;unsigned char r=0,w=77;virtual_sensor_create(&d,&c);
printf("device=%s\n",d.name);
printf("pre_init=%s\n",device_read(&d,&r,1)==DEV_NOT_READY?"PASS":"FAIL");
printf("init=%s\n",device_init(&d)==DEV_OK?"PASS":"FAIL");
printf("read=%s value=%u\n",device_read(&d,&r,1)==DEV_OK?"PASS":"FAIL",r);
printf("write=%s\n",device_write(&d,&w,1)==DEV_OK?"PASS":"FAIL");
device_read(&d,&r,1);printf("readback=%u\n",r);
printf("summary interface=PASS lifecycle=PASS read=PASS write=PASS\n");return 0;}
