#include <stdbool.h>

#ifndef TYPES_H
#define TYPES_H

struct Parameters {
  bool quiet;
  unsigned long width;
  unsigned long height;
  char *file_path;
  unsigned char size;
  unsigned char slope;
  unsigned char start[3];
  unsigned char var[3];
};

typedef struct Parameters parameters;

typedef void line_fn(unsigned long y, char *data_buffer);

#endif