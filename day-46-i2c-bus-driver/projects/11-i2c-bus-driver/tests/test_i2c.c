#include <assert.h>
#include "i2c/i2c.h"
int main(){i2c_bus_t b;uint8_t d[2]={1,2};i2c_transaction_t t={0x23,d,2,10};i2c_init(&b);assert(i2c_transfer(&b,&t)==I2C_OK);t.address=0;assert(i2c_transfer(&b,&t)==I2C_NACK);t.address=0x23;t.timeout_ms=0;assert(i2c_transfer(&b,&t)==I2C_TIMEOUT);t.timeout_ms=10;b.stuck_sda=true;assert(i2c_transfer(&b,&t)==I2C_OK&&b.recoveries==1);return 0;}
