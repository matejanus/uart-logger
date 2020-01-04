/*
 * logger.c
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#include "logger.h"

void logger_init(void){
	initSerialLogger();
}

void logger_send(const char* data)
{
	size_t len = strlen(data);

    if(len == 0)
    {
        return;
    }

    logData(data);
}
