#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// core function
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);

// support function
int s21_valid(matrix_t *M);
int s21_compare_matrix(matrix_t *A, matrix_t *B);
void s21_print_matrix(matrix_t M);
void s21_random_matrix(matrix_t *M);
int s21_matrix_is_square(matrix_t *M);
void s21_get_matrix_cut(matrix_t *A, matrix_t *matrix_cut, int rows_cut, int columns_cut);
#endif