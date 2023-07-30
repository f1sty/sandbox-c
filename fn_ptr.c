#include <stdio.h>

int (*fun)(const char *restrict format, ...);

int main(int argc, char *argv[]) {
  fun = printf;

  fun("test%d\n", 23);
  return 0;
}
