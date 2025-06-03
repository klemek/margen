#ifndef TYPES_H
#define TYPES_H

struct Parameters {
  unsigned long width;
  unsigned long height;
  char *file_path;
  unsigned int size;
  float slope;
  float start[3];
  float var[3];
};

typedef struct Parameters parameters;

typedef void line_fn(unsigned long y, char *data_buffer);

#endif