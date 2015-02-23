/*
 * File name            : i2c_1.c
 * Compiler             : XC8 compiler
 * IDE                  : Microchip MPLAB X IDE v1.90
 * Author               : Etiq Technologies
 * Description          : Example_14.2 Real Time Clock
 *                      : Created on October 30, 2013, 1:34 PM
 *                      : i2c Functions source file
 */
#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File 		*/
    #include <plib\i2c.h>
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File 		*/
    #include <i2c.h>
#endif

#if defined(__XC) || defined(__18CXX)
#include "delay.h"
#include "i2c_1.h"
#include "array.h"
#include "time.h"
#include "uart.h"
#endif

/*___________________________________Buuffer register clear function__________________________________________________________*/

void ReadBUF(void)                                                  /* Read function for clearing Buffer register           */
    {
    unsigned char c;
    c = SSPBUF;                                                     /* Reading out the buffer register to a variable        */
    c = SSPBUF;
    }


/*___________________________________I2C write function_______________________________________________________________________*/

void Write_I2C(unsigned char c)
{
    WriteI2C(c);                                                    /* I2C slave write function call                        */
    ReadBUF();                                                      /* Buffer clear function call                           */
}

/*_____________________________________I2C read function________________________________________________________________________*/

unsigned char Read(void)
    {
     unsigned char c;
     RestartI2C();                                                  /* Function call to Restart I2C bus                     */
     delay_ms(1);                                                   /* 1msec delay                                          */
     Write_I2C( 0xD1 );                                             /* Writing I2C slave address in read mode               */
     c = ReadI2C();                                                 /* Reading data from slave                              */
     ReadBUF();                                                     /* Buffer clear                                         */
     return(c);                                                     /* Reaturn data                                         */
    }

void Write_time_(unsigned char s, unsigned char m, unsigned char h)
{
     OpenI2C(MASTER, SLEW_OFF);                                     /* Initialize I2C module for 100kHz mode                    */                                                             //100kHz Baud clock @8MHz
     delay_ms(1);                                                   /* 1msec delay delay                                        */
     StartI2C();                                                    /* Starting I2C bus                                         */
     ReadBUF();                                                     /* Clearing buffer register                                 */
     Write_I2C(0xD0);                                               /* Write I2C slave address in write mode                    */
     delay_ms(1);
     Write_I2C(0x00);                                               /* Writing I2C slave register address                       */
     delay_ms(1);
     Write_I2C(s);                                                  /* Writing seconds data to I2C slave register               */
     delay_ms(1);
     Write_I2C(m);                                                  /* Writing minutes data to I2C slave register               */
     delay_ms(1);
     Write_I2C(h);                                                  /* Writing hours data to I2C slave register                 */
     delay_ms(1);
     StopI2C();
}


/*____________________________________________Time writing function______________________________________________________________*/

void Write_time(unsigned char day, unsigned char date, unsigned char month, unsigned char year)
     {
     StartI2C();                                                    /* Starting I2C bus                                         */
     ReadBUF();                                                     /* Clearing buffer register                                 */
     Write_I2C(0xD0);                                               /* Write I2C slave address in write mode                    */
     delay_ms(1);
     Write_I2C(0x03);                                               /* Writing I2C slave register address                       */
     delay_ms(1);
     Write_I2C(day);                                                /* Writing day data to I2C slave register                   */
     delay_ms(1);
     Write_I2C(date);                                               /* Writing date to I2C slave register                       */
     delay_ms(1);
     Write_I2C(month);                                              /* Writing month to I2C slave register                      */
     delay_ms(1);
     Write_I2C(year);                                               /* Writing year data to I2C slave register                  */
     delay_ms(1);
     StopI2C();                                                     /* stoping I2C bus                                          */
     CloseI2C();
     delay_ms(100);
     }

void Read_time(unsigned char mode)
    {
     OpenI2C(MASTER, SLEW_OFF);                                     /* Initialize I2C module for 100kHz mode                    */                                                             //100kHz Baud clock @8MHz
     delay_ms(1);                                                   /* 1msec delay delay                                        */
     StartI2C();                                                    /* Starting I2C bus                                         */
     delay_us(10);
     Write_I2C(0xD0);                                               /* Write I2C slave address in write mode                    */
     delay_ms(1);
     Write_I2C(0x00);                                               /* Writing I2C slave register address                       */
     delay_ms(10);
     Clear_array(time, 33);                                         /* Clearing a string                                        */
     Read_sec(time);                                                /* Reading seconds register of DS1307                       */
     Read_min(time);                                                /* Reading minute register of DS1307                        */
     Read_hour(time, mode);                                         /* Reading hour register of DS1307                          */
     Read_day();                                                    /* Reading day of week register of DS1307                   */
     Read_date(time);                                               /* Reading date register of DS1307                          */
     Read_month(time);                                              /* Reading month register of DS1307                         */
     Read_year(time);                                               /* Reading year register of DS1307                          */
     IdleI2C();                                                     /* Wait until I2C bus getting idle state                    */
     NotAckI2C();                                                   /* Sending Not acknowledge pulse to I2C slave               */
     IdleI2C();                                                     /* Wait until I2C bus getting idle state                    */
     StopI2C();                                                     /* Stops I2C bus                                            */
     CloseI2C();
}


/* _________________________________________________I2C Read function from a specific address_____________________________________*/

unsigned char Read_From_Addr(unsigned char addr)
    {
     unsigned char c;
     StartI2C();
     delay_ms(1);
     Write_I2C(0xD0);
     Write_I2C(addr);
     RestartI2C();
     delay_ms(1);
     Write_I2C( 0xD1 );
     c = ReadI2C();
     ReadBUF();
     StopI2C();
     return(c);
    }

/*_________________________________I2C write function to a specific address____________________________________________________*/

void Write_to_Addr(unsigned char data, unsigned char addr)
     {
     StartI2C();
     ReadBUF();
     Write_I2C(0xD0);
     delay_ms(1);
     Write_I2C(addr);
     delay_ms(1);
     Write_I2C(data);
     delay_ms(1);
     StopI2C();
     delay_ms(200);
     }