#include "init_program.h"

void pin_Configuration() {
	PINSEL_CFG_Type config;
	
	//===========================================================//
	// KEY1 & KEY2 pin configuration
	//===========================================================//
	// remplissage pour P2.10 sur GPIO port 2.10 -> KEY2
	config.Portnum = PINSEL_PORT_2;
	config.Pinnum = PINSEL_PIN_10;
	config.Funcnum = PINSEL_FUNC_0;
	config.Pinmode = 0;
	config.OpenDrain = PINSEL_PINMODE_NORMAL;
	PINSEL_ConfigPin(&config);
	
	// remplissage pour P2.11 sur GPIO port 2.11 -> KEY1
	config.Pinnum = PINSEL_PIN_11;
	PINSEL_ConfigPin(&config);
	
	
	//===========================================================//
	// IC20 pin configuration
	//===========================================================//
	// remplissage pour P0.27 sur SDA0
	config.Portnum = PINSEL_PORT_0;
	config.Pinnum = PINSEL_PIN_27;
	config.Funcnum = PINSEL_FUNC_1;
	PINSEL_ConfigPin(&config);
	
	// remplissage pour P0.28 sur SCL0
	config.Pinnum = PINSEL_PIN_28;
	PINSEL_ConfigPin(&config);
}

void init_i2c_eeprom() {

	I2C_Init(LPC_I2C0, 400000);	// power + clockrate (400000 : clockrate in Hz (= 400kHz))
	I2C_Cmd(LPC_I2C0, ENABLE);	// enable I2C0's operation
}

void init_timer() {
	
	TIM_MATCHCFG_Type configMatch; // Config du timer
	TIM_TIMERCFG_Type configPrescale; // Config du prescaler
	
	// Preparation de la configuration du prescaler
	configPrescale.PrescaleOption = TIM_PRESCALE_USVAL; // précision du prescaler en microseconde
	configPrescale.PrescaleValue = 500;

	// Application de la config
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &configPrescale);
	
	// Preparation de la configuration du timer
	configMatch.MatchChannel = 0;
	configMatch.IntOnMatch=ENABLE; // interruption
	configMatch.StopOnMatch=DISABLE; // 
	configMatch.ResetOnMatch=ENABLE;
	configMatch.ExtMatchOutputType=TIM_EXTMATCH_NOTHING;
	configMatch.MatchValue= 20;

	// Application de la config
	TIM_ConfigMatch(LPC_TIM0, &configMatch);
	return;
}

//===========================================================//
// TIMER Initialization
//===========================================================//
void init_timers() {
	
	// INIT TIMER 0
	init_timer();
	
	// enabling TIMER0 interruption
	NVIC_EnableIRQ(TIMER0_IRQn);	
	
}	
	
void start_init() {
	
	//===========================================================//
	// LCD Initialization
	//===========================================================//
	lcd_Initializtion();	// call to ili_lcd_general.c line 324
	//touch_init();	// call to touch_init.c line 66
	
	
	//===========================================================//
	// Pin configuration for buttons and I2C0
	//===========================================================//
	pin_Configuration();
	
	
	//===========================================================//
	// I2C0 configuration
	//===========================================================//
	init_i2c_eeprom();

	//===========================================================//
	// Timers configuration
	//===========================================================//
	init_timers();
}