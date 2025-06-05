AUTOMAKE_OPTIONS = foreign subdir-objects -Wall
bin_PROGRAMS = margen
margen_SOURCES = src/main.c src/args.c src/bmp.c src/generator.c src/rand.c
nodist_margen_SOURCES = src/main.h src/args.h src/bmp.h src/const.h src/generator.h src/rand.h src/types.h
BUILT_SOURCES = src/main.h src/args.h src/bmp.h src/const.h src/generator.h src/rand.h src/types.h
CLEANFILES = src/main.h src/args.h src/bmp.h src/const.h src/generator.h src/rand.h src/types.h
margen_LDFLAGS = -lm