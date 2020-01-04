/*
 * uart_driver.c
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */
#include "uart_driver.h"
#include "stm32f4xx_hal.h"
#include "FifoBuffer.h"

UART_HandleTypeDef uartHandle;

#define TX_FIFO_BUFFER_SIZE  256

#define USART_PORT USART2
#define USART_IRQ USART2_IRQn

static FifoBufferObj txFifo;
static char txFifoBuffer[TX_FIFO_BUFFER_SIZE];
static bool transmissionOngoing;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* TXE handler */
    char c;
    if(huart == &uartHandle) {
        if( Fifo_getNumberOfElements( &txFifo ) > 0 ) {
            if( Fifo_pop( &txFifo, &c ) ) {
                HAL_UART_Transmit_IT(&uartHandle, (uint8_t*)(&c), 1);
                transmissionOngoing = 1;
            }
        } else {
            transmissionOngoing = 0;
        }
    }
}

void initSerialLogger(void) {
	__HAL_RCC_USART2_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**USART2 GPIO Configuration
	 PA2     ------> USART2_TX
	 PA3     ------> USART2_RX
	 */
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);

	uartHandle.Instance = USART2;
	uartHandle.Init.BaudRate = 115200;
	uartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	uartHandle.Init.StopBits = UART_STOPBITS_1;
	uartHandle.Init.Parity = UART_PARITY_NONE;
	uartHandle.Init.Mode = UART_MODE_TX_RX;
	uartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	uartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&uartHandle) != HAL_OK) {
		Error_Handler();
	}

	transmissionOngoing = false;
	Fifo_initialize(&txFifo, txFifoBuffer, TX_FIFO_BUFFER_SIZE);
}
void startTransmission(void) {
	char c;
	if (transmissionOngoing)
		return;
	if (Fifo_getNumberOfElements(&txFifo) > 0) {
		Fifo_pop(&txFifo, &c);
		HAL_UART_Transmit_IT(&uartHandle, (uint8_t *)(&c), 1);
		transmissionOngoing = 1;
	}
}
bool isTransmissionOngoing(void) {
	return transmissionOngoing;
}

void enqueue_char(char _char) {
	Fifo_push(&txFifo, _char);
}
void enqueue_string(const char *_string) {
	Fifo_push_string(&txFifo, _string);
}
void logData(const char *_line) {
	Fifo_push_string(&txFifo, _line);
	Fifo_push(&txFifo, '\r');
	Fifo_push(&txFifo, '\n');
	startTransmission();
}
void logValue(const char *_line, int _value) {
	Fifo_push_string(&txFifo, _line);
	Fifo_push(&txFifo, ':');
	Fifo_push(&txFifo, ' ');
	char valueStr[20];
	itoa(_value, valueStr, 10);
	Fifo_push_string(&txFifo, valueStr);
	Fifo_push(&txFifo, '\r');
	Fifo_push(&txFifo, '\n');
	startTransmission();
}
void logString(const char *_line, const char *_string) {
	Fifo_push_string(&txFifo, _line);
	Fifo_push(&txFifo, ':');
	Fifo_push(&txFifo, ' ');
	Fifo_push_string(&txFifo, _string);
	Fifo_push(&txFifo, '\r');
	Fifo_push(&txFifo, '\n');
	startTransmission();
}

void USART2_IRQHandler(void)
{
  HAL_UART_IRQHandler(&uartHandle);
}

