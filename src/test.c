#include "s21_matrix.h"
#include <check.h>

START_TEST(s21_create_matrix_test_1) {
  matrix_t A;
  int create = s21_create_matrix(-10, 10, &A);
  ck_assert_uint_eq(create, 1);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  matrix_t A;
  int create = s21_create_matrix(10, 10, &A);
  ck_assert_uint_eq(create, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_eq_matrix_test_1) {
  matrix_t A, B;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  s21_fill_in(&A, 5);
  s21_fill_in(&B, 5);
  int equal = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(equal, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
  matrix_t A, B;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(5, 10, &B);
  s21_fill_in(&A, 5);
  s21_fill_in(&B, 5);
  int equal = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(equal, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
  matrix_t A, B;
  s21_create_matrix(10, 10, &A);
  s21_create_matrix(10, 10, &B);
  s21_fill_in(&A, 5);
  s21_fill_in(&B, 4);
  int equal = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(equal, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
  matrix_t A, B;
  s21_create_matrix(15, 10, &A);
  s21_create_matrix(15, 10, &B);
  s21_fill_in(&A, 5);
  s21_fill_in(&B, 5);
  int equal = s21_eq_matrix(&A, &B);
  ck_assert_uint_eq(equal, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

void part1_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_create_matrix_test_1);
  tcase_add_test(tc1_1, s21_create_matrix_test_2);
  tcase_add_test(tc1_1, s21_eq_matrix_test_1);
  tcase_add_test(tc1_1, s21_eq_matrix_test_2);
  tcase_add_test(tc1_1, s21_eq_matrix_test_3);
  tcase_add_test(tc1_1, s21_eq_matrix_test_4);
}

START_TEST(s21_sum_matrix_test_1) {
  matrix_t A, B, result, compare;
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_create_matrix(5, 5, &compare);
  s21_fill_in(&A, 3);
  s21_fill_in(&B, 4);
  s21_fill_in(&compare, 7);
  int sum_code = s21_sum_matrix(&A, &B, &result);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(sum_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t A, B, result;
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(4, 4, &B);
  s21_fill_in(&A, 3);
  s21_fill_in(&B, 4);
  int sum_code = s21_sum_matrix(&A, &B, &result);
  ck_assert_uint_eq(sum_code, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix = NULL;
  int sum_code = s21_sum_matrix(&A, &B, &result);
  ck_assert_uint_eq(sum_code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_1) {
  matrix_t A, B, result, compare;
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_create_matrix(5, 5, &compare);
  s21_fill_in(&A, 3);
  s21_fill_in(&B, 4);
  s21_fill_in(&compare, -1);
  int sub_code = s21_sub_matrix(&A, &B, &result);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(sub_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
  matrix_t A, B, result;
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(4, 4, &B);
  s21_fill_in(&A, 3);
  s21_fill_in(&B, 4);
  int sub_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_uint_eq(sub_code, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_3) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix = NULL;
  int sub_code = s21_sub_matrix(&A, &B, &result);
  ck_assert_uint_eq(sub_code, 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&A);
}
END_TEST

void part2_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_sum_matrix_test_1);
  tcase_add_test(tc1_1, s21_sum_matrix_test_2);
  tcase_add_test(tc1_1, s21_sum_matrix_test_3);
  tcase_add_test(tc1_1, s21_sub_matrix_test_1);
  tcase_add_test(tc1_1, s21_sub_matrix_test_2);
  tcase_add_test(tc1_1, s21_sub_matrix_test_3);
}

START_TEST(s21_mult_number_test_1) {
  matrix_t A, result, compare;
  s21_create_matrix(12, 12, &A);
  s21_create_matrix(12, 12, &compare);
  s21_fill_in(&A, 5);
  s21_fill_in(&compare, -25);
  int mult_code = s21_mult_number(&A, -5, &result);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(mult_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix = NULL;
  int mult_code = s21_mult_number(&A, -5, &result);
  ck_assert_uint_eq(mult_code, 1);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_1) {
  matrix_t A, B, result, compare;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);
  s21_create_matrix(3, 3, &compare);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = -1;
  B.matrix[0][2] = 1;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 3;
  B.matrix[1][2] = 4;

  compare.matrix[0][0] = 9;
  compare.matrix[0][1] = 11;
  compare.matrix[0][2] = 17;
  compare.matrix[1][0] = 12;
  compare.matrix[1][1] = 13;
  compare.matrix[1][2] = 22;
  compare.matrix[2][0] = 15;
  compare.matrix[2][1] = 15;
  compare.matrix[2][2] = 27;

  int mult_code = s21_mult_matrix(&A, &B, &result);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(mult_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
  matrix_t A, B, result, compare;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(4, 3, &B);
  s21_create_matrix(3, 3, &compare);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 14;
  A.matrix[0][2] = 33;
  A.matrix[0][3] = 51;
  A.matrix[1][0] = 62;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[1][3] = -1;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 34;
  A.matrix[2][2] = 44;
  A.matrix[2][3] = 0;

  B.matrix[0][0] = 78;
  B.matrix[0][1] = 14;
  B.matrix[0][2] = 98;
  B.matrix[1][0] = 43;
  B.matrix[1][1] = 98;
  B.matrix[1][2] = 88;
  B.matrix[2][0] = 0;
  B.matrix[2][1] = 93;
  B.matrix[2][2] = 12;
  B.matrix[3][0] = 23;
  B.matrix[3][1] = 35;
  B.matrix[3][2] = 93;

  compare.matrix[0][0] = 1853;
  compare.matrix[0][1] = 6240;
  compare.matrix[0][2] = 6469;
  compare.matrix[1][0] = 4942;
  compare.matrix[1][1] = 1499;
  compare.matrix[1][2] = 6295;
  compare.matrix[2][0] = 1618;
  compare.matrix[2][1] = 7452;
  compare.matrix[2][2] = 3716;

  int mult_code = s21_mult_matrix(&A, &B, &result);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(mult_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_mult_matrix_test_3) {
  matrix_t A, B, result;
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(4, 3, &B);

  A.matrix = NULL;

  int mult_code = s21_mult_matrix(&A, &B, &result);
  ck_assert_uint_eq(mult_code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_1) {
  matrix_t A, compare, result;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &compare);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;

  compare.matrix[0][0] = 1;
  compare.matrix[0][1] = 2;
  compare.matrix[0][2] = 3;
  compare.matrix[1][0] = 4;
  compare.matrix[1][1] = 5;
  compare.matrix[1][2] = 6;

  int trans_code = s21_transpose(&A, &result);

  for (int i = 0; i < A.columns; i++) {
    for (int j = 0; j < A.rows; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(trans_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix = NULL;
  int trans_code = s21_transpose(&A, &result);
  ck_assert_uint_eq(trans_code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  double result;
  int determ_code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, 0);
  ck_assert_uint_eq(determ_code, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_2) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;

  double result;
  int determ_code = s21_determinant(&A, &result);

  ck_assert_double_eq(result, 1);
  ck_assert_uint_eq(determ_code, 0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_3) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);
  A.matrix = NULL;
  double result;
  int determ_code = s21_determinant(&A, &result);

  ck_assert_uint_eq(determ_code, 1);
  s21_remove_matrix(&A);
}
END_TEST

void part3_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_mult_number_test_1);
  tcase_add_test(tc1_1, s21_mult_number_test_2);
  tcase_add_test(tc1_1, s21_mult_matrix_test_1);
  tcase_add_test(tc1_1, s21_mult_matrix_test_2);
  tcase_add_test(tc1_1, s21_mult_matrix_test_3);
  tcase_add_test(tc1_1, s21_transpose_test_1);
  tcase_add_test(tc1_1, s21_transpose_test_2);
  tcase_add_test(tc1_1, s21_determinant_test_1);
  tcase_add_test(tc1_1, s21_determinant_test_2);
  tcase_add_test(tc1_1, s21_determinant_test_3);
}

START_TEST(s21_calc_complements_test_1) {
  matrix_t A, compare, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &compare);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  compare.matrix[0][0] = 0;
  compare.matrix[0][1] = 10;
  compare.matrix[0][2] = -20;
  compare.matrix[1][0] = 4;
  compare.matrix[1][1] = -14;
  compare.matrix[1][2] = 8;
  compare.matrix[2][0] = -8;
  compare.matrix[2][1] = -2;
  compare.matrix[2][2] = 4;

  int comple_code = s21_calc_complements(&A, &result);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }
  ck_assert_uint_eq(comple_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_calc_complements_test_2) {
  matrix_t A, result;
  s21_create_matrix(3, 4, &A);
  int comple_code = s21_calc_complements(&A, &result);

  ck_assert_uint_eq(comple_code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_inverse_matrix_test_1) {
  matrix_t A, compare, result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &compare);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  compare.matrix[0][0] = 1;
  compare.matrix[0][1] = -1;
  compare.matrix[0][2] = 1;
  compare.matrix[1][0] = -38;
  compare.matrix[1][1] = 41;
  compare.matrix[1][2] = -34;
  compare.matrix[2][0] = 27;
  compare.matrix[2][1] = -29;
  compare.matrix[2][2] = 24;

  int inverse_code = s21_inverse_matrix(&A, &result);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq(compare.matrix[i][j], result.matrix[i][j]);
    }
  }

  ck_assert_uint_eq(inverse_code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&compare);
}
END_TEST

START_TEST(s21_calc_inverse_matrix_test_2) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int inverse_code = s21_inverse_matrix(&A, &result);

  ck_assert_uint_eq(inverse_code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

void part4_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_calc_complements_test_1);
  tcase_add_test(tc1_1, s21_calc_complements_test_2);
  tcase_add_test(tc1_1, s21_calc_inverse_matrix_test_1);
  tcase_add_test(tc1_1, s21_calc_inverse_matrix_test_2);
}

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  part1_tests(tc1_1);
  part2_tests(tc1_1);
  part3_tests(tc1_1);
  part4_tests(tc1_1);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
