#include "args.h"
#include "generator.h"
#include "types.h"

int main(int argc, char **argv) {
  Parameters params;
  params = parse_args(argc, argv);
  generate(params);
  return 0;
}