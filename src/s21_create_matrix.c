#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int exit_code = 0;
  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(rows * sizeof(double *));
  for (int i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = 0;
    }
  }
  return exit_code;
}
