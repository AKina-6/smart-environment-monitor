#include <assert.h>
#include "memory/memory_pool.h"
int main(void){memory_pool_t p;void*b[POOL_BLOCK_COUNT];pool_init(&p);assert(pool_used(&p)==0);for(int i=0;i<POOL_BLOCK_COUNT;i++){b[i]=pool_alloc(&p);assert(b[i]);}assert(pool_alloc(&p)==0);assert(pool_free(&p,b[3]));assert(pool_free_count(&p)==1);assert(pool_alloc(&p)==b[3]);assert(!pool_free(&p,(void*)0x1234));return 0;}
