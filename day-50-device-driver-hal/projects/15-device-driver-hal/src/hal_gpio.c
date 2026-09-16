#include <stdbool.h>
typedef struct { bool output; int level; } hal_gpio_t;
void hal_gpio_init(hal_gpio_t*g){if(g){g->output=true;g->level=0;}}
void hal_gpio_write(hal_gpio_t*g,int level){if(g&&g->output)g->level=level;}
