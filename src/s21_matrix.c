#include "s21_matrix.h"

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

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix)
        free(A->matrix[i]);
    }
    if (A->matrix)
      free(A->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = 1;
  if (s21_valid(A) && s21_valid(B) && s21_compare_matrix(A, B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >
            EPS * fabs(B->matrix[i][j]))
          result = 0;
      }
    }
  } else {
    result = 0;
  }
  return result;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = 0;
  s21_create_matrix(A->rows, A->columns, result);
  if (s21_valid(A) && s21_valid(B)) {
    if (s21_compare_matrix(A, B)) {
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
  s21_create_matrix(A->rows, A->columns, result);
  if (s21_valid(A) && s21_valid(B)) {
    if (s21_compare_matrix(A, B)) {
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
  s21_create_matrix(A->rows, A->columns, result);
  if (s21_valid(A)) {
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
  s21_create_matrix(A->rows, B->columns, result);
  if (s21_valid(A) && s21_valid(B)) {
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

        double tmp_result;
        s21_determinant(&matrix_cut, &tmp_result);
        *result += A->matrix[i][0] * pow(-1, i) * tmp_result;
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

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int exit_code = 0;
  s21_create_matrix(A->rows, A->columns, result);

  double determinant;
  s21_determinant(A, &determinant);
  if (fabs(determinant) > EPS) {
    matrix_t minor;
    s21_create_matrix(A->rows, A->columns, &minor);
    s21_calc_complements(A, &minor);

    matrix_t transpose_minor;
    s21_create_matrix(A->rows, A->columns, &transpose_minor);
    s21_transpose(&minor, &transpose_minor);

    s21_mult_number(&transpose_minor, 1 / determinant, result);

    s21_remove_matrix(&minor);
    s21_remove_matrix(&transpose_minor);

    s21_inf_to_zero(result);
  } else {
    exit_code = 1;
  }
  return exit_code;
}

void s21_inf_to_zero(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (1 / A->matrix[i][j] == -INFINITY) {
        A->matrix[i][j] = 0;
      }
    }
  }
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

void s21_fill_in(matrix_t *M, double fill_number) {
  for (int i = 0; i < M->rows; i++) {
    for (int j = 0; j < M->columns; j++) {
      M->matrix[i][j] = fill_number;
    }
  }
}

void s21_get_matrix_cut(matrix_t *A, matrix_t *matrix_cut, int columns_cut,
                        int rows_cut) {
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