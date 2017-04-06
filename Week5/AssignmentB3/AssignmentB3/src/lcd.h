/* lcd.h */

#ifndef LCD_H_
#define LCD_H_
#define LCD_RS 2
#define LCD_E 3

void init_lcd_4bit(void);
void display_text(char *str);
void set_cursor(int position);
void lcd_write_data(unsigned char byte);
void lcd_write_command(unsigned char byte);
void lcd_strobe_lcd_e(void);
void clearScreen(void);

#endif /* LCD_H_ */