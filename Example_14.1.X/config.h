/*
 * File name            : config.h
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_14.1 Real Time Clock
 *                      : Created on May 03, 2014, 11:30 AM
 *                      : Configuration bit settings header file
 */


#ifndef CONFIG_H
#define	CONFIG_H
// PIC18F4550 Configuration Bit Settings
#if defined(__18CXX)

 	 #pragma config WDT 	= OFF          		//WDT disabled (enabled by SWDTEN bit)
         #pragma config STVREN 	= OFF           	//stack overflow/underflow reset enabled
	 #pragma config PWRT 	= OFF
	 #pragma config	BOR   	= OFF
  	 #pragma config	PBADEN  = OFF
	 #pragma config	MCLRE	= ON
	 #pragma config	LVP     = OFF
         #pragma config XINST 	= OFF          		//Extended instruction set disabled
         #pragma config CP0 	= OFF            	//Program memory is not code-protected
         #pragma config FOSC 	= HS          		//HS oscillator, PLL enabled, HSPLL used by USB
         #pragma config IESO 	= OFF
         #pragma config FCMEN 	= OFF          		//Fail-Safe Clock Monitor disabled
         #pragma config WDTPS 	= 32768        	 	//1:32768

#include <p18cxxx.h>   /* C18 General Include File */

#elif defined(__XC)

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)
// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)
// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)
// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#include <xc.h>        /* XC8 General Include File */

#endif

#endif	/* CONFIG_H */

