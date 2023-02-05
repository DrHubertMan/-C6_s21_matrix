#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int exit_code = INCORRECT_MATRIX;
  if (rows > 0 && columns > 0) {
    exit_code = OK;
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(result->rows, sizeof(double *));
    if (result->matrix == NULL) {
      exit_code = INCORRECT_MATRIX;
    } else {
      int i = 0;
      while (i < result->rows) {
        result->matrix[i] = calloc(result->columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          exit_code = INCORRECT_MATRIX;
          free(result->matrix[i]);
          break;
        }
        i++;
      }
    }
  }
  return exit_code;
}

int s21_valid_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return !(!A || !B || !result || !A->matrix || !B->matrix);
}

int s21_compare_matrix(matrix_t *A, matrix_t *B) {
  return ((A->columns != B->columns) || (A->rows != B->rows)) ? FAILURE
                                                              : SUCCESS;
}

void s21_remove_matrix(matrix_t *result) {
  if (result != NULL) {
    for (int i = 0; i < result->rows; i++) {
      free(result->matrix[i]);
    }
    free(result->matrix);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int exit_code = SUCCESS;
  if (A->columns != B->columns || A->rows != B->rows || !A || !B) {
    exit_code = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > S21_EPS) {
          exit_code = FAILURE;
        }
        if (exit_code == FAILURE) {
          break;
        }
      }
    }
  }
  return exit_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = OK;
  if (!s21_valid_matrix(A, B, result)) {
    exit_code = INCORRECT_MATRIX;
  } else {
    if (s21_compare_matrix(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    } else {
      exit_code = BAD_CALCULATE;
    }
  }
  return exit_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int exit_code = OK;
  if (!s21_valid_matrix(A, B, result)) {
    exit_code = INCORRECT_MATRIX;
  } else {
    if (s21_compare_matrix(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    } else {
      exit_code = BAD_CALCULATE;
    }
  }
  return exit_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OK;
  if (s21_create_matrix(A->rows, A->columns, result) == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (number == 0.0) {
          result->matrix[i][j] = 0;
        } else {
          result->matrix[i][j] = number * A->matrix[i][j];
        }
      }
    }
  } else {
    res = INCORRECT_MATRIX;
  }
  return res;
}

//  k                  N                N
// m *A[i][k]    *  K  *B[k][j]   =   M  *C[i][j]
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  if (A->columns == B->rows) {
    if (s21_create_matrix(A->rows, B->columns, result) == 0) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = 0;
          for (int c = 0; c < A->columns; c++) {
            result->matrix[i][j] += A->matrix[i][c] * B->matrix[c][j];
          }
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  } else {
    res = BAD_CALCULATE;
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int exit_code = OK;
  if (!s21_valid_matrix(A, A, result))
    exit_code = INCORRECT_MATRIX;
  else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[j][i];
  }
  return exit_code;
}

int s21_determinant(matrix_t *A, double *result) {
  int exit_code = OK;
  if (!(!A || !result || !A->matrix)) {
    if (A->columns == A->rows) {
      if (A->columns == 1) {
        *result = A->matrix[0][0];
      } else {
        int ignore_rows = 0;
        bool ignore_columns[64] = {0};
        *result = s21_determinant_recursive(*A, A->columns, ignore_rows,
                                            ignore_columns);
      }
    } else {
      exit_code = BAD_CALCULATE;
    }
  } else
    exit_code = INCORRECT_MATRIX;
  return exit_code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int exit_code = OK;
  if (s21_valid_matrix(A, A, result)) {
    if (A->columns == A->rows) {
      exit_code = s21_create_matrix(A->columns, A->rows, result);  // 4
      if (exit_code == OK) {
        if (A->columns == 1) {
          result->matrix[0][0] = A->matrix[0][0];
        } else if (A->columns == 2) {
          result->matrix[0][0] = A->matrix[1][1];
          result->matrix[0][1] = -A->matrix[1][0];
          result->matrix[1][0] = -A->matrix[0][1];
          result->matrix[1][1] = A->matrix[0][0];
        } else {
          for (int i = 0; i < A->columns; i++) {
            for (int j = 0; j < A->columns; j++) {
              result->matrix[i][j] =
                  pow(-1.0, i + j) * s21_det_of_minor(A, i, j);
            }
          }
        }
      }
    } else {
      exit_code = BAD_CALCULATE;
    }
  } else
    exit_code = INCORRECT_MATRIX;
  return exit_code;
}

