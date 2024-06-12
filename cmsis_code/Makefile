# Compiler parameters
CC=arm-none-eabi-gcc

# Add --specs=rdimon.specs for semi-hosting
CFLAGS=-mcpu=cortex-m4 -mthumb --specs=nano.specs -u _printf_float 
CPPFLAGS=-DSTM32F401xE \
	 -Ivendor/CMSIS/Device/ST/STM32F4/Include \
	 -Ivendor/CMSIS/CMSIS/Core/Include \
	 -Iinclude

LINKER_FILE=linker_script.ld
LDFLAGS=-T $(LINKER_FILE) 
LDFLAGS2=-lm

# Flasher parameters
PROGRAMMER=openocd
PROGRAMMER_FLAGS=-f interface/stlink.cfg -f target/stm32f4x.cfg

# Source files
SRCDIRS := . include vendor/CMSIS/Device/ST/STM32F4/Source/Templates
SRCS := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c, %.o, $(notdir $(SRCS)))


# Output directory
OUTPUT_DIR := .

VPATH := $(SRCDIRS)

# Compiling sequence
all: blink.elf clean

# Compilation rule
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

blink.elf: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $^ -o blink.elf  $(LDFLAGS2)



# Flash sequence

flash: blink.elf
	$(PROGRAMMER) $(PROGRAMMER_FLAGS) -c "program blink.elf verify reset exit"

# Clean operation
.PHONY: clean
clean:
	rm -f *.o 

