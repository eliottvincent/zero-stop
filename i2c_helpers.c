#include "i2c_helpers.h"

void i2c_eeprom_write(uint16_t addr, uint8_t data[64], int length, int mode) {
	
	// initializing the configuration
	I2C_M_SETUP_Type transferConfig;

	//=======================================================================//
	// Intermediate address creation: slave id + page number + operation
	//=======================================================================//
	// applying a mask to extract the 3 bits (the page number)...
	// ...and shiffting 8 to move the 
	// 0x700 represents the value of the mask : 0000111000000000
	uint8_t firstThreeBits = (addr & 0x0700) >> 8;
	
	uint8_t finalAddr = 0x50 + firstThreeBits;
	
	//=======================================================================//
	// Insertion of word address into buffer
	//=======================================================================//
	// 0xff represents the value of the mask: 0000 0000 1111 1111 (8 last bits)
	uint8_t word_address = (addr & 0x00ff);
	data[0] = word_address;

	
	transferConfig.sl_addr7bit = finalAddr;	// slave address in 7-bit mode
	transferConfig.tx_data = data;	// transmit data value
	transferConfig.tx_length = length + 1;	// transmit data length
	transferConfig.rx_data = NULL;	// read data value
	transferConfig.rx_length = 0;	// read data length
	transferConfig.retransmissions_max = 2;	// max re-transmission value
	
	if (mode == 0){
		I2C_MasterTransferData(LPC_I2C0, &transferConfig, I2C_TRANSFER_POLLING);
	}else{
		
		complete = 0;
		I2C_MasterTransferData(LPC_I2C0, &transferConfig, I2C_TRANSFER_INTERRUPT);
		
		// Check if MasterTransferData is completed within a delay of 1s, if not change state to MEMORY ERROR
		// Couldn't figure out how to write while(complete == 0) out of the function ?! Memory error if condition out of this function...
		
		wait_memory_counter = 100;
		wait_memory_flag = 1;
			do {
				if (memory_error_flag == 1){
					memory_error_flag = 0;
					previous_state = MEMORY_ERROR;
					current_state = MEMORY_ERROR;
					complete = 1;
				}
			}	while(complete == 0);
			
				wait_memory_flag = 0;
			
			if (previous_state == GAME_END_WRITE){
				current_state = GAME_END_READ;
			}else if (previous_state == GAME_END_READ){
				current_state = GAME_END;
			}
			
	}
}

void i2c_eeprom_read(uint16_t addr, uint8_t data[64], int length, int mode) {

	// initializing the configuration
	I2C_M_SETUP_Type transferConfig;

	//=======================================================================//
	// Intermediate address creation: slave id + page number + operation
	//=======================================================================//
	// applying a mask to extract the 3 bits (the page number)...
	// ...and shiffting 8 to move the 
	// 0x700 represents the value of the mask : 0000111000000000
	uint8_t firstThreeBits = (addr & 0x0700) >> 8;
	
	uint8_t finalAddr = 0x50 + firstThreeBits;
	
	//=======================================================================//
	// Insertion of word address into buffer
	//=======================================================================//
	// 0xff represents the value of the mask: 0000 0000 1111 1111 (8 last bits)
	uint8_t word_address = (addr & 0x00ff);
	data[0] = word_address;

	transferConfig.sl_addr7bit = finalAddr;	// slave address in 7-bit mode
	transferConfig.tx_data = data;	// transmit data value
	transferConfig.tx_length = 1;	// transmit data length
	transferConfig.rx_data = data;	// read data value
	transferConfig.rx_length = length + 1;	// read data length
	transferConfig.retransmissions_max = 2;	// max re-transmission value
	
	if (mode == 0) {
		I2C_MasterTransferData(LPC_I2C0, &transferConfig, I2C_TRANSFER_POLLING);
	}
	
	else {		
		complete = 0;
		I2C_MasterTransferData(LPC_I2C0, &transferConfig, I2C_TRANSFER_INTERRUPT);
			
			// Check if MasterTransferData is completed within a delay of 1s, if not change state to MEMORY ERROR
			// Couldn't figure out how to write while(complete == 0) out of the function ?! Memory error if condition out of this function...
			wait_memory_counter = 100;
			wait_memory_flag = 1;
			do {
				if (memory_error_flag == 1){
					memory_error_flag = 0;
					previous_state = MEMORY_ERROR;
					current_state = MEMORY_ERROR;
					complete = 1;
				}
			}	while(complete == 0);
			
			wait_memory_flag = 0;
			
			if (previous_state == GAME_END_WRITE){
				current_state = GAME_END_READ;
			}else if (previous_state == GAME_END_READ){
				current_state = GAME_END;
			}
	}
}