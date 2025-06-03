#include "args.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help(int status_code) {
  puts("usage: mg "
       "[--help] "
       "[-q] "
       "[-w=WIDTH] "
       "[-h=HEIGHT] "
       "[-o=PATH] "
       "[-p=PIXEL_SIZE] "
       "[-s=SLOPE] "
       "[-c=R,G,B] "
       "[-v=R,G,B]\n\n"
       "generates a marble-like pattern bitmap image.\n\n"
       "options:\n"
       "  --help             show this help message and exit\n"
       "  -q, --quiet        do not print to console\n"
       "  -w, --width        image width (default: 1920)\n"
       "  -h, --height       image height (default: 1080)\n"
       "  -o, --output       output file (default: output.bmp)\n"
       "  -p, --pixel        pixel size (default: random)\n"
       "  -s, --slope        slope [0-255] (default: random)\n"
       "  -c, --color        base color [0-255,0-255,0-255] (default: random)\n"
       "  -v, --variation    base variation [0-255,0-255,0-255] (default: "
       "random)");
  exit(status_code);
}

void invalid_arg(char *arg) {
  fprintf(stderr, "invalid argument: '%s'\n\n", arg);
  print_help(1);
}

void invalid_value(char *arg, char *subarg, char *value) {
  if (subarg == NULL) {
    fprintf(stderr, "invalid value for argument '%s': '%s'\n\n", arg, value);
  } else {
    fprintf(stderr, "invalid value for argument '%s' %s: '%s'\n\n", arg, subarg,
            value);
  }
  print_help(1);
}

bool is_arg(char *arg, char *ref) { return strcoll(arg, ref) == 0; }

char *split_arg_value(char *arg) {
  strtok(arg, "=");
  return strtok(NULL, "=");
}

bool is_digit(char c) { return c >= '0' && c <= '9'; }

bool is_number(char *value) {
  if (value == NULL) {
    return false;
  }
  unsigned long value_len = strlen(value);
  int i;
  for (i = 0; i < value_len; i++) {
    if (!is_digit(value[i])) {
      return false;
    }
  }
  return value;
}

long parse_number(char *arg, char *value) {
  if (!is_number(value)) {
    invalid_value(arg, NULL, value);
  }
  return atol(value);
}

void parse_color(char *arg, char *value, unsigned char color[3]) {
  char *tmp;
  tmp = strtok(value, ",");
  if (!is_number(tmp)) {
    invalid_value(arg, "(R)", tmp);
  }
  color[0] = (unsigned char)atoi(tmp);
  tmp = strtok(NULL, ",");
  if (!is_number(tmp)) {
    invalid_value(arg, "(G)", tmp);
  }
  color[1] = (unsigned char)atoi(tmp);
  tmp = strtok(NULL, ",");
  if (!is_number(tmp)) {
    invalid_value(arg, "(B)", tmp);
  }
  color[2] = (unsigned char)atoi(tmp);
}

parameters parse_args(int argc, char **argv) {
  parameters params;

  params.quiet = false;
  params.width = 1920;
  params.height = 1080;
  params.file_path = "output.bmp";
  params.size = 1;       // TODO random
  params.slope = 128;    // TODO random
  params.start[0] = 128; // TODO random
  params.start[1] = 128; // TODO random
  params.start[2] = 128; // TODO random
  params.var[0] = 20;    // TODO random
  params.var[1] = 20;    // TODO random
  params.var[2] = 20;    // TODO random

  int i;
  char *arg;
  char *value;
  for (i = 1; i < argc; i++) {
    arg = argv[i];
    value = split_arg_value(arg);
    if (is_arg(arg, "--help")) {
      print_help(0);
    } else if (is_arg(arg, "-q") || is_arg(arg, "--quiet")) {
      params.quiet = true;
    } else if (is_arg(arg, "-w") || is_arg(arg, "--width")) {
      params.width = (unsigned long)parse_number(arg, value);
    } else if (is_arg(arg, "-h") || is_arg(arg, "--height")) {
      params.height = (unsigned long)parse_number(arg, value);
    } else if (is_arg(arg, "-o") || is_arg(arg, "--output")) {
      params.file_path = value;
    } else if (is_arg(arg, "-p") || is_arg(arg, "--pixel")) {
      params.size = (unsigned char)parse_number(arg, value);
    } else if (is_arg(arg, "-s") || is_arg(arg, "--slope")) {
      params.size = (unsigned char)parse_number(arg, value);
    } else if (is_arg(arg, "-c") || is_arg(arg, "--color")) {
      parse_color(arg, value, params.start);
    } else if (is_arg(arg, "-v") || is_arg(arg, "--variation")) {
      parse_color(arg, value, params.start);
    } else {
      invalid_arg(arg);
    }
  }

  return params;
}