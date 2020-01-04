/*
 * uart_driver.h
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#pragma once
#include <stdbool.h>
#include <stdlib.h>

void initSerialLogger(void);
void startTransmission(void);
bool isTransmissionOngoing(void);

void enqueue_char(char _char);
void enqueue_string(const char* _string);
void logData(const char* _line);
void logValue(const char* _line, int _value);
void logString(const char* _line, const char* _string);
void testSend(char* _line);

