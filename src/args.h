#ifndef ARGS_H
#define ARGS_H

struct Parameters {
  unsigned long width;
  unsigned long height;
  char *file_path;
  unsigned char start[3];
  unsigned char slope[2];
  unsigned char var[3];
};

typedef struct Parameters parameters;

parameters parse_args(int argc, char **argv);

#endif