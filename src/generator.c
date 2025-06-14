#include "args.h"
#include "bmp.h"
#include "config.h"
#include "rand.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BMP_COLOR_DEPTH 3

parameters global_params;
float slope;
unsigned char color_depth;
unsigned int line_width;
unsigned char *last_line;
unsigned char *current_line;

unsigned char generate_pixel(unsigned char depth, unsigned char top_pixel,
                             unsigned char left_pixel) {
  short k = rand_uchar(global_params.var[depth] + 1);
  short v = (rand_uchar(2) == 0 ? k : -k) + (left_pixel)*slope +
            (top_pixel) * (1.0 - slope);
  return (unsigned char)(v < 0 ? 0 : (v > 255 ? (unsigned char)255 : v));
}

void generate_line() {
  unsigned int i;
  for (i = 0; i < line_width; i++) {
    last_line[i] = current_line[i];
  }
  for (i = 0; i < line_width; i++) {
    if (i < color_depth) {
      current_line[i] = generate_pixel(i % color_depth, last_line[i],
                                       global_params.start[i % color_depth]);
    } else {
      current_line[i] = generate_pixel(i % color_depth, last_line[i],
                                       current_line[i - color_depth]);
    }
  }
}

void generate_bmp_line(unsigned short y, unsigned char *data_buffer,
                       unsigned int len) {
  unsigned int i;
  unsigned int x;
  if (y % global_params.size == 0) {
    generate_line();
  }
  for (i = 0; i < len; i++) {
    x = i / (BMP_COLOR_DEPTH * global_params.size);
    data_buffer[(global_params.rotation / 2) == 1 ? i : (len - i - 1)] =
        current_line[x * color_depth + (i % color_depth)];
  }
}

void debug_parameters(parameters params) {
  if (!params.quiet) {
    printf("  output  %s\n", params.file_path);
    printf("  seed    %ld\n", params.seed);
    printf("  width   %d\n", params.width);
    printf("  height  %d\n", params.height);
    printf("  pixel   %d\n", params.size);
    printf("  slope   %d\n", params.slope);
    if (params.monochrome) {
      printf("  color   %u\n", params.start[0]);
      printf("  var.    %u\n", params.var[0]);
    } else {
      printf("  color   %u,%u,%u\n", params.start[0], params.start[1],
             params.start[2]);
      printf("  var.    %u,%u,%u\n", params.var[0], params.var[1],
             params.var[2]);
    }
    printf("  rot.    %d\n", params.rotation);
  }
}

void init(parameters params) {
  global_params = params;
  slope = ((float)params.slope) / 255.0;
  color_depth = params.monochrome ? 1 : 3;
  debug_parameters(params);
  line_width = ((params.width / params.size) + 1) * color_depth;
  last_line = (unsigned char *)malloc(line_width);
  current_line = (unsigned char *)malloc(line_width);
  unsigned int i = 0;
  for (i = 0; i < line_width; i++) {
    current_line[i] = params.start[i % color_depth];
  }
  set_seed(params.seed);
}

void clean() {
  free(last_line);
  free(current_line);
}

void print_time(parameters params, clock_t start) {
  if (!params.quiet) {
    clock_t now = clock();
    printf("time: %.3fs\n", (float)(now - start) / CLOCKS_PER_SEC);
  }
}

void generate(parameters params) {
  if (!params.quiet) {
    puts(PACKAGE " " VERSION);
  }
  clock_t start = clock();
  init(params);
  bmp_generate(params.width, params.height, BMP_COLOR_DEPTH,
               params.rotation % 2 == 1, params.file_path, generate_bmp_line);
  clean();
  print_time(params, start);
}