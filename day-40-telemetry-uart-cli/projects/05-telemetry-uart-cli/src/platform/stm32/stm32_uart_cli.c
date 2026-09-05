/* STM32 integration sketch. Reuse Day 06/24 UART RX infrastructure. */
#include "cli/cli.h"
#include "stm32f1xx_hal.h"
#include <string.h>
extern UART_HandleTypeDef huart1;
static char line_buffer[96];
static unsigned int line_length=0U;
static cli_context_t *g_cli=0;

void stm32_cli_bind(cli_context_t *cli) { g_cli=cli; line_length=0U; }

void stm32_cli_on_rx_byte(uint8_t byte)
{
    if (!g_cli) return;
    if (byte=='\r' || byte=='\n') {
        if (line_length==0U) return;
        line_buffer[line_length]='\0';
        char reply[256];
        int n=cli_execute(g_cli,line_buffer,reply,sizeof(reply));
        if (n>0) {
            HAL_UART_Transmit(&huart1,(uint8_t*)reply,(uint16_t)strlen(reply),100U);
            const uint8_t crlf[2]={'\r','\n'};
            HAL_UART_Transmit(&huart1,(uint8_t*)crlf,2U,100U);
        }
        line_length=0U;
        return;
    }
    if (line_length+1U < sizeof(line_buffer)) line_buffer[line_length++]=(char)byte;
    else line_length=0U;
}
