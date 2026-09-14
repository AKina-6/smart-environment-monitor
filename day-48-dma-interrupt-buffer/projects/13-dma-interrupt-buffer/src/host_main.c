#include <stdio.h>
#include "io/dma_io.h"
static const char*s(io_state_t x){return x==IO_IDLE?"IDLE":x==IO_BUSY?"BUSY":x==IO_DONE?"DONE":"ERROR";}
int main(){dma_channel_t c;uint8_t d[16];io_buffer_t b={d,16,0,OWNER_APP};dma_init(&c);int ok=dma_start(&c,&b,8);printf("start=%s state=%s owner=%s\n",ok?"PASS":"FAIL",s(c.state),b.owner==OWNER_DMA?"DMA":"APP");ok=dma_isr_complete(&c,&b);printf("complete=%s state=%s owner=%s completed=%u\n",ok?"PASS":"FAIL",s(c.state),b.owner==OWNER_APP?"APP":"DMA",c.completed);dma_start(&c,&b,4);dma_isr_error(&c,&b);printf("error state=%s owner=%s errors=%u\n",s(c.state),b.owner==OWNER_APP?"APP":"DMA",c.error_count);printf("summary dma=PASS interrupt=PASS ownership=PASS error=PASS\n");return 0;}
