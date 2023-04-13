/*
 * RC522.h
 *
 *  Created on: Apr 12, 2023
 *      Author: Jay Patel
 */

#ifndef INC_RC522_H_
#define INC_RC522_H_

#include <stdint.h>

#define STATUS2REG 0x08
#define


uint8_t RC522_SPI_read(uint8_t addr);
uint8_t RC522_SPI_write(uint8_t addr, uint8_t data);



#endif /* INC_RC522_H_ */
