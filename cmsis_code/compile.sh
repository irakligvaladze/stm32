arm-none-eabi-gcc main.c startup.c vendor/CMSIS/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c -T linker_script.ld -o blink.elf -Ivendor/CMSIS/CMSIS/Core/Include -Ivendor/CMSIS/Device/ST/STM32F4/Include -mcpu=cortex-m4 -mthumb -nostdlib -DSTM32F401xE