double s21_det_of_minor(matrix_t *A, int i_, int j_) {
  double result = 0;
  matrix_t B;
  if (!(s21_create_matrix(A->columns - 1, A->columns - 1, &B))) {
    for (int i = 0; i < A->columns; i++) {
      short im = i;
      if (im > i_) im--;
      for (int j = 0; j < A->columns; j++) {
        short jm = j;
        if (jm > j_) jm--;
        if (i != i_ && j != j_) B.matrix[im][jm] = A->matrix[i][j];
      }
    }
    s21_determinant(&B, &result);
    s21_remove_matrix(&B);
  }
  return result;
}

double s21_determinant_recursive(matrix_t A, int n, int ignore_rows,
                                 bool *ignore_columns) {
  double exit_code = 0;
  if (n == 2) {
    double B[2][2] = {0};
    for (int i = ignore_rows, i_ = 0; i < A.columns; i++) {
      for (int j = 0, j_ = 0; j < A.columns; j++) {
        if (ignore_columns[j] == 0) {
          B[i_][j_] = A.matrix[i][j];
          j_++;
        }
      }
      i_++;
    }
    exit_code = B[0][0] * B[1][1] - B[0][1] * B[1][0];
  } else if (n > 2) {
    int sign = 0;
    n--;
    for (int i = ignore_rows; i < A.columns; i++) {
      ignore_rows += 1;
      for (int j = 0; j < A.columns; j++) {
        if (ignore_columns[j] == 0) {
          ignore_columns[j] = 1;
          double exit_code_ =
              pow(-1.0, sign) * A.matrix[i][j] *
              s21_determinant_recursive(A, n, ignore_rows, ignore_columns);
          exit_code += exit_code_;
          ignore_columns[j] = 0;
          sign++;
        }
      }
      break;
    }
  }
  return exit_code;
}

/*Алгоритм нахождения обратной матрицы
Определяют, квадратная ли матрица. Если нет, то обратной матрицы для нее не
существует. Вычисление определителя матрицы A. Если он не равен нулю,
продолжаем решение, иначе - обратной матрицы не существует. Нахождение
транспонированной матрицы AT. Определение алгебраических дополнений. Заменяют
каждый элемент матрицы его алгебраическим дополнением. Составление обратной
матрицы из алгебраических дополнений: каждый элемент полученной матрицы делят
на определитель исходной матрицы. Результирующая матрица является обратной
для исходной матрицы. Делают проверку: перемножают исходную и полученную
матрицы. В результате должна получиться единичная матрица.*/

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int exit_code = OK;
  double det = 0;
  if (s21_valid_matrix(A, A, result)) {
    if (s21_determinant(A, &det) == 0) {
      if (det != 0) {
        if (A->columns == 1) {
          exit_code = s21_create_matrix(1, 1, result);
          result->matrix[0][0] = 1.0 / A->matrix[0][0];
        } else {
          matrix_t alg, mult;
          exit_code = s21_calc_complements(A, &alg);
          exit_code = s21_transpose(&alg, &mult);
          exit_code = s21_mult_number(&mult, 1.0 / det, result);
          s21_remove_matrix(&alg);
          s21_remove_matrix(&mult);
        }
      } else {
        exit_code = BAD_CALCULATE;
      }
    } else {
      exit_code = BAD_CALCULATE;
    }
  } else {
    exit_code = INCORRECT_MATRIX;
  }
  return exit_code;
}
