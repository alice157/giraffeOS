SHELL:=/bin/bash -O globstar # Too lazy to use find
BUILD_DIR = build
SOURCE_DIR = src
EXECUTABLE = giraffeOS.bin
ISO = giraffeOS.iso
CC = i686-elf-gcc
LD = i686-elf-gcc
AS = nasm
LFLAGS = -ffreestanding -O2 -nostdlib -Wall -Wextra
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
ASFLAGS = -felf32
INCLUDES = -I include
LIBS = -lgcc

.PHONY: clean all build-structure
ASMSOURCES = $(wildcard $(SOURCE_DIR)/**/*.s)
CSOURCES = $(wildcard $(SOURCE_DIR)/**/*.c)

# Ugly hack, I have no idea how to do this "properly", pull requests welcome!
# Basically generates a list of all the object files to be made, changing names and paths
OBJECTS = $(patsubst $(SOURCE_DIR)%,$(BUILD_DIR)%, $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(ASMSOURCES) $(CSOURCES))))


# ------------------------------------------------------------------------------
all: $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c build_structure
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.s build_structure
	$(AS) $(ASFLAGS) $(<) -o $(@)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
# I know, it actually refers to gcc, but seeing as it's used as the linker in this case,
# it seemed proper to call it LD for readability's sake.
	$(LD) -T $(SOURCE_DIR)/linker.ld -o $(BUILD_DIR)/$(EXECUTABLE) $(LFLAGS) $(^) $(LIBS)

build_structure:
	find $(SOURCE_DIR) -type d -links 2 -exec mkdir -p "$(BUILD_DIR)/{}" \;

clean:
	rm -rf $(BUILD_DIR)/*
