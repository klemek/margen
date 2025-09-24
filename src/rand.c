#include "rand.h"

static unsigned long long mcg_state = 0xcafef00dd15ea5e5u; // Must be odd
static unsigned long long const multiplier = 6364136223846793005u;

// https://en.wikipedia.org/wiki/Permuted_congruential_generator
static unsigned long rand(void) {
  unsigned long long x;
  unsigned count;

  x = mcg_state;
  count = (unsigned)(x >> 61);

  mcg_state = x * multiplier;
  x ^= x >> 22;

  return (unsigned long)(x >> (22 + count));
}

void rand_seed(unsigned long long seed) {
  mcg_state = 2 * seed + 1;
  (void)rand();
}

unsigned int rand_uint(unsigned int max) {
  return max == 0 ? 0 : (unsigned int)(rand() % max);
}
