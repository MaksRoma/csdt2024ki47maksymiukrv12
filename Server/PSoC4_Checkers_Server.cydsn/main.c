#include "project.h"

void UART_PrintString(char *buf);

const int BUF_SIZE = 8;
int main(void)
{
    uint8 ch = 0;
    uint8 i = 0;
    char buf[BUF_SIZE + 1];
    
    for(int j = 0; j < BUF_SIZE + 1; ++j)
    {
        buf[j] = 0;
    }
    
    UART_Start();
    
    UART_UartPutString(buf);
   
    while(1)
    {
        
        if(i == BUF_SIZE)
        {
            buf[i] = 0;
            UART_UartPutString(buf);
            for(int j = 0; j < BUF_SIZE; ++j)
            {
                buf[j] = 0;
            }
            i = 0;
        }

        ch = UART_UartGetChar();
        
        if(ch != 0u)
        {
            if(ch >= 97 && ch <= 122)
            {
                ch -= 32;
//                UART_UartPutChar(ch);
                buf[i] = ch;
                ++i;
            }
            else
            {
//                UART_UartPutChar(ch);
                buf[i] = ch;
                ++i;
            }
        }
                
    }
    
    return 0;
}

void UART_PrintString(char *buf)
{
    uint8 i = 0;
    while(buf[i] != '\0')
    {
        UART_UartPutChar(buf[i]);
        ++i;
    }
}
