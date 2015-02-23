/*
 * File name            : i2c_1.h
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_14.1 Real Time Clock
 *                      : Created on October 30, 2013, 12:17 PM
 *                      : I2C functions declaration header file
 */

#ifndef I2C_1_H
#define	I2C_1_H

/*________________________________I2C slave reading Function_______________________________________ */
unsigned char Read(void);
/*
 * Include          :       i2c_1.h
 * Description      :       Continuously reads from I2C slave DS1307
 * Arguments        :       None
 * Returns          :       BCD value
 */



/*_____________________Function to write slave DS1307______________________________________________*/
void Write_time(unsigned char day, unsigned char date, unsigned char month, unsigned char year);
/*
 * Include          :       i2c_1.h
 * Description      :       Writes time data to slave DS1307
 * Arguments        :       BCD values
 * Returns          :       None
 */



/*____________________Time keeper register read function of DS1307_________________________________*/
void Read_time(unsigned char mode);
/*
 * Include          :       i2c_1.h
 * Description      :       Reads time keeper register of the slave DS1307
 * Arguments        :       BCD values
 * Returns          :       None
 */



/*_______________Time keeper register read function of DS1307_______________________________________*/
unsigned char Read_From_Addr(unsigned char addr);
/*
 * Include          :       i2c_1.h
 * Description      :       Reads from a specific register address of the slave DS1307
 * Arguments        :       Address
 * Returns          :       BCD values
 */


/*_______________________Write function to a specific address location of the slave DS1307_____________*/
void Write_to_Addr(unsigned char data, unsigned char addr);
/*
 * Include          :       i2c_1.h
 * Description      :       Writes to a specific register address of the slave DS1307
 * Arguments        :       Data, Address
 * Returns          :       None
 */


/*______________________________________ Buffer register clear function_____________________________*/
extern void ReadBUF(void);
/*
 * Include          :       i2c_1.h
 * Description      :       Read function to clear buffer register .
 * Arguments        :       None
 * Returns          :       None
 */



/* ___________________________________Write function to I2C slave DS1307_________________________________*/
void Write_I2C(unsigned char c);
/*
 * Include          :       i2c_1.h
 * Description      :       Continuous Write function to I2C slave DS1307
 * Arguments        :       Data (BCD value)
 * Returns          :       None
 */

void Write_time_(unsigned char s, unsigned char m, unsigned char h);

#endif	/* I2C_1_H */

