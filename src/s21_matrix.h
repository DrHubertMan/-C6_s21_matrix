#ifndef S21_MATRIX_H
#define S21_MATRIX_H
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);


int s21_valid(matrix_t M);
int s21_compare_matrix(matrix_t *A, matrix_t *B);

#endif