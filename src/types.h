#include <stdbool.h>

#ifndef TYPES_H
#define TYPES_H

typedef struct Parameters {
  bool quiet;
  bool monochrome;
  unsigned long seed;
  unsigned int width;
  unsigned int height;
  char *file_path;
  unsigned int size;
  unsigned int slope;
  unsigned int start[3];
  unsigned int var[3];
  unsigned int rotation;
} Parameters;

typedef void line_fn(unsigned int y, unsigned char *data_buffer,
                     unsigned int len);

#endif