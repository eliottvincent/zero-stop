#include "init_program.h"
#include "i2c_helpers.h"
#include "interrupts.h"
#include "screen_helpers.h"

#include "global.h"

#define COUNTER_INITIAL_VALUE 1000;
#define WAIT_MEMORY_COUNTER_INITIAL_VALUE 100;

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	
	
	//===========================================================//
	// Start initialization
	//===========================================================//
	current_state = MENU;
	start_init();
	
	// Timer launch
	TIM_Cmd(LPC_TIM0, ENABLE);
	
	display_home();
	
	while(1) {
		
		switch (current_state) {
			case MENU :
				if (game_begin_flag == 1){
					game_begin_flag = 0;
					current_state = GAME_BEGIN;
				}
			break;
			
			case GAME_BEGIN:

				counter_actual_value = COUNTER_INITIAL_VALUE;	// counter reset
				current_state = GAME_LAUNCHED;
				break;
			
			case GAME_LAUNCHED :
				if (game_end_flag == 1){
					game_end_flag = 0;
					current_state = GAME_END_WRITE;
				}
				
				if (counter_actual_value == 0){
					current_state = GAME_LOST;
				}else if (counter_actual_value  < 500 && counter_actual_value != 0) {
					LCD_write_english_string(0x0000, 0xD0, "A vous de jouer !         ", 0xFFFF, 0xF81F);
				}else if (counter_actual_value > 500) {
					sprintf(str, "Temps restant : %d            ", counter_actual_value / 10);
					LCD_write_english_string(0x0000, 0xD0, str, 0xFFFF, 0xF81F);
				}
			break;

			case GAME_END_WRITE:
				data_write[1] = counter_actual_value / 10;
				previous_state = GAME_END_WRITE;
			
				// WRITE
				// the length is set at 1 because we use only the first 2 cells of our data[] array
				i2c_eeprom_write(0x0011, data_write, 1, 1);

			break;
			
			case GAME_END_READ:
				// READ
				previous_state = GAME_END_READ;
				i2c_eeprom_read(0x0011, data_read, 1, 1);
			break;
			
			case GAME_END :
				// SCREEN
				sprintf(str, "Votre dernier score : %d      ", data_read[0]);
				
				LCD_write_english_string(0x0000, 0x00D0, str, 0xFFFF, 0xF81F);

				current_state = MENU;
				break;
			
			case GAME_LOST:
				LCD_write_english_string(0x0000, 0x00D0, "             Perdu!           ", 0xFFFF, 0xF81F);
				current_state = MENU;
				break;
			
			case MEMORY_ERROR :
				LCD_write_english_string(0x0000, 0x00D0, "Memoire inaccessible :(           ", 0xFFFF, 0xF81F);
				current_state = MENU;
				break;
		}
		
	}	

}




//---------------------------------------------------------------------------------------------	
//---------------------------------------------------------------------------------------------	
//---------------------------------------------------------------------------------------------	
//---------------------------------------------------------------------------------------------	
//---------------------------------------------------------------------------------------------	
//---------------------------------------------------------------------------------------------	
//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
