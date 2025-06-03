#include "args.h"

parameters parse_args(int argc, char **argv) {
  parameters params = EMPTY_PARAMS;

  params.width = 1920;
  params.height = 1080;
  params.file_path = "output.bmp";

  // TODO

  return params;
}