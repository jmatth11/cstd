#include "headers/magic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // ============================================================
  // Using AUTO_C for automatic string cleanup
  // ============================================================
  char *name AUTO_C = malloc(32);
  snprintf(name, 32, "Hello, Magic!");
  printf("Name: %s\n", name);
  printf("Name pointer before scope end: %p\n", (void *)name);

  // ============================================================
  // Using AUTO_I for automatic int pointer cleanup
  // ============================================================
  int *value AUTO_I = malloc(sizeof(int));
  *value = 42;
  printf("Value: %d\n", *value);
  printf("Value pointer before scope end: %p\n", (void *)value);

  // ============================================================
  // Using AUTO_D for automatic double pointer cleanup
  // ============================================================
  double *pi AUTO_D = malloc(sizeof(double));
  *pi = 3.14159;
  printf("Pi: %.5f\n", *pi);
  printf("Pi pointer before scope end: %p\n", (void *)pi);

  // ============================================================
  // Using AUTO_F for automatic float pointer cleanup
  // ============================================================
  float *fval AUTO_F = malloc(sizeof(float));
  *fval = 2.5f;
  printf("Float value: %.2f\n", *fval);
  printf("Float pointer before scope end: %p\n", (void *)fval);

  // ============================================================
  // Using AUTO_P for generic void pointer cleanup
  // ============================================================
  void *data AUTO_P = malloc(128);
  memset(data, 0, 128);
  printf("Data pointer before scope end: %p\n", data);

  // ============================================================
  // Pointers are automatically freed when they go out of scope
  // ============================================================
  printf("All pointers will be automatically freed\n");

  return 0;
}
