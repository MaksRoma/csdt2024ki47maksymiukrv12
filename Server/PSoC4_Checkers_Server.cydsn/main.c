#include "project.h"
int main(void)
{
    uint8 ch;

    UART_Start();
    
    while(1)
    {
        ch = UART_UartGetChar();
    
        if(0u != ch)
        {
            if(ch >= 97 && ch <= 122)
            {
                ch -= 32;
                UART_UartPutChar(ch);
            }
            else
            {
                UART_UartPutChar(ch);
            }
        }
    }
}
