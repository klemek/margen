#include "args.h"
#include "bmp.h"
#include <string.h>

#define WIDTH 256
#define HEIGHT 256
#define COLOR_DEPTH 3

void generate_line(unsigned long y, char *data_buffer) {
  memset(data_buffer, y, WIDTH * COLOR_DEPTH);
}

void generate(parameters params) {
  // TODO
  bmp_generate(WIDTH, HEIGHT, COLOR_DEPTH, "test.bmp", generate_line);
}