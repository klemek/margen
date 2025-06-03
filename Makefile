.PHONY: build
clean:
	rm -rf build

build:
	mkdir -p build && \
		cd build && \
		gcc -Wall -c ../src/*.c && \
		gcc -Wall -o mg *.o