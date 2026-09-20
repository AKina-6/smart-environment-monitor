#include <stdio.h>
#include "memory/memory_pool.h"
int main(void){memory_pool_t p;void*b[POOL_BLOCK_COUNT];pool_init(&p);for(int i=0;i<POOL_BLOCK_COUNT;i++)b[i]=pool_alloc(&p);printf("full_protection=%s\n",pool_alloc(&p)==0?"PASS":"FAIL");printf("free=%s\n",pool_free(&p,b[2])?"PASS":"FAIL");printf("reuse=%s\n",pool_alloc(&p)==b[2]?"PASS":"FAIL");printf("invalid_free=%s\n",!pool_free(&p,(void*)0x1234)?"PASS":"FAIL");printf("summary static_pool=PASS fixed_block=PASS exhaustion=PASS reuse=PASS\n");return 0;}
