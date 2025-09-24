#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "args.h"
#include "bmp.h"
#include "config.h"
#include "rand.h"

#define BMP_COLOR_DEPTH 3

static Parameters global_params;
static float slope;
static unsigned char color_depth;
static unsigned int line_width;
static unsigned char *last_line;
static unsigned char *current_line;

static unsigned char generate_pixel(unsigned char depth,
                                    unsigned char top_pixel,
                                    unsigned char left_pixel) {
  int k = rand_uint(global_params.var[depth] + 1);
  int v = (rand_uint(2) == 0 ? k : -k) + (left_pixel)*slope +
          (top_pixel) * (1.0 - slope);
  return (unsigned char)(v < 0 ? 0 : (v > 255 ? (unsigned char)255 : v));
}

static void generate_line() {
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

static void generate_bmp_line(unsigned int y, unsigned char *data_buffer,
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

static void debug_parameters(Parameters params) {
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

static void init(Parameters params) {
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
  rand_seed(params.seed);
}

static void clean() {
  free(last_line);
  free(current_line);
}

static void print_time(Parameters params, clock_t start) {
  if (!params.quiet) {
    clock_t now = clock();
    printf("time: %.3fs\n", (float)(now - start) / CLOCKS_PER_SEC);
  }
}

void generator_run(Parameters params) {
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