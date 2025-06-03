.PHONY: build
clean:
	rm -rf build

build:
	mkdir -p build
	gcc -Wall src/*.c src/*.h -o build/mg