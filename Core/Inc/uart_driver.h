/*
 * uart_driver.h
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#pragma once
#include "stm32f4xx_hal.h"
#include <stdbool.h>

enum uart_baudrate {
    BAUD_9600,
    BAUD_115200,
    BAUD_COUNT
};

enum uart_device {
    UART_DEBUG,
    UART_BLE,
    UART_COUNT
};

typedef void (*uart_driver_callback)(uint8_t data);

void uart_driver_init(enum uart_device device, enum uart_baudrate baud, bool handshake);
void uart_driver_deinit(enum uart_device device);
void send(enum uart_device device, const char* data, uint16_t size);

void uart_driver_send(enum uart_device device, uint8_t data[], uint16_t len);
void uart_driver_send_string(enum uart_device device, const char* data);
void uart_driver_register_callback(enum uart_device device, uart_driver_callback callback);

