#include "memory/memory_pool.h"
#include <stddef.h>
void pool_init(memory_pool_t*p){if(!p)return;for(size_t i=0;i<POOL_BLOCK_COUNT;i++)p->used[i]=false;p->used_count=0;}
void* pool_alloc(memory_pool_t*p){if(!p||p->used_count==POOL_BLOCK_COUNT)return 0;for(size_t i=0;i<POOL_BLOCK_COUNT;i++)if(!p->used[i]){p->used[i]=true;p->used_count++;return p->storage[i];}return 0;}
bool pool_free(memory_pool_t*p,void*ptr){if(!p||!ptr)return false;for(size_t i=0;i<POOL_BLOCK_COUNT;i++)if(ptr==p->storage[i]){if(!p->used[i])return false;p->used[i]=false;p->used_count--;return true;}return false;}
uint32_t pool_used(const memory_pool_t*p){return p?p->used_count:0;}
uint32_t pool_free_count(const memory_pool_t*p){return p?POOL_BLOCK_COUNT-p->used_count:0;}
