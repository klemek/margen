#include "args.h"
#include "const.h"
#include "rand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_help(int status_code) {
  puts(NAME
       " " VERSION "\n\n"
       "usage: " NAME " "
       "[--help] "
       "[-v] "
       "[-q] "
       "[-w=WIDTH] "
       "[-h=HEIGHT] "
       "[-o=PATH] "
       "[--seed=SEED]"
       "[-p=PIXEL_SIZE] "
       "[-s=SLOPE] "
       "[-c=R,G,B] "
       "[--var=R,G,B] "
       "[-m]\n\n"
       "generate a marble-like pattern bitmap image, blazing fast.\n\n"
       "options:\n"
       "  --help             show this help message and exit\n"
       "  -q, --quiet        do not print to console\n"
       "  -w, --width        image width (default: 1920)\n"
       "  -h, --height       image height (default: 1080)\n"
       "  -o, --output       output file (default: output.bmp)\n"
       "  -seed              random seed (default: time based)\n"
       "  -p, --pixel        pixel size (default: random)\n"
       "  -s, --slope        slope [0-255] (default: random)\n"
       "  -c, --color        base color [0-255,0-255,0-255] (default: random)\n"
       "  -v, --variation    base variation [0-255,0-255,0-255] (default: "
       "random)\n"
       "  -m, --monochrome   black & white generation");
  exit(status_code);
}

void invalid_arg(char *arg) {
  fprintf(stderr, "invalid argument: '%s'\n\n", arg);
  print_help(1);
}

void invalid_value(char *arg, char *value) {
  fprintf(stderr, "invalid value for argument '%s': '%s'\n\n", arg, value);
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
  return true;
}

unsigned char parse_char(char *arg, char *value) {
  if (!is_number(value)) {
    invalid_value(arg, value);
  }
  unsigned long long tmp_value = (unsigned long long)atoll(value);
  if (tmp_value >= 256) {
    invalid_value(arg, value);
  }
  return (unsigned char)tmp_value;
}

unsigned short parse_ushort(char *arg, char *value) {
  if (!is_number(value)) {
    invalid_value(arg, value);
  }
  unsigned long long tmp_value = (unsigned long long)atoll(value);
  if (tmp_value >= 65536) {
    invalid_value(arg, value);
  }
  return (unsigned short)tmp_value;
}

unsigned short parse_ulong(char *arg, char *value) {
  if (!is_number(value)) {
    invalid_value(arg, value);
  }
  return (unsigned long)atoll(value);
}

void parse_color(char *arg, char *value, unsigned char color[3]) {
  char *tmp;
  tmp = strtok(value, ",");
  color[0] = parse_char(arg, tmp);
  tmp = strtok(NULL, ",");
  color[1] = parse_char(arg, tmp);
  tmp = strtok(NULL, ",");
  color[2] = parse_char(arg, tmp);
}

parameters parse_args(int argc, char **argv) {
  parameters params;

  params.quiet = false;
  params.seed = (unsigned long)time(NULL);
  params.width = 0;
  params.height = 0;
  params.file_path = "output.bmp";
  params.monochrome = false;

  bool size_set = false;
  bool slope_set = false;
  bool start_set = false;
  bool var_set = false;

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
    } else if (is_arg(arg, "-v") || is_arg(arg, "--version")) {
      puts(NAME " " VERSION);
      exit(0);
    } else if (is_arg(arg, "-w") || is_arg(arg, "--width")) {
      params.width = parse_ushort(arg, value);
      if (params.width == 0) {
        invalid_value(arg, value);
      }
      if (params.height == 0) {
        params.height = params.width;
      }
    } else if (is_arg(arg, "-h") || is_arg(arg, "--height")) {
      params.height = parse_ushort(arg, value);
      if (params.height == 0) {
        invalid_value(arg, value);
      }
      if (params.width == 0) {
        params.width = params.height;
      }
    } else if (is_arg(arg, "--seed")) {
      params.seed = parse_ulong(arg, value);
    } else if (is_arg(arg, "-o") || is_arg(arg, "--output")) {
      params.file_path = value;
    } else if (is_arg(arg, "-p") || is_arg(arg, "--pixel")) {
      params.size = parse_ushort(arg, value);
      if (params.size == 0) {
        invalid_value(arg, value);
      }
      size_set = true;
    } else if (is_arg(arg, "-s") || is_arg(arg, "--slope")) {
      params.slope = parse_char(arg, value);
      slope_set = true;
    } else if (is_arg(arg, "-c") || is_arg(arg, "--color")) {
      parse_color(arg, value, params.start);
      start_set = true;
    } else if (is_arg(arg, "-v") || is_arg(arg, "--variation")) {
      parse_color(arg, value, params.var);
      var_set = true;
    } else if (is_arg(arg, "-m") || is_arg(arg, "--monochrome")) {
      params.monochrome = true;
    } else {
      invalid_arg(arg);
    }
  }

  if (params.width == 0 && params.height == 0) {
    params.width = 1920;
    params.height = 1080;
  }

  set_seed(params.seed);

  if (!size_set) {
    params.size = rand_ushort(10) + 3;
  }

  if (!slope_set) {
    params.slope = rand_uchar(50) + 100;
  }

  if (!start_set) {
    params.start[0] = rand_uchar(256);
    params.start[1] = rand_uchar(256);
    params.start[2] = rand_uchar(256);
  }

  if (!var_set) {
    params.var[0] = rand_uchar(20);
    params.var[1] = rand_uchar(20);
    params.var[2] = rand_uchar(20);
  }

  return params;
}