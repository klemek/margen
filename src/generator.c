#include "args.h"
#include "bmp.h"
#include "rand.h"
#include <math.h>
#include <stdio.h>

#define COLOR_DEPTH 3

parameters global_params;
float global_fslope;

void generate_line(unsigned short y, unsigned char *data_buffer,
                   unsigned int len) {
  unsigned int i;
  for (i = 0; i < len; i++) {
    data_buffer[i] = rand_uchar(256);
  }
}

unsigned char pixel_gen(unsigned char depth, unsigned char top_pixel,
                        unsigned char left_pixel) {
  float v = fminf(
      255.0, fmaxf(0.0, (rand_float(2.0) - 1.0) * global_params.var[depth] +
                            ((float)left_pixel) * global_fslope +
                            ((float)top_pixel) * (1.0 - global_fslope)));
  return (unsigned char)v;
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
  global_fslope = ((float)params.slope) / 255.0;
  debug_parameters(params);
  set_seed(params.seed);
  bmp_generate(params.width, params.height, COLOR_DEPTH, params.file_path,
               generate_line);
  return 0;
}