#include "interrupts.h"

void I2C0_IRQHandler(void){
	I2C_MasterHandler(LPC_I2C0);
	if (I2C_MasterTransferComplete(LPC_I2C0)){
		complete = 1;
	}
}

void TIMER0_IRQHandler(void) {
	
		switch(current_state) {

		// game is already launched
		case GAME_LAUNCHED:

			counter_actual_value --;
			
			//KEY 1 scrutation: when the player pushes KEY1
			if (((GPIO_ReadValue((uint8_t) 2)>> 11) & 0x01) == 0 && buttonPressedKey1 == 0) {
				buttonPressedKey1 = 1;
				game_end_flag = 1;
			} 
			
			//KEY 1 scrutation: when KEY1 isn't pushed
			else if (((GPIO_ReadValue((uint8_t) 2)>> 11) & 0x01) == 1 && buttonPressedKey1 == 1) {
				buttonPressedKey1 = 0;
			}
			break;

			// game is still not launched
			case MENU:

				//KEY 2 scrutation: when the player pushes KEY2
				if (((GPIO_ReadValue((uint8_t) 2)>> 10) & 0x01) == 0 && buttonPressedKey2 == 0) {
					buttonPressedKey2 = 1;
					game_begin_flag = 1;
				}
				
				//KEY 2 scrutation: when KEY2 isn't pushed
				else if (((GPIO_ReadValue((uint8_t) 2)>> 10) & 0x01) == 1 && buttonPressedKey2 == 1) {
					buttonPressedKey2 = 0;
				}
				break;
		}
		
				
			if (wait_memory_flag == 1){
					wait_memory_counter --;
			
					if (wait_memory_counter == 0){
						memory_error_flag = 1;
					}
			}
		
		TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}