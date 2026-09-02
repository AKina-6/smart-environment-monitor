#include "host_sensor.h"
bool host_read_temperature(void *c,float *v){ host_sensor_t*h=c; if(!h||!v)return false; h->t_reads++; *v=24.0f+(float)(h->t_reads%3U); return true; }
bool host_read_humidity(void *c,float *v){ host_sensor_t*h=c; if(!h||!v)return false; h->h_reads++; if(h->fail_next_humidity){h->fail_next_humidity=false;return false;} *v=45.0f+(float)(h->h_reads%2U); return true; }
bool host_read_light(void *c,float *v){ host_sensor_t*h=c; if(!h||!v)return false; h->l_reads++; static const float seq[4]={100.0f,900.0f,200.0f,800.0f}; *v=seq[(h->l_reads-1U)%4U]; return true; }
