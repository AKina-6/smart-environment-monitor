#ifndef DMA_IO_H
#define DMA_IO_H
#include <stdbool.h>
#include <stdint.h>
typedef enum { IO_IDLE, IO_BUSY, IO_DONE, IO_ERROR } io_state_t;
typedef enum { OWNER_APP, OWNER_DMA } buffer_owner_t;
typedef struct { uint8_t *data; uint32_t capacity,length; buffer_owner_t owner; } io_buffer_t;
typedef struct { io_state_t state; uint32_t completed,error_count; } dma_channel_t;
void dma_init(dma_channel_t*);
bool dma_start(dma_channel_t*,io_buffer_t*,uint32_t);
bool dma_isr_complete(dma_channel_t*,io_buffer_t*);
void dma_isr_error(dma_channel_t*,io_buffer_t*);
#endif
