#include "args.h"
#include "bmp.h"
#include <stdio.h>

#define COLOR_DEPTH 3

parameters global_params;

void generate_line(unsigned short y, unsigned char *data_buffer,
                   unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++) {
    data_buffer[i] = global_params.start[i % 3];
  }
}

void debug_parameters(parameters params) {
  if (!params.quiet) {
    printf("output  %s\n", params.file_path);
    printf("seed    %ld\n", params.seed);
    printf("width   %d\n", params.width);
    printf("height  %d\n", params.height);
    printf("pixel   %d\n", params.size);
    printf("color   %u,%u,%u\n", params.start[0], params.start[1],
           params.start[2]);
    printf("var.    %u,%u,%u\n", params.var[0], params.var[1], params.var[2]);
  }
}

int generate(parameters params) {
  global_params = params;
  debug_parameters(params);
  bmp_generate(params.width, params.height, COLOR_DEPTH, params.file_path,
               generate_line);
  return 0;
}