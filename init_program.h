#ifndef HEADER_FILE
#define HEADER_FILE

#include "lpc17xx_libcfg_default.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_i2c.h"
#include "lpc17xx_timer.h"
#include "stdio.h"

#include "./touch/ili_lcd_general.h"
#include "./touch/touch_panel.h"

void start_init();

void pin_Configuration();
void init_timer();
void init_i2c_eeprom();


#endif