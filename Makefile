TARGET ?= margen
INSTALL_DIR ?= $(HOME)/.local/bin
TEST_ARGS ?= -w=100
SHELL := /bin/bash

.PHONY: build
clean:
	@rm -rf build

build:
	@mkdir -p build
	gcc -Wall src/*.c src/*.h -lm -o build/$(TARGET)

.PHONY: install
install: build
	cp -f build/$(TARGET) $(INSTALL_DIR)/$(TARGET)

.PHONY: time
time: build
	time ./build/$(TARGET) $(TEST_ARGS)

.PHONY: valgrind
valgrind: build
	valgrind --leak-check=full -s ./build/$(TARGET) $(TEST_ARGS)