AUTOMAKE_OPTIONS = foreign subdir-objects -Wall
bin_PROGRAMS = margen
margen_SOURCES = src/main.c src/args.c src/bmp.c src/generator.c src/rand.c
margen_CFLAGS = -Ofast -march=native -flto -funroll-loops -fprefetch-loop-arrays -fno-exceptions -fopenmp
include_HEADERS = src/main.h src/args.h src/bmp.h src/generator.h src/rand.h src/config.h src/types.h