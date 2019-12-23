/*
 * uart_driver.h
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#pragma once
#include "stm32f4xx.h"
#include <stdbool.h>

void uart_driver_init(enum uart_device device, enum uart_baudrate baud, bool handshake);
void send(UART_HandleTypeDef* uartHandle, const char* data, uint16_t size);


