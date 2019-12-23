/*
 * logger.h
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "uart_driver.h"

#define LOGGER_MAX_MESSAGE_SIZE ((uint32_t) 100)

enum logger_level{
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
};

void logger_init(void);
void logger_send(enum logger_level level, const char* data);
