#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 10000000

int main(int argc, char *argv[]) {
  int i, count = 0;
  double x, y, z, pi;

  #pragma omp parallel for private(x, y, z) reduction(+:count) num_threads(NUM_THREADS)
  for (i = 0; i < NUM_ITERATIONS; i++) {
    x = (double)rand() / RAND_MAX;
    y = (double)rand() / RAND_MAX;
    z = x * x + y * y;
    if (z <= 1) {
      count++;
    }
  }

  pi = (double)count / NUM_ITERATIONS * 4;
  printf("Estimated value of pi: %f\n", pi);

  return 0;
}
