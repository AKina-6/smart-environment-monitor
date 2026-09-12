#include "i2c/i2c.h"
void i2c_init(i2c_bus_t*b){if(b)*b=(i2c_bus_t){0};}
bool i2c_bus_recover(i2c_bus_t*b){if(!b)return false;if(!b->stuck_sda)return true;b->stuck_sda=false;b->busy=false;b->recoveries++;return true;}
i2c_status_t i2c_transfer(i2c_bus_t*b,const i2c_transaction_t*t){if(!b||!t||!t->data||!t->length)return I2C_BUS_ERROR;if(b->stuck_sda&&!i2c_bus_recover(b))return I2C_BUS_ERROR;if(!t->address)return I2C_NACK;if(!t->timeout_ms)return I2C_TIMEOUT;b->busy=true;b->busy=false;return I2C_OK;}
