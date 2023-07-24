#!/bin/sh

arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include/FreeRTOS -o ./lib/FreeRTOS/heap_4.o ./src/FreeRTOS/heap_4.c
arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include/FreeRTOS -o ./lib/FreeRTOS/list.o ./src/FreeRTOS/list.c
arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include/FreeRTOS -o ./lib/FreeRTOS/queue.o ./src/FreeRTOS/queue.c
arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include/FreeRTOS -o ./lib/FreeRTOS/timers.o ./src/FreeRTOS/timers.c
arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include/FreeRTOS -o ./lib/FreeRTOS/port.o ./src/FreeRTOS/port.c
arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include/FreeRTOS -o ./lib/FreeRTOS/tasks.o ./src/FreeRTOS/tasks.c
