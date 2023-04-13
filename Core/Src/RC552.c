/*
 * RC552.c
 *
 *  Created on: Apr 12, 2023
 *      Author: Jay Patel
 */

#include "RC522.h"
#include "main.h"

extern hspi1;

uint8_t RC522_SPI_read(uint8_t addr, uint8_t* data)
{
	uint8_t txBuf[2] = {{addr | 0x80}, 0x00}; /* Sec. 8.1.2.3
											   * XXXX_XXXX
											   * 1XXX_XXXX OR
											   * ----------
											   * 1XXX_XXXX
											   */
	uint8_t rxBuf[2];

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	uint8_t status = (HAL_SPI_TransmitReceive(hspi1, txBuf, rxBuf, 2, HAL_MAX_DELAY)) == HAL_OK;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET); // after done reading we are going to pull the SS high

	*data = rxBuf[1];
	return status;
}

uint8_t RC522_SPI_write(uint8_t addr, uint8_t data)
{
	uint8_t txBuf[2] = {addr, data};

	uint8_t status = (HAL_SPI_Transmit(hspi1, txBuf, 2, HAL_MAX_DELAY)) == HAL_OK;
	return status;



}





