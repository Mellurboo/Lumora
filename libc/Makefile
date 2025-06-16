# libc/Makefile

SRC_DIR := .
BUILD_DIR := ../bin/libc
SRCS := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
LIBC := $(BUILD_DIR)/libc.a

CC := gcc
AR := ar
CFLAGS := -ffreestanding -O2 -Wall -Wextra -I kernel -I include

all: $(LIBC)

# Create object files, keeping directory structure
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Archive into libc.a
$(LIBC): $(OBJS)
	mkdir -p $(dir $@)
	$(AR) rcs $@ $^

.PHONY: all
