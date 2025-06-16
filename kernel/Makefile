#
# Build Variables
#
BUILD_DIR = ../bin/kernel
OBJ_DIR = $(BUILD_DIR)/obj

#
# Compiler/Linker Setup
#
CC = gcc
CFLAGS = -O2 -I ../limine -I include -I ../libc/include
LDFLAGS =

override CFLAGS += \
	-Wall \
	-Wextra \
	-ffreestanding \
	-fno-stack-protector \
	-nostdlib \
	-m64 \
	-mno-sse \
	-mno-sse2 \
	-mno-mmx \
	-mno-red-zone \
	-mno-80387 \
	-fno-PIC \
	-mcmodel=kernel \
	-march=x86-64

override LDFLAGS += \
	-Wl,-m,elf_x86_64 \
	-Wl,--build-id=none \
	-nostdlib \
	-static \
	-z max-page-size=0x1000 \
	-T linker.ld

# Paths
LIBC = ../bin/libc/libc.a

# Sources & Objects
SRCS := $(shell find . -name '*.c')
OBJS := $(patsubst ./%.c, $(OBJ_DIR)/%.o, $(SRCS))

KERNEL_BIN = $(BUILD_DIR)/kernel

#
# Build Rules
#
all: $(KERNEL_BIN)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BIN): $(OBJS) $(LIBC)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBC)

.PHONY: all