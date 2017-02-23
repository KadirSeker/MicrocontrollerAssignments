/*
 * lcd.h
 *
 * Created: 16-2-2017 11:17:16
 *  Author: Christiaan
 */ 


#ifndef LCD_H_
#define LCD_H_

#define LCD_E 	3
#define LCD_RS	2

void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);
void lcd_display_text(char *str);
void lcd_init( void );
void lcd_set_cursor(int position);

int counter;

#endif /* LCD_H_ */