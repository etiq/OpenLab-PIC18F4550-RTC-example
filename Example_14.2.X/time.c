
/*
 * File name            : time.c
 * Compiler             : XC8 compiler
 * IDE                  : Microchip MPLAB X IDE v1.90
 * Author               : Etiq Technologies
 * Description          : Example_14.2 Real Time Clock
 *                      : Created on October 30, 2013, 2:13PM
 *                      : Time functions source file
 */

#if defined(__XC) || defined(__18CXX)
#include "i2c_1.h"
#include "time.h"
#include "array.h"
#include "delay.h"
#include "uart.h"
#include <string.h>
#endif



/*____________________________________Decimal to BCD Conversion_______________________________________________________*/

unsigned char DEC_to_BCD(unsigned char t)
    {
    return (((t/10)<<4)|(t%10));
    }


/*____________________________________Conversion of ASCII BCD_________________________________________________________*/

unsigned char BCD_format(unsigned char *str)
    {
    unsigned char a;
    a = (*str-'0')<<4;
    str++;
    return (a|(*str-'0'));
    }


/*____________________________BCD to decimal conversion function________________________________________________________*/

unsigned char BCD_to_DEC(unsigned char c)
    {
    return ((c>>4)*10+(c&0x0F)*1);
    }


/*___________________________Array/string clearing function______________________________________________________________*/

void Clear_array(unsigned char *e, unsigned char n)
    {
 unsigned char i;
    for(i=0;i<n;i++)
        {
        *e = ' ';
        e++;
        }
    }


/*_______________________________Time formating function______________________________________________________________*/

/* Function converts the input arguments second, minute and hour into BCD format
 * Identifies the 12/24 hour mode from user entry to write to DS1307.
 * 
 */
void Set_time(unsigned char* sec, unsigned char* min, unsigned char* hour, unsigned char mode)
    {
    unsigned char s, m, h, x, y, z;
    unsigned char str3[37] = "\nEnter the time in the format HHMMSS";
	unsigned char error[] = "\nInvalid Entry..!";
do
    {
    Write_str(str3);
    Read_string(str, 6);
    h = BCD_format(str);
    m = BCD_format(str+2);
    s = BCD_format(str+4);
    x = BCD_to_DEC(s);
    y = BCD_to_DEC(m);
    z = BCD_to_DEC(h);
   if((mode==0)||(mode==1))
   {
    if(((x>=0&&x<=59) && (y>=0&&y<=59) && (z>=1&&z<=12) ))
        {
        s = s&0x7F;
        m = m&0x7F;
        h = h&0x1F;
        if(mode==0)
            h = h|0x40;
                else if(mode == 1)
                    h = h|0x60;
        h = h&0x7F;
        }
    else
        Write_str(error);
    }
   else if(((x>=0&&x<=59) && (y>=0&&y<=59) && (z>=0&&z<=24) ) && (mode==2))
        {
        h = h|0x00;
        h = h&0x7F;
        }
    else
        Write_str(error);            /* Checking invalid entry by testing with a condition in the loop         */
    }while(!(((x>=0&&x<=59) && (y>=0&&y<=59) && (z>=1&&z<=12))  ||   ((x>=0&&x<=59) && (y>=0&&y<=59) && (z>=0&&z<=24) && (mode==2)) ));

    *sec = s;
    *min = m;
    *hour = h;
    }
/*______________________________ Function to Read day data from UART________________________________________________*/

unsigned char Set_day(void)
           {
unsigned char error[18] = "\nInvalid Entry..!";
unsigned char str5[] = "\nEnter the DAY SUN-01 MON-02 TUE-03 WED-04 THURS-05 FRI-06 SAT-07\0";

            unsigned char day;
            Write_str(str5);
            Clear_array(str, 8);
            do
            {
            Read_string(str, 2);
            day = BCD_format(str);
            Write_str(str);
            if(day>=1 && day<=7)
                {
                return (day);
                }
            else{
                Write_str(error);
     //           Write_str(data_1);
                }
             }while(!(day>=1 && day<=7));           /* Checking invalid entry by testing with a condition in the loop         */
           }

/*__________________________Date formatting function__________________________________________________________________*/

void Set_date(unsigned char* date, unsigned char* month, unsigned char* year)
    {
   unsigned char x, y, z;
   unsigned char str6[30] = "\nEnter DATE/MONTH/YEAR\tDDMMYY", error[] = "\nInvalid Entry..!";   
do
    {
    Write_str(str6);
    Read_string(str, 6);
    *date = BCD_format(str);
    *month = BCD_format(str+2);
    *year = BCD_format(str+4);
    x = BCD_to_DEC(*date);
    y = BCD_to_DEC(*month);
    z = BCD_to_DEC(*year);
    if((x>=1&&x<=31) && (y>=1&&y<=12) && (z>=1&&z<=99))
    {
        *date = *date & 0x3F;
        *month = *month & 0x1F;
        *year = *year & 0xFF;
    }
    else
     Write_str(error);
   }while(!((x>=0&&x<=31) && (y>=0&&y<=12) && (z>=0&&z<=99)));   /* Checking invalid entry by testing with a condition in the loop  */
   }


/*_______________________________________Reading Data from UART____________________________________________________*/

