BUILD_DIR = build
SOURCE_DIR = src
EXECUTABLE = giraffeOS.bin
ISO = giraffeOS.iso
CC = i686-elf-gcc
LD = i686-elf-gcc
AS = i686-elf-as
LFLAGS = -ffreestanding -O2 -nostdlib -Wall -Wextra
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
INCLUDES = -I include
LIBS = -lgcc

.PHONY: clean all
ASMSOURCES = $(wildcard $(SOURCE_DIR)/*.s)
CSOURCES = $(wildcard $(SOURCE_DIR)/*.c)

# Ugly hack, I have no idea how to do this "properly", pull requests welcome!
# Basically generates a list of all the object files to be made, changing names and paths
OBJECTS = $(patsubst $(SOURCE_DIR)%,$(BUILD_DIR)%, $(patsubst %.c,%.o, $(patsubst %.s,%.o, $(ASMSOURCES) $(CSOURCES))))


# ------------------------------------------------------------------------------
all: $(BUILD_DIR)/$(EXECUTABLE)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $^ -o $@

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.s
	$(AS) $(<) -o $(@)

$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS)
# I know, it actually refers to gcc, but seeing as it's used as the linker in this case,
# it seemed proper to call it LD for readability's sake.
	$(LD) -T $(SOURCE_DIR)/linker.ld -o $(BUILD_DIR)/$(EXECUTABLE) $(LFLAGS) $(^) $(LIBS)

clean:
	rm -fv $(BUILD_DIR)/*.o
	rm -fv $(BUILD_DIR)/$(EXECUTABLE)
