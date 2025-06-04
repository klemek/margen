TARGET ?= margen
INSTALL_DIR ?= $(HOME)/.local/bin
TEST_ARGS ?=
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

.PHONY: release
release: clean build time
	@echo -n "Version (x.y.z): "
	@read VERSION; \
		sed -i "s/#define VERSION.*/#define VERSION \"v$$VERSION\"/g" ./src/const.h; \
		git add ./src/const.h; \
		git diff origin/master; \
		git commit -m "$(TARGET) v$$VERSION"; \
		git tag v$$VERSION -m "$(TARGET) v$$VERSION"
	@echo updated ./src/const.h and tagged version
