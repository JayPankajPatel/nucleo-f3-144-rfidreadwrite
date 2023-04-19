/*
 * RC552.c
 *
 *  Created on: Apr 12, 2023
 *      Author: Jay Patel
 */

#include "RC522.h"
#include <strings.h>



uint8_t RC522_SPI_read(uint8_t reg_addr, uint8_t* read_data)
{
	uint8_t rx_bits;
	uint8_t read_addr = ((reg_addr << 1) & 0x7E) | 0x80; //8.1.2.3 Table 8
	uint8_t status;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET); 	 // Bring NSS Low to begin transaction.

	status = (HAL_SPI_TransmitReceive(&hspi1, &read_addr, &rx_bits, 1, HAL_MAX_DELAY)) ==  HAL_OK; // Size param is set in initialization
																   	   	   	   	   	   	   	       // in this case its : hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
																   	   	   	   	   	   	   	   	   // 1 is refering to 1 byte
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);       // Bring NSS High to end transaction.

	*read_data = rx_bits;

#ifdef DEBUG_LOG
	char* message;
	uint16_t size;
	if(status)
	{
		message = "Successful SPI Read Operation";
		size = strlen(message);
		VirCOMPrint((uint8_t*)message, size);
	}
	else
	{
		message = "Not Successful SPI Read Operation";
		size = strlen(message);
		VirCOMPrint((uint8_t*)message, size);
	}
#endif /* DEBUG_LOG */


	return status;

}

uint8_t RC522_SPI_write(uint8_t reg_addr, uint8_t write_data)
{
	uint8_t write_addr = ((reg_addr << 1) & 0x7E);

	uint8_t status;

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, RESET); 	 		 // Bring NSS Low to begin transaction.

	status = (HAL_SPI_Transmit(&hspi1, &write_addr, 1, HAL_MAX_DELAY)) == HAL_OK;// Size param is set in initialization
	   	   	       	   	   	   	   	   	   	   	   	   	   						 // in this case its : hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	   	   	   	   	   	   	   	   	   	   	   	   	   	    				     // 1 is refering to 1 byte
	status = (HAL_SPI_Transmit(&hspi1, &write_data, 1, HAL_MAX_DELAY)) == HAL_OK;

	// 8.1.2.2, first bit read in is don't care as it sends a bit config to read data, reading starts at byte 1


	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, SET);		 // Bring NSS High to end transaction.


#ifdef DEBUG_LOG
	char* message;
	uint16_t size;
	if(status)
	{
		message = "Successful SPI Write Operation\n";
		size = strlen(message);
		VirCOMPrint((uint8_t*)message, size);
	}
	else
	{
		message = "Not Successful SPI Write Operation\n";
		size = strlen(message);
		VirCOMPrint((uint8_t*)message, size);
	}
#endif /* DEBUG_LOG */

	return status;

}

void clear_bitmask(uint8_t reg_addr, uint8_t mask)
{
	RC522_SPI_write(reg_addr, write_data)
}
void set_bitmask(uint8_t reg_addr, uint8_t mask)
{

}

void RC522_SPI_init(void)
{
	RC522_SPI_write(0x26, 0x00);
}











