#include "args.h"

const parameters EMPTY_PARAMS = {
    0, 0, NULL, 0, 0.0, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}};

parameters parse_args(int argc, char **argv) {
  parameters params;

  params.width = 1920;
  params.height = 1080;
  params.file_path = "output.bmp";

  // TODO

  return params;
}