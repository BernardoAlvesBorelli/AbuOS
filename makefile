AS = nasm
CC = gcc
LD = ld
EMU = qemu-system-i386

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

TARGET = $(BIN_DIR)/myos.bin
LINKER_SCRIPT = linker.ld

# Lista de objetos automática
OBJS = $(OBJ_DIR)/boot.o \
       $(OBJ_DIR)/kernel.o \
       $(OBJ_DIR)/video/video.o

# Flags (Adicionado -Isrc para o compilador achar o video.h facilmente)
ASFLAGS = -f elf32
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -Isrc
LDFLAGS = -m elf_i386 -T $(LINKER_SCRIPT)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)

# Regra para arquivos Assembly
$(OBJ_DIR)/boot.o: $(SRC_DIR)/boot.asm
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Regra genérica para arquivos C (incluindo subpastas)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(EMU) -kernel $(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all run clean