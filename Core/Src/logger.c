/*
 * logger.c
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#include "logger.h"

static uint8_t uartRx[10] = {0};
static int cnt_idx = 0;

static void logger_uart_callback(uint8_t data){
	uartRx[cnt_idx] = data;

	if(data == '\n'){
		int i =0;
	}
	 else{
		 cnt_idx++;
	 }
}

void logger_init(void){
	uart_driver_init(UART_DEBUG, BAUD_115200, false);
	uart_driver_register_callback(UART_DEBUG, logger_uart_callback);
}

void logger_send(enum logger_level level, const char* data)
{
	size_t len = strlen(data);

    if(len >= LOGGER_MAX_MESSAGE_SIZE)
        len = LOGGER_MAX_MESSAGE_SIZE;

    if(len == 0)
    {
        return;
    }

        uart_driver_send(UART_DEBUG, (uint8_t*)data, len);
}
