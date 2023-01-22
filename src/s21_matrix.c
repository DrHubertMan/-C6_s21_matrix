#include "s21_matrix.h"

int s21_valid(matrix_t *M) {
  int result = 0;
  if ((M != NULL) && (M->matrix != NULL) && (M->rows > 0) && (M->columns > 0))
    result = 1;
  return result;
}

int s21_compare_matrix(matrix_t *A, matrix_t *B) {
  int result = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    result = 1;
  }
  return result;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    if (A->matrix)
      free(A->matrix[i]);
  }
  if (A->matrix)
    free(A->matrix);
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) { 
    int result = 1;
    if (s21_valid(A) && s21_valid(B) && s21_compare_matrix(A, B)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; A->columns; j++) {
                if(A->matrix[i][j] - B->matrix[i][j] > EPS)
                result = 0;
            }
        }
    } else {
        result = 0;
    }
    return result;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int exit_code = 0;
  result->rows = rows;
  result->columns = columns;
  if (rows > 0 && columns > 0) {
    result->matrix = (double **)calloc(rows, sizeof(double *));
    for (int i = 0; i < result->rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = i;
      }
    }
  } else { 
      exit_code = 1;
  }
  return exit_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = 0;
  if (s21_valid(A) && s21_valid(B)) {
    if (s21_compare_matrix(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      exit_code = 2;
    }
  } else {
    exit_code = 1;
  }
  return exit_code;
}

int main() {
  matrix_t test;
  s21_create_matrix(4, 3, &test);
  // for (int i = 0; i < test.rows; i++) {
  //   for (int j = 0; j < test.columns; j++) {
  //     printf("%f ", test.matrix[i][j]);
  //   }
  //   printf("\n");
  // }
  s21_remove_matrix(&test);
  return 0;
}
