#ifndef DEVICE_H
#define DEVICE_H
#include <stdbool.h>
#include <stdint.h>
typedef enum { DEV_OK=0, DEV_ERROR, DEV_NOT_READY } device_status_t;
typedef struct device device_t;
typedef device_status_t (*device_init_fn)(device_t*);
typedef device_status_t (*device_read_fn)(device_t*,uint8_t*,uint32_t);
typedef device_status_t (*device_write_fn)(device_t*,const uint8_t*,uint32_t);
struct device {
    const char *name; void *context;
    device_init_fn init; device_read_fn read; device_write_fn write;
    bool ready;
};
device_status_t device_init(device_t*);
device_status_t device_read(device_t*,uint8_t*,uint32_t);
device_status_t device_write(device_t*,const uint8_t*,uint32_t);
#endif
