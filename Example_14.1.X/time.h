/*
 * File name            : time.h
 * Compiler             : MPLAB XC8/ MPLAB C18 compiler
 * IDE                  : Microchip  MPLAB X IDE v1.90/ MPLAB IDE v8
 * Author               : Etiq Technologies
 * Description          : Example_14.1 Real Time Clock
 *                      : Created on October 30, 2013, 12:40 PM
 *                      : Time functions header file
 */

#ifndef TIME_H
#define	TIME_H
/* _______________________________________main Function__________________________________________________*/
void main(void);
/*
 * Include          :       time.h
 * Description      :       main routine
 * Arguments        :       None
 * Returns          :       None
 */


/*_____________________________Decimal to BCD conversion function________________________________________*/
unsigned char DEC_to_BCD(unsigned char t);
/*
 * Include          :       time.h
 * Description      :       Converting the decimal argument to BCD value
 * Arguments        :       Decimal value
 * Returns          :       BCD value
 */


/*___________________________String to BCD conversion function____________________________________________*/
unsigned char BCD_format(unsigned char *str);
/*
 * Include          :       time.h
 * Description      :       Converting each string elements to BCD value
 * Arguments        :       Address of a string
 * Returns          :       BCD value  
 */


/*____________________________BCD to Decimal conversion function_________________________________________*/
unsigned char BCD_to_DEC(unsigned char c);
/*
 * Include          :       time.h
 * Description      :       Converting a BCD (input parameter) to decimal value
 * Arguments        :       BCD value
 * Returns          :       Decimal value  
 */


/*_____________________________________Clearing array function___________________________________________*/
void Clear_array(unsigned char *e, unsigned char n);
/*
 * Include          :       time.h
 * Description      :       Clearing an array variable
 * Arguments        :       Address of string(or address of array), Offset value(Number of elements that
 *                          have to be cleared from starting address of the string)
 * Returns          :       None
 */


/*____________________________________Time setting function______________________________________________*/
void Set_time(unsigned char* sec, unsigned char* min, unsigned char* hour, unsigned char mode);
/*
 * Include          :       time.h
 * Description      :       Converting the input time data to BCD format
 * Arguments        :       Address of character variables, Decimal value
 * Returns          :       None
 */


/*___________________________________Day of week setting function ________________________________________*/
unsigned char Set_day(void);
/*
 * Include          :       time.h
 * Description      :       Converting the input day data number to BCD format
 * Arguments        :       None
 * Returns          :       BCD value
 */

/*_______________________________________Date setting function_____________________________________________*/
void Set_date(unsigned char* date, unsigned char* month, unsigned char* year);
/*
 * Include          :       time.h
 * Description      :       Converting the day, month, year decimal data to BCD format
 * Arguments        :       Address of character variables
 * Returns          :       None
 */


/*___________________________________Data getting and processing function__________________________________*/
unsigned char Get_data(void);
/*
 * Include          :       time.h
 * Description      :       Data input from UART and writing to I2C slave after converting into BCD format
 * Arguments        :       None
 * Returns          :       Decimal value
 */


/*______________________________________Seconds register Read function _____________________________________*/
void Read_sec(unsigned char * e);
/*
 * Include          :       time.h
 * Description      :       Reads seconds register of I2C slave DS1307 and stores value in a string variable
 * Arguments        :       Address of the string variables
 * Returns          :       None
 */


/*______________________________________Minutes register reading function_____________________________________*/
void Read_min(unsigned char * e);
/*
 * Include          :       time.h
 * Description      :       Reads minutes register of I2C slave DS1307 and stores value in a string variable
 * Arguments        :       Address of the string variables
 * Returns          :       None
 */


/*______________________________________Hour register reading function________________________________________*/
void Read_hour(unsigned char * e, unsigned char mode);
/*
 * Include          :       time.h
 * Description      :       Reads hour register of I2C slave DS1307 and stores value in a string variable
 * Arguments        :       Address of the string variables, Decimal value
 * Returns          :       None
 */


/*__________________________________________String writing function____________________________________________*/
void Write_ARR(unsigned char *c, unsigned char * e);
/*
 * Include          :       time.h
 * Description      :       Writing a string data to a string variable
 * Arguments        :       Address of string variables
 * Returns          :       None
 */


/*_____________________________________Day of week writing function____________________________________________*/
void write_DAY(unsigned char day);
/*
 * Include          :       time.h
 * Description      :       Identifying the day of week from the input parameter
 * Arguments        :       Decimal value
 * Returns          :       None
 */


/*_____________________________________Day of week reading function____________________________________________*/
void Read_day(void);
/*
 * Include          :       time.h
 * Description      :       Reading the day of week from the day of week register of I2C slave DS1307
 * Arguments        :       None
 * Returns          :       None
 */


/*_____________________________________Day of week reading function____________________________________________*/
void Read_date(unsigned char * e);
/*
 * Include          :       time.h
 * Description      :       Reading the day of week from the day of week register of I2C slave DS1307
 * Arguments        :       Address of string the variable
 * Returns          :       None
 */



/* ___________________________________Function to read month___________________________________________________*/
void Read_month(unsigned char *e);
/*
 * Include          :       time.h
 * Description      :       Reading the month from the month register of I2C slave DS1307
 * Arguments        :       Address of the string variable
 * Returns          :       None
 */


/* ___________________________________Function to read year___________________________________________________*/
void Read_year(unsigned char *e);
/*
 * Include          :       time.h
 * Description      :       Reading the year from the year register of I2C slave DS1307
 * Arguments        :       Address of the string variable
 * Returns          :       None
 */
#endif	/* TIME_H */