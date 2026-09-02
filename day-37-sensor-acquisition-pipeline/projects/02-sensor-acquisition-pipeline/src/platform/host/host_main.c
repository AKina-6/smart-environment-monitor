#include <stdio.h>
#include "sensor/acquisition.h"
#include "host_sensor.h"
int main(void){
 host_sensor_t host={0}; sensor_source_t src={&host,host_read_temperature,host_read_humidity,host_read_light}; acquisition_pipeline_t p;
 if(!acquisition_pipeline_init(&p,&src,0U)) return 1;
 for(uint32_t now=0;now<=3000U;now+=250U){
  if(now==2000U) host.fail_next_humidity=true;
  acquisition_pipeline_poll(&p,now);
  if((now%1000U)==0U){ sensor_snapshot_t s=acquisition_pipeline_snapshot(&p,now); printf("t=%lu T=%.2f H=%.2f L=%.2f valid=%d%d%d coherent=%s reads=%lu/%lu/%lu failures=%lu\n",(unsigned long)now,s.temperature_c,s.humidity_pct,s.light_lux,s.temperature_valid?1:0,s.humidity_valid?1:0,s.light_valid?1:0,s.coherent?"yes":"no",(unsigned long)p.temperature_reads,(unsigned long)p.humidity_reads,(unsigned long)p.light_reads,(unsigned long)p.read_failures); }
 }
 printf("summary temp_reads=%lu humidity_reads=%lu light_reads=%lu failures=%lu\n",(unsigned long)p.temperature_reads,(unsigned long)p.humidity_reads,(unsigned long)p.light_reads,(unsigned long)p.read_failures); return 0; }
