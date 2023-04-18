/*
 * RC552.c
 *
 *  Created on: Apr 12, 2023
 *      Author: Jay Patel
 */

#include "RC522.h"
#include "main.h"

extern hspi1;

uint8_t RC522_SPI_read_transmit_recieve(uint8_t addr, uint8_t* data)
{
	uint8_t rx_bits;
	uint8_t read_addr = ((addr << 1) & 0x7E) | 0x80; //8.1.2.3 Table 8
	uint8_t status;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET); 	 // Bring NSS Low to begin transaction.

	status = (HAL_SPI_TransmitReceive(&hspi1, &read_addr, &rx_bits, 1, HAL_MAX_DELAY)) ==  HAL_OK; // Size param is set in initialization
																   	   	   	   	   	   	   	       // in this case its : hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
																   	   	   	   	   	   	   	   	   // 1 is refering to 1 byte
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);       // Bring NSS High to end transaction.

	data = rx_bits;

	return status;

}

uint8_t RC522_SPI_write(uint8_t addr, uint8_t write_val)
{
	uint8_t write_addr = ((addr << 1) & 0x7E);

	uint8_t status;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET); 	 		 // Bring NSS Low to begin transaction.

	status = (HAL_SPI_Transmit(&hspi1, &write_addr, 1, HAL_MAX_DELAY)) == HAL_OK;// Size param is set in initialization
	   	   	       	   	   	   	   	   	   	   	   	   	   						 // in this case its : hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	   	   	   	   	   	   	   	   	   	   	   	   	   	    				     // 1 is refering to 1 byte
	status &= (HAL_SPI_Transmit(&hspi1, &write_val, 1, HAL_MAX_DELAY)) == HAL_OK;

	// 8.1.2.2, first bit read in is don't care as it sends a bit config to read data, reading starts at byte 1


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);		 // Bring NSS High to end transaction.

	return status;

}

void RC522_SPI_init(void)
{
	RC522_SPI_write(0x26, 0x00);
}











