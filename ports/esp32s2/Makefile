# Makefile for MicroPython on ESP32S2.
#
# This is a simple, convenience wrapper around idf.py (which uses cmake).

# Select the board to build for, defaulting to GENERIC.
BOARD ?= GENERIC

# If the build directory is not given, make it reflect the board name.
BUILD ?= build-$(BOARD)

# Device serial settings.
BAUD ?= 460800
PORT ?= /dev/ttyUSB0

PYTHON ?= python3

.PHONY: all clean flash erase

IDFPY_FLAGS +=  -B $(BUILD) -D MICROPY_BOARD=$(BOARD) -D IDF_TARGET=esp32s2

all:
	idf.py $(IDFPY_FLAGS) build
	@$(PYTHON) makeimg.py \
		$(BUILD)/bootloader/bootloader.bin \
		$(BUILD)/partition_table/partition-table.bin \
    	$(BUILD)/micropython.bin \
    	$(BUILD)/firmware.bin

clean:
	idf.py $(IDFPY_FLAGS) fullclean

erase:
	idf.py $(IDFPY_FLAGS) -p $(PORT) erase_flash

flash:
	idf.py $(IDFPY_FLAGS) -p $(PORT) -b $(BAUD) flash
