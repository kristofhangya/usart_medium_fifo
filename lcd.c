#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

void LCD_init()
{
	//portok beallitasa
	DDRE |= 0xf0;		
	DDRF |= (1<<CMD_RS) | (1<<CMD_RW) | (1<<CMD_EN);	
	//iras
	PORTF &= ~(CMD_RW);		
	//reset
	PORTF &= ~(1<<CMD_RS);
	PORTE = 0x20;
	LCD_clock();
	LCD_clock(); 
	LCD_clock();

	//4 bites uzemmod, 7x5pixel, 2soros
	LCD_command(0x28);
	LCD_command(0x28);
	LCD_command(0x28);
	//lcd alaphelyzetbe
	LCD_command(0x02);
	//ldc torlese
	LCD_command(0x01);
	//kurzor villog, alahuzas be, LCD be
	LCD_command(0x08 | (1<<LCD_EN) | (1<<LCD_CUR) | (1<<LCD_BL));
}
void LCD_clock()		//LCD engedélyezés várakoztatás
{
	_delay_ms(6);
	PORTF |= (1<<CMD_EN);
	_delay_ms(5);
	PORTF  &= ~(1<<CMD_EN);
      _delay_ms(1);
}
void LCD_command(unsigned char val)		//PARANCSOK
{
	PORTF &= ~(1<<CMD_RS);
	PORTE = val & 0xf0;		
	LCD_clock();
	PORTE = val << 4;
	LCD_clock();
}
void LCD_data(unsigned char val)
{
	PORTF |= (1<<CMD_RS);
	PORTE = val & 0xf0;
	LCD_clock();				//feldolgozás
	PORTE = val << 4;			//kiírás	
	LCD_clock();				
}
void LCD_goto(unsigned char row, unsigned char col)
{
	if((col>=16) || (row>=4))return;
	if(row>=2)
	{
		row = row - 2;
		col = col + 16;
	} 
	LCD_command((1<<7)|(row<<6)|col);
}
