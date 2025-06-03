#include <stdio.h>
#include <string.h>

#ifndef ARGS_H
#define ARGS_H

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

parameters parse_args(int argc, char **argv);

#endif