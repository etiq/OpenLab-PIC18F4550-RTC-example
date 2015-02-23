/*
 * File name            : uart_1.h
 * Compiler             : XC8 compiler
 * IDE                  : Microchip MPLAB X IDE v1.90
 * Author               : Etiq Technologies
 * Description          : Example_14.2 Real Time Clock
 *                      : Created on October 30, 2013, 1:20 PM
 *                      : UART functions header file
 */
#ifndef UART_H
#define	UART_H

/*___________________________________UART configuration function___________________________________*/

void UsartConfig(unsigned char config1, unsigned char config2);
/*
 * Include          :       uart_1.h
 * Description      :       Configure UART module with desired baud rate
 * Arguments        :       Configuraion data
 * Returns          :       None
 */


/*_____________________________________UART byte write function_____________________________________*/

void Write(char data);
/*
 * Include          :       uart_1.h
 * Description      :       Writes a byte to UART
 * Arguments        :       character
 * Returns          :       None
 */


/*_____________________________________UART string write function___________________________________*/

void Write_str(unsigned char *c);
/*
 * Include          :       uart_1.h
 * Description      :       Writes string data to UART
 * Arguments        :       Address of a string
 * Returns          :       None
 */


/*_____________________________________UART Byte read function_______________________________________ */

unsigned char Read_char(void);
/*
 * Include          :       uart_1.h
 * Description      :       Reads a single byte from UART
 * Arguments        :       None
 * Returns          :       Character
 */



/*__________________________________________UART string read function________________________________*/

void Read_string(unsigned char *str, unsigned char n);
/*
 * Include          :       uart_1.h
 * Description      :       Reads string data from UART
 * Arguments        :       Address of a string, string length
 * Returns          :       None
 */


#endif	/* UART_1_H */

