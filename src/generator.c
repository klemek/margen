#include "args.h"
#include "bmp.h"
#include <string.h>

#define COLOR_DEPTH 3

parameters global_params = EMPTY_PARAMS;

void generate_line(unsigned long y, char *data_buffer) {
  memset(data_buffer, y, global_params.width * COLOR_DEPTH);
}

void generate(parameters params) {
  global_params = params;
  bmp_generate(params.width, params.height, COLOR_DEPTH, params.file_path,
               generate_line);
}