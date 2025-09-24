#include "main.h"
#include "args.h"
#include "generator.h"
#include "types.h"

int main(int argc, char **argv) {
  Parameters params;
  params = args_parse(argc, argv);
  generator_run(params);
  return 0;
}