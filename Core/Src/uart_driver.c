/*
 * uart_driver.c
 *
 *  Created on: Dec 23, 2019
 *      Author: janus
 */

#include "uart_driver.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

static UART_HandleTypeDef UartHandle[UART_COUNT];
static uart_driver_callback uart_driver_clb[UART_COUNT] = {NULL, NULL};
static uint8_t uart_rx_buffer[UART_COUNT];

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* TXE handler */
    char c;
}


void uart_driver_init(enum uart_device device, enum uart_baudrate baud, bool handshake)
{
    static const uint32_t baud_table[BAUD_COUNT] = {115200, 115200};

    if(device >= UART_COUNT || baud >= BAUD_COUNT){
        assert(false); //remove from production code
        return;
    }
    memset(&UartHandle[device], 0, sizeof(UART_HandleTypeDef));

    if(device == UART_DEBUG) {
        GPIO_InitTypeDef  GPIO_InitStruct;
        memset(&GPIO_InitStruct, 0, sizeof(GPIO_InitStruct));

        UartHandle[device].Instance = USART2;

        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        PA0     ------> USART2_CTS
        PA1     ------> USART2_RTS
         */
        if (handshake == true) {
       /*     GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
            GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);*/
        }

        /**USART2 GPIO Configuration
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }

       UartHandle[device].Init.BaudRate   = baud_table[baud];
       UartHandle[device].Init.WordLength = UART_WORDLENGTH_8B;
       UartHandle[device].Init.StopBits   = UART_STOPBITS_1;
       UartHandle[device].Init.Parity     = UART_PARITY_NONE;
       UartHandle[device].Init.Mode       = UART_MODE_TX_RX;
       UartHandle[device].Init.HwFlowCtl  = handshake == true ? UART_HWCONTROL_RTS_CTS : UART_HWCONTROL_NONE;
       UartHandle[device].Init.OverSampling = UART_OVERSAMPLING_16;

       if(HAL_UART_Init(&UartHandle[device]) != HAL_OK) {
           assert(false);
           return;
       }

       HAL_UART_Receive_IT(&UartHandle[device], &uart_rx_buffer[device], 1);

       if(device == UART_DEBUG) {
    	   HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
		   HAL_NVIC_EnableIRQ(USART2_IRQn);
       }

}

void uart_driver_deinit(enum uart_device device)
{

}


void send(enum uart_device device, const char* data, uint16_t size)
{
	HAL_UART_Transmit_IT(&UartHandle[device], data, size);
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&UartHandle[UART_DEBUG] );
}

