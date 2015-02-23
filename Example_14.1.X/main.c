/*
 * File name            : main.c
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_14.1 Real Time Clock
 *                      : Created on October 30, 2013, 2:13PM
 *                      : Example code implements time setting and time reading of external RTC DS1307.
 */

/*
 * RTC DS1307, low-power clock/calendar provides seconds, minutes, hours, day, date, month, and year information.
 * Two hardware modules UART and I2C are enabled for communication. User interface is implemented through UART
 * and the microcontroller communicates with DS1307 using I2C protocol. DS1307 operates as a slave device on the
 * I2C bus. On power on reset user is asked for time settings. On entering valid data, RTC starts running and
 * continuously displays time read from time keeper register. At any time user can re-enter the new data to
 * DS1307. Refer data sheet of DS1307 for time keeper registers mapping.

 I2C bus
 --------
 PORTB RB0 - SDA (Data)
 PORTB RB1 - SCL (Clock)

 LCD PIN configurations
 ----------------------
    8 bit data
    Control PORT    -       PORTA

    RA0     -       EN
    RA1     -       R/W
    RA2     -       RS

    Data PORT       -       PORTD

 USART module PORT-PIN Configuration
 -----------------------------------
    Tx     -       RC6
    Rx     -       RC7

 */
#if defined(__XC)
    #include <plib\usart.h>
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File 	*/
#elif defined(__18CXX)
    #include <usart.h>
#endif

#if defined(__XC) || defined(HI_TECH_C)
#include <stdint.h>        /* For uint8_t definition 		*/
#include <stdbool.h>       /* For true/false definition 	*/
#endif

#if defined(__XC) || defined(__18CXX)
#include <string.h>
#include "config.h"
#include "array.h"
#include "delay.h"
#include "time.h"
#include "uart.h"
#include "i2c_1.h"
#endif

#define Fosc 20000000                                                 /* External crystal frequency                              */
#define baud 9600                                                     /* UART baud rate                                          */
#define config2 ((Fosc/baud/64)-1)
#define Reload ((20000000/100000)/4-1);                               /* MSSP Baud Rate Reload Register value                    */


/*_________________________________________ main function_____________________________________________________________*/
void main(void)
  {
     unsigned char mode;
     unsigned char str7[35] = "\nDo you want to set the time? y/n";
     unsigned char str8[29] = "Please enter a valid data..!";
     unsigned char config1 = 0x00, c;
     config1 = (USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX & USART_BRGH_LOW);
     SSPADD = Reload;                                               /* loading MSSP Baud Rate Reload Register value           */
     UsartConfig(config1, config2);                                 /* Invoking UART configuration function                   */
     do
     {
     Write_str(str7);
     c = Read_char();                                               /* Reading a string from UART                                         */
        if((c== 'Y')  ||  (c== 'y'))                                /* Test for 12 hour mode                                              */
        mode = Get_data();                                          /* function call to get input data from user              */
        else if((c== 'N')  ||  (c== 'n'))
        break;
        else
        Write_str(str8);
     }while(!((c== 'Y')  ||  (c== 'y')  ||  (c== 'N')  ||  (c== 'n'))) ;
     while(1)                                                       /* Infinite loop                                          */
     {
     Read_time(mode);                                               /* function call to read RTC DS1307 continuously          */
     Write_str(time);                                               /* Write the read time data from the slave to UART          */
     delay_ms(10);
     }
  }