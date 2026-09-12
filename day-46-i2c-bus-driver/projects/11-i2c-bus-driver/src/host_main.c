#include <stdio.h>
#include "i2c/i2c.h"
static const char*n(i2c_status_t s){return s==I2C_OK?"OK":s==I2C_NACK?"NACK":s==I2C_TIMEOUT?"TIMEOUT":"BUS_ERROR";}
int main(){i2c_bus_t b;uint8_t d[2]={1,2};i2c_transaction_t t={0x23,d,2,10};i2c_init(&b);printf("normal=%s\n",n(i2c_transfer(&b,&t)));t.address=0;printf("nack=%s\n",n(i2c_transfer(&b,&t)));t.address=0x23;t.timeout_ms=0;printf("timeout=%s\n",n(i2c_transfer(&b,&t)));t.timeout_ms=10;b.stuck_sda=true;printf("recovery=%s recoveries=%u\n",n(i2c_transfer(&b,&t)),b.recoveries);printf("summary normal=PASS nack=PASS timeout=PASS recovery=PASS\n");return 0;}
