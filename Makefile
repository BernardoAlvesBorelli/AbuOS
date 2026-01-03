# Ferramentas
AS = nasm
CC = gcc
LD = ld
EMU = qemu-system-i386

# Pastas
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ISO_DIR = iso_root

# Arquivos
TARGET = $(BIN_DIR)/myos.bin
ISO_TARGET = $(BIN_DIR)/myos.iso
LINKER_SCRIPT = linker.ld

# Lista de objetos
OBJS = $(OBJ_DIR)/boot.o \
       $(OBJ_DIR)/kernel.o \
       $(OBJ_DIR)/video/video.o \
       $(OBJ_DIR)/libc/stdio.o \
       $(OBJ_DIR)/gdt.o \
	   $(OBJ_DIR)/idt.o \
	   $(OBJ_DIR)/keyboard.o \
	   $(OBJ_DIR)/timer.o

# Flags
CFLAGS = -m32 -ffreestanding -O2 -Wall -Wextra -I$(SRC_DIR)
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T $(LINKER_SCRIPT)

# Regra padrão
all: $(TARGET)

# Linkagem do Kernel
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(LD) $(LDFLAGS) -o $(TARGET) $(OBJS)
	@echo "Kernel e Libc vinculados com sucesso em $(TARGET)!"

# Criação da ISO bootável
iso: $(TARGET)
	@mkdir -p $(ISO_DIR)/boot/grub
	@cp $(TARGET) $(ISO_DIR)/boot/
	@echo 'set timeout=0' > $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'set default=0' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo 'menuentry "Meu Sistema Operacional" {' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    multiboot /boot/myos.bin' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '    boot' >> $(ISO_DIR)/boot/grub/grub.cfg
	@echo '}' >> $(ISO_DIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_TARGET) $(ISO_DIR)
	@echo "ISO criada com sucesso em $(ISO_TARGET)!"

# Regra genérica para arquivos C
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para o arquivo de boot (Assembly)
$(OBJ_DIR)/boot.o: $(SRC_DIR)/boot.asm
	@mkdir -p $(OBJ_DIR)
	$(AS) $(ASFLAGS) $< -o $@

# Rodar no QEMU usando o kernel direto (rápido para teste)
run: $(TARGET)
	$(EMU) -kernel $(TARGET)

# Rodar no QEMU usando a ISO (simula boot real com GRUB)
run-iso: iso
	$(EMU) -cdrom $(ISO_TARGET)

# Limpeza completa
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(ISO_DIR)

.PHONY: all run run-iso clean iso