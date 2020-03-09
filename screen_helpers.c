#include "screen_helpers.h"

void display_home() {
	
	LCD_write_english_string(0x0000, 0x0000, "------------------------------", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0010, "             0 stop           ", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0020, "------------------------------", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0030, "The timer starts at 10 seconds", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0040, "and starts counting down. When", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0050, "you push the KEY1 button, the ", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0060, "timer will stop. Easy right?! ", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0070, "But the timer will go blank at", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0080, "about 4 seconds so you will   ", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0x0090, "have to guess how close the   ", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0xA0, "is to 0!                      ", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0xB0, "------------------------------", 0xFFFF, 0xF81F);
	LCD_write_english_string(0x0000, 0xC0, "      Press KEY2 to play!     ", 0xFFFF, 0xF81F);
}