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
#define GENRANDID  0x02



uint8_t RC522_SPI_read_transmit_recieve(uint8_t addr, uint8_t* data);
uint8_t RC522_SPI_write(uint8_t addr, uint8_t write);
void RC522_SPI_init(void);


#endif /* INC_RC522_H_ */
