#include "args.h"
#include "generator.h"

int main(int argc, char **argv) {
  parameters params;
  params = parse_args(argc, argv);
  generate(params);
  return 0;
}