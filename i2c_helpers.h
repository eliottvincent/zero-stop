#ifndef HEADER_FILE
#define HEADER_FILE

#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_i2c.h"
#include "global_import.h"

void i2c_eeprom_write(uint16_t addr, uint8_t data[64], int length, int mode);
void i2c_eeprom_read(uint16_t addr, uint8_t data[64], int length, int mode);

#endif