/* main.c
 * Copyright (C) 2019 Subhendu Biswas <sbodd05@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/***************************************************************************
	Platform    : STM32F103C8T6 (cortex M3)
	Description : usart2 (using STM32F10x_StdPeriph_Lib_V3.5.0 library)
	Pin Desc    : PA2(TX),PA3(RX)
****************************************************************************/

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t xTaskHandle1=NULL;
TaskHandle_t xTaskHandle2=NULL;

/* The task functions prototype*/
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);
static void prvSetupHardware(void);
static void prvSetupUart(void);

void uartPutchar(unsigned char);
void printMsg(char *);

int main(void)
{
	/* Use internal RC oscillator clock */
	RCC_DeInit();
	SystemCoreClockUpdate();

	prvSetupHardware();

	printMsg("This is hello world app starting\n");
    
    /* Create one of the two tasks. */
    BaseType_t xReturn = pdPASS;
    xReturn = xTaskCreate(vTask1, "Task-1", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandle1);
    if (pdPASS == xReturn)
        printMsg("successful to create task-1\n");
    else
        printMsg("failed to create task-1\n");
    
    /* Create second task */
    xReturn = xTaskCreate(vTask2, "Task-2", configMINIMAL_STACK_SIZE, NULL, 2, &xTaskHandle2);
    if (pdPASS == xReturn)
        printMsg("successful to create task-2\n");
    else
        printMsg("failed to create task-2\n");

    /* Start the scheduler */
    vTaskStartScheduler();

    for( ;; ) ;	
}

void vTask1(void *pvParameters)
{
        /* As per most tasks, this task is implemented in an infinite loop. */
        for( ;; )
        {
		printMsg("This is Task-1\n");
		vTaskDelay(500);
        }
}
/*-----------------------------------------------------------*/

void vTask2(void *pvParameters)
{
        /* As per most tasks, this task is implemented in an infinite loop. */
        for( ;; )
        {
		printMsg("This is Task-2\n");
		vTaskDelay(200);
        }
}

static void prvSetupHardware(void)
{
        // setup uart2
        prvSetupUart();
}

void prvSetupUart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	USART_InitTypeDef USART_InitStructure;


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	// UART2 TX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	// UART2 RX
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init (USART2,&USART_InitStructure);
	USART_Cmd (USART2,ENABLE);		
}

void uartPutchar(unsigned char ch)
{	
	USART2->DR = (ch & 0x01ff);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == 0);
}

void printMsg(char *ptr)
{
        while(*ptr!='\0')
        {
                uartPutchar(*ptr);
                *ptr++;
        }
}

#ifdef USE_FULL_ASSERT
void assert_failed ( uint8_t * file , uint32_t line)
{
/* Infinite loop */
/* Use GDB to find out why we're here */
while (1);
}
#endif
