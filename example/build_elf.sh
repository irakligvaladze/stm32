arm-none-eabi-gcc startup.c main.c -T linker_script.ld -o blink.elf -mcpu=cortex-m4 -mthumb -nostdlib
