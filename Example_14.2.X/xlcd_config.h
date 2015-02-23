/*
 * File name            : xlcd_config.h
 * Compiler             : XC8 compiler
 * IDE                  : Microchip MPLAB X IDE v1.90
 * Author               : Etiq Technologies
 * Description          : Example_7.4 External Character LCD
 *                      : Created on November 23, 2013, 5:10 PM
 *                      : External character LCD configuration header file
 */

#ifndef XLCD_CONFIG_H
#define	XLCD_CONFIG_H

#if defined(__XC)
    #include <plib\xlcd.h>
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
    #include <xlcd.h>
#endif

#define BIT8
/*                  DATA_PORT definitions                        */

 #define PORTB      			PORTD
 #define TRISB                          TRISD

/*                  CONTROL_PORT definitions                    */

 #define RW_PIN_   LATAbits.LATA1   		/* PORT for RW */
 #define TRIS_RW_  TRISAbits.TRISA1             /* TRIS for RW */

 #define RS_PIN_   LATAbits.LATA2   		/* PORT for RS */
 #define TRIS_RS_  TRISAbits.TRISA2             /* TRIS for RS */

 #define E_PIN_    LATAbits.LATA0               /* PORT for D  */
 #define TRIS_E_   TRISAbits.TRISA0             /* TRIS for E  */
extern void DelayFor18TCY(void);
extern void DelayPORXLCD(void);
extern void DelayXLCD(void);

void Write_time_XLCD(char *str);


#endif

