
/*
 * File name            : uart.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_14.1 Real Time Clock
 *                      : Created on October 30, 2013, 2:13PM
 *                      : UART functions source file
 */

#if defined(__XC)
    #include <plib\usart.h>
#elif defined(__18CXX)
    #include <usart.h>
#endif
/*______________________________ UART functions_____________________________________*/


void UsartConfig(unsigned char config1, unsigned char config2)
    {
    OpenUSART( config1, config2);
    }

void Write(char data)
{
    WriteUSART(data);
    while(BusyUSART());
}

void Write_str(unsigned char *c)                                    /* Function writes a string to UART                      */
    {
    Write(0x0D);
    while(*c != '\0')
        {
        WriteUSART(*c);
        while(BusyUSART());
        c++;
        }

    }

unsigned char Read_char(void)                                        /* Function reads a byte from UART                      */
    {
    unsigned char c;
    while(!(DataRdyUSART()));
    c = ReadUSART();
    Write('\n');
    Write('\r');
    Write(c);
    return (c);
    }

void Read_string(unsigned char *buffer, unsigned char len)            /* Reads a string data from UART of having specific length*/
  {
  char i;                                                             
  unsigned char data;
      Write(0x0D);
      Write('\n');
  for(i=0;i<len;i++)                                                  
    {
    while(!DataRdyUSART());                                           /* Wait for data to be received                           */
    data = getcUSART();                                               /* Get a character from the USART                         */
    *buffer = data;                                                   /* save data in a string                                  */
    WriteUSART(data);
    while(BusyUSART());
    buffer++;                                                         /* Increment the string pointer                           */
    }
  }