#ifndef I2C_H
#define I2C_H
#include <stdbool.h>
#include <stdint.h>
typedef enum { I2C_OK, I2C_NACK, I2C_TIMEOUT, I2C_BUS_ERROR } i2c_status_t;
typedef struct { uint8_t address; uint8_t *data; uint32_t length, timeout_ms; } i2c_transaction_t;
typedef struct { bool busy, stuck_sda; uint32_t recoveries; } i2c_bus_t;
void i2c_init(i2c_bus_t*);
bool i2c_bus_recover(i2c_bus_t*);
i2c_status_t i2c_transfer(i2c_bus_t*, const i2c_transaction_t*);
#endif
