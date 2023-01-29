#include "s21_matrix.h"

int main() {
  matrix_t test_one, test_result;
  s21_create_matrix(3, 3, &test_one);
  s21_random_matrix(&test_one);
  double determinant;
  s21_determinant(&test_one, &determinant);
  s21_print_matrix(test_one);
  printf("%.2f\n", determinant);
  s21_remove_matrix(&test_one);
  return 0;
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
      for (int j = 0; j < A->columns; j++) {
        if (A->matrix[i][j] - B->matrix[i][j] > EPS)
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

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = 0;
  if (s21_valid(A) && s21_valid(B)) {
    if (s21_compare_matrix(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
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

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int exit_code = 0;
  if (s21_valid(A)) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  } else {
    exit_code = 1;
  }
  return exit_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = 0;
  if (s21_valid(A) && s21_valid(B)) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double mul = 0;
        for (int k = 0; k < A->columns; k++) {
          mul += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = mul;
      }
    }
  } else {
    exit_code = 1;
  }
  return exit_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int exit_code = 0;
  s21_create_matrix(A->columns, A->rows, result);
  if (s21_valid(A)) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else {
    exit_code = 1;
  }
  return exit_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int exit_code = 0;
  if (s21_valid(A) && s21_matrix_is_square(A)) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else if (A->rows > 2) {
      for (int i = 0; i < A->rows; i++) {
        matrix_t matrix_cut;
        s21_get_matrix_cut(A, &matrix_cut, i, 0);
        *result +=
            A->matrix[i][0] * pow(-1, i) * s21_determinant(&matrix_cut, result);
        s21_remove_matrix(&matrix_cut);
      }
    }
  } else {
    exit_code = 1;
  }
  return exit_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int exit_code = 0;
  s21_create_matrix(A->rows, A->columns, result);
  if (s21_valid(A) && s21_matrix_is_square(A)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t matrix_cut;
        s21_get_matrix_cut(A, &matrix_cut, i, j);
        
        double determinant;
        s21_determinant(&matrix_cut, &determinant);

        result->matrix[i][j] = pow(-1, i + j) * determinant;
        s21_remove_matrix(&matrix_cut);
      }
    }
  } else {
    exit_code = 1;
  }
  return exit_code;
}

void s21_print_matrix(matrix_t M) {
  for (int i = 0; i < M.rows; i++) {
    for (int j = 0; j < M.columns; j++) {
      printf("%4.f ", M.matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

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

void s21_random_matrix(matrix_t *M) {
  int free_value = 0;
  for (int i = 0; i < M->rows; i++) {
    for (int j = 0; j < M->columns; j++) {
      M->matrix[i][j] = free_value;
      free_value += 1;
    }
  }
}

void s21_get_matrix_cut(matrix_t *A, matrix_t *matrix_cut, int rows_cut,
                        int columns_cut) {
  s21_create_matrix(A->rows - 1, A->columns - 1, matrix_cut);
  for (int i = 0, a = 0; i < A->rows; i++) {
    if (i != columns_cut) {
      for (int j = 0, b = 0; j < A->columns; j++) {
        if (j != rows_cut) {
          matrix_cut->matrix[a][b] = A->matrix[i][j];
          b++;
        }
      }
      a++;
    }
  }
}

int s21_matrix_is_square(matrix_t *M) {
  int exit_code = 0;
  if (M->rows == M->columns)
    exit_code = 1;
  return exit_code;
}