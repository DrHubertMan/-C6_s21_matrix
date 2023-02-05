#ifndef s21_MATRIX_H_
#define s21_MATRIX_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define INCORRECT_MATRIX 1
#define BAD_CALCULATE 2

#define SUCCESS 1
#define FAILURE 0

#define S21_EPS 1e-6

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// core function
int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_transpose(matrix_t *A, matrix_t *result);
void s21_minor_matrix(matrix_t *A, matrix_t *minor, int row, int column);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
void s21_remove_matrix(matrix_t *result);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// another function
int s21_valid_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_compare_matrix(matrix_t *A, matrix_t *B);
double s21_det_of_minor(matrix_t *A, int i_, int j_);
double s21_determinant_recursive(matrix_t A, int n, int ignore_rows,
                                 bool *ignore_columns);

#endif // s21_MATRIX_H_