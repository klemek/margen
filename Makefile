TARGET=mg

.PHONY: build
clean:
	rm -rf build

build:
	mkdir -p build
	gcc -Wall src/*.c src/*.h -o build/$(TARGET)

.PHONY: leak-test
leak-test: clean build
	valgrind --leak-check=full -s ./build/$(TARGET)
