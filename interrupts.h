#ifndef HEADER_FILE
#define HEADER_FILE

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_i2c.h"

#include "global_import.h"
#include "lpc17xx_timer.h"
#include "stdio.h"
#include "./touch/ili_lcd_general.h"
#include "./touch/touch_panel.h"

void TIMER0_IRQHandler(void);
void TIMER2_IRQHandler(void);

#endif