unsigned char Get_data(void)
    {
 unsigned char s, m, h, day, date, month, year, mode=4;
 unsigned char str2[19] = "\nSELECT MODE 12/24";
 unsigned char str8[14] = "\nEnter AM/PM?";
 unsigned char error[] = "\nInvalid Entry..!";
 unsigned char s_1[3] = "12";   
 unsigned char s_2[3] = "24";   
 unsigned char s_3[3] = "am";   
 unsigned char s_4[3] = "AM";   
 unsigned char s_5[3] = "pm";   
 unsigned char s_6[3] = "PM";   
do
    {
    Write_str(str2);
    Read_string(str, 2);                             /* Reading a string from UART                                         */
        if(!(strcmp(str, s_1)))                      /* Test for 12 hour mode                                              */
        {
         do{
            Write_str(str8);
            Read_string(str, 2);
                if(!(strcmp(str, s_3)) || !(strcmp(str, s_4))  )      /* Testing if string is AM                           */
                    {
                    mode = 0;                               /* AM                                                            */
                    }
                    else if(!(strcmp(str, s_5)) || !(strcmp(str, s_6))  )      /* Testing if string is PM                   */
                    {
                    mode = 1;
                    }
                        else
                        {
                        Write_str(error);
                        }
             }while(!(mode==0||mode==1));
         }
        else if(!(strcmp(str, s_2)))                                           /* Testing for 24 hour mode                 */
     {
     mode = 2;
     }
     else
         {
         Write_str(error);
         }
    }while(!(mode==0 || mode==1 || mode==2));
    Set_time(&s, &m, &h ,mode);
    Write_time_(s, m, h);                           /* Writing sec, min, hour registers of RTC immediately after user entry */
    day = Set_day();
    Set_date(&date, &month, &year);
    Write_time(day, date, month, year);
    return (mode);
    }

/*________________________Seconds register reading function_________________________________________________________*/

void Read_sec(unsigned char * e)
    {
     unsigned char c;
     e=e+6;
     c = Read();
     *e = ((c>>4)&0x07) + '0';
     e++;
     *e = (c&0x0F) + '0';
     e++;
     *e = ' ';
    }

/*__________________________Minute register reading function_____________________________________________________*/

void Read_min(unsigned char * e)
    {
     unsigned char c;
     e= e+3;
     c = Read();
     *e = ((c>>4)&0x07) + '0';
     e++;
     *e = (c&0x0F) + '0';
     e++;
     *e = ':';
    }

/*_____________________________Hour register reading function_____________________________________________________*/

void Read_hour(unsigned char * e, unsigned char mode)
    {
     unsigned char c,i=0;
     c = Read();
     if((mode==0)||(mode==1))
     *e = ((c>>4)&0x01) + '0';
     else
     *e = ((c>>4)&0x03) + '0';
     e++;
     *e = (c&0x0F) + '0';
     e++;
     *e = ':';
     while(i!=11)
        {
         e++;
         i++;
        }
     if((c>>6)&0x01)
     {
     if((c>>5)&0x01)
         *e = 'P';
     else
         *e = 'A';
         e++;
         *e = 'M';
      }
    }

/*________________________________________String writing function______________________________________________________*/

/*
 * Writing a day of week string data to string variable
 */
void Write_ARR(unsigned char *c, unsigned char * e)
    {
    e = e+17;
    while(*c!='\0')
        {
        *e = *c;
        e++;
        c++;
        }
    e = e+2;
    *e = ' ';
    }

/*_____________________________Function to identify the day read from slave__________________________________________________*/

void write_DAY(unsigned char day)
    {
 unsigned char day_1[4] = "SUN";
 unsigned char day_2[4] = "MON";
 unsigned char day_3[4] = "TUE";
 unsigned char day_4[4] = "WED";
 unsigned char day_5[4] = "THU";
 unsigned char day_6[4] = "FRI";
 unsigned char day_7[4] = "SAT";

    switch(day)
        {
            case 1: Write_ARR(day_1, time);
            break;
            case 2: Write_ARR(day_2, time);
            break;
            case 3: Write_ARR(day_3, time);
            break;
            case 4: Write_ARR(day_4, time);
            break;
            case 5: Write_ARR(day_5, time);
            break;
            case 6: Write_ARR(day_6, time);
            break;
            case 7: Write_ARR(day_7, time);
            break;
        }
    }


/*____________________________________Day of week register read function_______________________________________________*/

void Read_day(void)
    {
    write_DAY(0x07 & Read());
    }

/*__________________________________________Date read function_________________________________________________________*/

void Read_date(unsigned char * e)
    {
     unsigned char c;
     e= e+23;
     *e = ' ';
     e++;
     c = Read();
     *e = ((c>>4)&0x03) + '0';
     e++;
     *e = (c&0x0F) + '0';
     e++;
     *e = '/';
    }

/*______________________________________________Month read function____________________________________________________*/

void Read_month(unsigned char *e)
    {
     unsigned char c;
     e= e+27;
     c = Read();
     *e = ((c>>4)&0x01) + '0';
     e++;
     *e = (c&0x0F) + '0';
     e++;
     *e = '/';
    }


/*____________________________________Year read function_____________________________________________________________*/

void Read_year(unsigned char *e)
     {
     unsigned char c;
     e= e+30;
     c = Read();
     *e = (c>>4) + '0';
     e++;
     *e = (c&0x0F) + '0';
     e++;
     *e = '\r';
     e++;
     *e = '\0';
    }