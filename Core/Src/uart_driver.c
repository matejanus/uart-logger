/*
 * uart_driver.c
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#include "uart_driver.h"

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* TXE handler */
    char c;
}


void send(UART_HandleTypeDef* uartHandle, const char* data, uint16_t size)
{
	HAL_UART_Transmit_IT(uartHandle, data, size);
}
