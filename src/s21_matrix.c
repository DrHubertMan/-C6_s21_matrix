#include "s21_matrix.h"

int main() {
  matrix_t test;
  s21_create_matrix(3, 3, &test);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%f ", test.matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}
