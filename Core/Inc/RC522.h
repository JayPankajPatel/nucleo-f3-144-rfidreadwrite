/*
 * RC522.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Jay Patel
 */

#ifndef INC_RC522_H_
#define INC_RC522_H_

#include "main.h"

#include <stdint.h>
#include "stm32f3xx_hal.h"

#ifdef DEBUG_LOG
	#include "usbd_cdc_if.h"
#endif /* DEBUG LOG */

#define STATUS2REG 0x08
#define GENRANDID  0x02


extern SPI_HandleTypeDef hspi1;



uint8_t RC522_SPI_read(uint8_t reg_addr, uint8_t* read_data);
uint8_t RC522_SPI_write(uint8_t reg_addr, uint8_t write_data);
void RC522_SPI_init(void);
void clear_bitmask(uint8_t reg_addr);
void set_bitmask();


#endif /* INC_RC522_H_ */
