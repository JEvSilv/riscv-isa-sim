CC=riscv64-unknown-elf-gcc
BUILD_DIR = bin
SRC_DIR = srcs
SOURCES = $(shell find $(SRC_DIR)/ -name "*.c")
TARGET  = program
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.rv)

default: $(OBJECTS)

.SECONDEXPANSION:

$(OBJECTS): $$(patsubst $(BUILD_DIR)/%.rv,$(SRC_DIR)/%.c,$$@)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) $<

clean:
	rm $(BUILD_DIR)/*
.PHONY: default

