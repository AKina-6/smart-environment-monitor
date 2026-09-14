#include <assert.h>
#include "io/dma_io.h"
int main(){dma_channel_t c;uint8_t d[8];io_buffer_t b={d,8,0,OWNER_APP};dma_init(&c);assert(dma_start(&c,&b,4));assert(b.owner==OWNER_DMA&&c.state==IO_BUSY);assert(!dma_start(&c,&b,2));assert(dma_isr_complete(&c,&b));assert(b.owner==OWNER_APP&&c.completed==1);assert(dma_start(&c,&b,8));dma_isr_error(&c,&b);assert(c.state==IO_ERROR&&b.owner==OWNER_APP&&c.error_count==1);return 0;}
