#include "io/dma_io.h"
void dma_init(dma_channel_t*c){if(c)*c=(dma_channel_t){IO_IDLE,0,0};}
bool dma_start(dma_channel_t*c,io_buffer_t*b,uint32_t n){if(!c||!b||!b->data||!n||n>b->capacity||b->owner!=OWNER_APP||c->state==IO_BUSY)return false;b->length=n;b->owner=OWNER_DMA;c->state=IO_BUSY;return true;}
bool dma_isr_complete(dma_channel_t*c,io_buffer_t*b){if(!c||!b||c->state!=IO_BUSY||b->owner!=OWNER_DMA)return false;b->owner=OWNER_APP;c->state=IO_DONE;c->completed++;return true;}
void dma_isr_error(dma_channel_t*c,io_buffer_t*b){if(!c||!b)return;b->owner=OWNER_APP;c->state=IO_ERROR;c->error_count++;}
