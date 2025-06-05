#include <stdbool.h>

#ifndef TYPES_H
#define TYPES_H

struct Parameters {
  bool quiet;
  bool monochrome;
  unsigned long seed;
  unsigned short width;
  unsigned short height;
  char *file_path;
  unsigned short size;
  unsigned char slope;
  unsigned char start[3];
  unsigned char var[3];
  unsigned char rotation;
};

typedef struct Parameters parameters;

typedef void line_fn(unsigned short y, unsigned char *data_buffer,
                     unsigned int len);

#endif