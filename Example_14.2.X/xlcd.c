/*
 * File name            : xlcd.c
 * Compiler             : XC8 compiler
 * IDE                  : Microchip MPLAB X IDE v1.90
 * Author               : Etiq Technologies
 * Description          : Example_7.4 External Character LCD
 *                      : Created on November 23, 2013, 3:10 PM
 *                      : External character LCD function definitions source file
 */

#if defined(__XC)
    #include <plib\xlcd.h>
	#include <plib\delays.h>
#elif defined(__18CXX)
    #include <xlcd.h>
	#include <delays.h>
#endif


#include "delay.h"
#include "xlcd_config.h"
unsigned char BusyXLCD(void)
{
        RW_PIN_ = 1;                                 /* Set the control bits for read                    */
        RS_PIN_ = 0;
        DelayFor18TCY();                            /* Invoking delay                                   */
        E_PIN_ = 1;                                  /* Clock in the command                             */
        DelayFor18TCY();
#ifdef BIT8                                         /* 8-bit interface                                  */
        if(DATA_PORT&0x80)                          /* Read bit 7 (busy bit)                            */
        {                                           /* If high                                          */
                E_PIN_ = 0;                          /* Reset clock line                                 */
                RW_PIN_ = 0;                         /* Reset control line                               */
                return 1;                           /* Return TRUE                                      */
        }
        else                                        /* Bit 7 low                                        */
        {
                E_PIN_ = 0;                          /* Reset clock line                                 */
                RW_PIN_ = 0;                         /* Reset control line                               */
                return 0;                           /* Return FALSE                                     */
        }
#endif
}
void WriteCmdXLCD(unsigned char cmd)
{
#ifdef BIT8                                                                 /* 8-bit interface                                  */
        TRIS_DATA_PORT = 0;                                                 /* Data port output                                 */
        DATA_PORT = cmd;                                                    /* Write command to data port                       */
        RW_PIN_ = 0;                                                         /* Set the control signals                          */
        RS_PIN_ = 0;                                                         /* Register select input=0 for sending a command    */
        DelayFor18TCY();
        E_PIN_ = 1;                                                          /* Clock the command input                          */
        DelayFor18TCY();                                                    /* Invokung delay                                   */
        E_PIN_ = 0;
        DelayFor18TCY();                                                    /* Invoking delay                                   */
        TRIS_DATA_PORT = 0xff;                                              /* Data port direction as input                     */

#endif
        return;
}

void WriteDataXLCD(char data)
{
#ifdef BIT8                                                                 /* 8-bit interface                                  */
        TRIS_DATA_PORT = 0;                                                 /* Data port output                                 */
        DATA_PORT = data;                                                   /* Write data to data port                          */
        RS_PIN_ = 1;                                                         /* Set control bits                                 */
        RW_PIN_ = 0;
        DelayFor18TCY();                                                    /* Invoking delay                                   */
        E_PIN_ = 1;                                                          /* Clock data into LCD                              */
        DelayFor18TCY();                                                    /* Invoking delay                                   */
        E_PIN_ = 0;
        DelayFor18TCY();                                                    /* Invoking delay                                   */
        RS_PIN_ = 0;                                                         /* clear register select bit                        */
        TRIS_DATA_PORT = 0xff;                                              /* Make data port direction as input                */
#endif
        return;
}

void OpenXLCD(unsigned char lcdtype)
    {
        #ifdef BIT8                                                         /* 8-bit mode                                       */
        DATA_PORT = 0;                                                      /* clearing data port                               */
        TRIS_DATA_PORT = 0x00;                                              /* Direction of data port set to output             */
#endif
        TRIS_RW_ = 0;                                                        /* Direction of all control bits set as outputs     */
        TRIS_RS_ = 0;
        TRIS_E_ = 0;
        RW_PIN_ = 0;                                                         /* Write/Read pin made low (Write mode)             */
        RS_PIN_ = 0;                                                         /* Register select pin made low (command mode)      */
        E_PIN_ = 0;                                                          /* Clock pin cleared                                */

        /* Delay for 15ms to allow for LCD Power on reset           */
        DelayPORXLCD();
 /*-------------------reset procedure through software-------------------------------------*/
		 WriteCmdXLCD(0x30);
                 Delay10KTCYx(0x05);
		 WriteCmdXLCD(0x30);
		 Delay10KTCYx(0x01);
		 WriteCmdXLCD(0x32);
                 while( BusyXLCD() );
/*------------------------------------------------------------------------------------------*/

        // Set data interface width, # lines, font
        while(BusyXLCD());                                                  /* Wait if LCD busy                                  */
        WriteCmdXLCD(lcdtype);                                              /* Writing code for lcdtype                          */

        /* Turn the display on then off */
        while(BusyXLCD());                                                  /* Wait if LCD busy                                  */
        WriteCmdXLCD(DOFF&CURSOR_OFF&BLINK_OFF);                            /* Write command for Display OFF/cursor Blink OFF    */
        while(BusyXLCD());                                                  /* Wait if LCD busy                                  */
        WriteCmdXLCD(DON);                                                  /* Write command for Display ON                      */

        /* Clear display            */
        while(BusyXLCD());                                                  /* Wait if LCD busy                                  */
        WriteCmdXLCD(0x01);                                                 /* Clear display                                     */
        /* Set DD Ram address to 0  */
        while(BusyXLCD());                                                  /* Wait if LCD busy                                  */
        SetDDRamAddr(0x80);                                                 /* Set Display data ram address to 0                 */
        return;
    }

/* ----------------------------- Writing Time string to XLCD ------------------------------------*/
void Write_time_XLCD(char *str)
{ unsigned char i=0;
WriteCmdXLCD(0x80);
    while(i!=16)
    {
    WriteDataXLCD(*str);
    str++;
    i++;
    }
str++;
i=17;
WriteCmdXLCD(0xC0);
while(i!=32)
    {    
    WriteDataXLCD(*str);
    str++;
    i++;
    }
    }