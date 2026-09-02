#ifndef HOST_SENSOR_H
#define HOST_SENSOR_H
#include <stdbool.h>
#include <stdint.h>
typedef struct { uint32_t t_reads,h_reads,l_reads; bool fail_next_humidity; } host_sensor_t;
bool host_read_temperature(void*,float*);
bool host_read_humidity(void*,float*);
bool host_read_light(void*,float*);
#endif
