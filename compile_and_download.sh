#!/bin/sh


# arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -I ./include -o stm32f10x_usart.o stm32f10x_usart.c
arm-none-eabi-gcc -c -mthumb -mcpu=cortex-m3 -DSTM32F10X_MD -I include -I include/FreeRTOS -o main.o main.c
arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 --specs=nosys.specs -T ./ld/stm32_flash.ld -o out.elf ./lib/startup_stm32f10x_md.o ./lib/system_stm32f10x.o ./lib/stm32f10x_gpio.o ./lib/stm32f10x_rcc.o ./lib/stm32f10x_usart.o ./lib/FreeRTOS/tasks.o ./lib/FreeRTOS/queue.o ./lib/FreeRTOS/list.o ./lib/FreeRTOS/port.o ./lib/FreeRTOS/heap_4.o ./lib/FreeRTOS/timers.o main.o
arm-none-eabi-objcopy out.elf -O ihex out.hex
sudo stm32flash -b 115200 -w out.hex -v -g 0x0 /dev/ttyACM0
