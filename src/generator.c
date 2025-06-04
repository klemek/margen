#include "args.h"
#include "bmp.h"
#include "rand.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define COLOR_DEPTH 3

parameters global_params;
float global_fslope;
unsigned int line_width;
unsigned char *last_line;
unsigned char *current_line;

unsigned char generate_pixel(unsigned char depth, unsigned char top_pixel,
                             unsigned char left_pixel) {
  float v = fminf(
      255.0, fmaxf(0.0, (rand_float(2.0) - 1.0) * global_params.var[depth] +
                            ((float)left_pixel) * global_fslope +
                            ((float)top_pixel) * (1.0 - global_fslope)));
  return (unsigned char)v;
}

void generate_line() {
  unsigned int i;
  for (i = 0; i < line_width; i++) {
    last_line[i] = current_line[i];
  }
  for (i = 0; i < line_width; i++) {
    if (i < COLOR_DEPTH) {
      current_line[i] = generate_pixel(i % COLOR_DEPTH, last_line[i],
                                       global_params.start[i % COLOR_DEPTH]);
    } else {
      current_line[i] = generate_pixel(i % COLOR_DEPTH, last_line[i],
                                       current_line[i - COLOR_DEPTH]);
    }
  }
}

void generate_bmp_line(unsigned short y, unsigned char *data_buffer,
                       unsigned int len) {
  unsigned int i;
  unsigned int x;
  for (i = 0; i < len; i++) {
    if (y > 0 && y % global_params.size == 0) {
      generate_line();
    }
    x = i / (COLOR_DEPTH * global_params.size);
    data_buffer[i] = current_line[x * COLOR_DEPTH + (i % COLOR_DEPTH)];
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

void init(parameters params) {
  global_params = params;
  global_fslope = ((float)params.slope) / 255.0;
  debug_parameters(params);
  line_width = ((params.width / params.size) + 1) * COLOR_DEPTH;
  last_line = (unsigned char *)malloc(line_width);
  current_line = (unsigned char *)malloc(line_width);
  unsigned int i = 0;
  for (i = 0; i < line_width; i++) {
    current_line[i] = params.start[i % COLOR_DEPTH];
  }
  set_seed(params.seed);
  generate_line();
}

void clean() {
  free(last_line);
  free(current_line);
}

void generate(parameters params) {
  init(params);
  bmp_generate(params.width, params.height, COLOR_DEPTH, params.file_path,
               generate_bmp_line);
  clean();
}