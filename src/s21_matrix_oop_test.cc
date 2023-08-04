#include "s21_matrix_oop.h"

#include "gtest/gtest.h"

TEST(Constructor, basic) {
  s21::S21Matrix matrix;

  EXPECT_EQ(matrix.GetRows(), 1);
  EXPECT_EQ(matrix.GetRows(), 1);
}

TEST(Constructor, rows_cols) {
  s21::S21Matrix matrix(5, 5);

  EXPECT_EQ(matrix.GetRows(), 5);
  EXPECT_EQ(matrix.GetCols(), 5);
}

TEST(Constructor, copy) {
  s21::S21Matrix matrix_source(2, 2);

  matrix_source(0, 0) = 1.0;
  matrix_source(0, 1) = 2.0;
  matrix_source(1, 0) = 3.0;
  matrix_source(1, 1) = 4.0;

  s21::S21Matrix matrix_dest(matrix_source);

  EXPECT_TRUE(matrix_source == matrix_dest);
}

TEST(Constructor, move) {
  s21::S21Matrix matrix_source(2, 2);
  s21::S21Matrix matrix_dest(2, 2);

  s21::S21Matrix moved(std::move(matrix_source));

  EXPECT_TRUE(moved == matrix_dest);

  EXPECT_EQ(matrix_source.GetRows(), 0);
  EXPECT_EQ(matrix_source.GetCols(), 0);
}

TEST(EqMatrix, true) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 1.0;
  matrix2(0, 1) = 2.0;
  matrix2(1, 0) = 3.0;
  matrix2(1, 1) = 4.0;

  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(EqMatrix, false) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(SumMatrix, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1.SumMatrix(matrix2));
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(SubMatrix, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1.SubMatrix(matrix2));
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

TEST(MulNumber, normal) {
  s21::S21Matrix matrix1(2, 2);
  double num = 5.0;

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1.MulNumber(num);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 20.0);
}

TEST(MulMatrix, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1.MulMatrix(matrix2));
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 50.0);
}

TEST(Transpose, normal) {
  s21::S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(matrix1.Transpose()(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(matrix1.Transpose()(0, 1), 3.0);
  EXPECT_DOUBLE_EQ(matrix1.Transpose()(1, 0), 2.0);
  EXPECT_DOUBLE_EQ(matrix1.Transpose()(1, 1), 4.0);
}

TEST(CalcComplements, normal) {
  s21::S21Matrix matrix1(3, 3);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(0, 2) = 3.0;
  matrix1(1, 0) = 4.0;
  matrix1(1, 1) = 5.0;
  matrix1(1, 2) = 6.0;
  matrix1(2, 0) = 7.0;
  matrix1(2, 1) = 8.0;
  matrix1(2, 2) = 9.0;

  EXPECT_NO_THROW(matrix1.CalcComplements());
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(0, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(0, 2), -3.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(1, 1), -12.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(1, 2), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(2, 0), -3.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(2, 1), 6.0);
  EXPECT_DOUBLE_EQ(matrix1.CalcComplements()(2, 2), -3.0);
}

TEST(Determinant, normal) {
  s21::S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_NO_THROW(matrix1.Determinant());
  EXPECT_DOUBLE_EQ(matrix1.Determinant(), -2.0);
}

TEST(InverseMatrix, normal) {
  s21::S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  EXPECT_NO_THROW(matrix1.InverseMatrix());
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(0, 0), -2.0);
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(0, 1), 1.0);
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(matrix1.InverseMatrix()(1, 1), -0.5);
}

TEST(GetRows, normal) {
  s21::S21Matrix matrix1(3, 2);

  EXPECT_EQ(matrix1.GetRows(), 3);
}

TEST(SetRows, less) {
  s21::S21Matrix matrix1(3, 3);

  EXPECT_NO_THROW(matrix1.SetRows(2));
  EXPECT_EQ(matrix1.GetRows(), 2);
}

TEST(SetRows, more) {
  s21::S21Matrix matrix1(2, 2);

  EXPECT_NO_THROW(matrix1.SetRows(3));
  EXPECT_EQ(matrix1.GetRows(), 3);
  EXPECT_DOUBLE_EQ(matrix1(2, 0), 0);
  EXPECT_DOUBLE_EQ(matrix1(2, 1), 0);
}

TEST(GetCols, normal) {
  s21::S21Matrix matrix1(2, 3);

  EXPECT_EQ(matrix1.GetCols(), 3);
}

TEST(SetCols, less) {
  s21::S21Matrix matrix1(3, 3);

  EXPECT_NO_THROW(matrix1.SetCols(2));
  EXPECT_EQ(matrix1.GetCols(), 2);
}

TEST(SetCols, more) {
  s21::S21Matrix matrix1(2, 2);

  EXPECT_NO_THROW(matrix1.SetCols(3));
  EXPECT_EQ(matrix1.GetCols(), 3);
  EXPECT_DOUBLE_EQ(matrix1(0, 2), 0);
  EXPECT_DOUBLE_EQ(matrix1(1, 2), 0);
}

TEST(Plus, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 + matrix2);
  s21::S21Matrix result = matrix1 + matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 12.0);
}

TEST(AssnPlus, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 += matrix2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 12.0);
}

TEST(Minus, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 - matrix2);
  s21::S21Matrix result = matrix1 - matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(result(1, 1), -4.0);
}

TEST(AssnMinus, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 -= matrix2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), -4.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), -4.0);
}

TEST(MulMatrixOperator, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 * matrix2);
  s21::S21Matrix result = matrix1 * matrix2;
  EXPECT_DOUBLE_EQ(result(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 50.0);
}

TEST(MulNumberOperator, normal) {
  s21::S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  s21::S21Matrix result = matrix1 * 5.0;
  EXPECT_DOUBLE_EQ(result(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(result(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(result(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(result(1, 1), 20.0);
}

TEST(AssnMulMatrixOperator, normal) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix2(0, 0) = 5.0;
  matrix2(0, 1) = 6.0;
  matrix2(1, 0) = 7.0;
  matrix2(1, 1) = 8.0;

  EXPECT_NO_THROW(matrix1 *= matrix2);
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 50.0);
}

TEST(AssnMulNumberOperator, normal) {
  s21::S21Matrix matrix1(2, 2);

  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;

  matrix1 *= 5.0;
  EXPECT_DOUBLE_EQ(matrix1(0, 0), 5.0);
  EXPECT_DOUBLE_EQ(matrix1(0, 1), 10.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 0), 15.0);
  EXPECT_DOUBLE_EQ(matrix1(1, 1), 20.0);
}

TEST(Assn, copy) {
  s21::S21Matrix matrix_source(2, 2);

  matrix_source(0, 0) = 1.0;
  matrix_source(0, 1) = 2.0;
  matrix_source(1, 0) = 3.0;
  matrix_source(1, 1) = 4.0;

  s21::S21Matrix matrix_dest = matrix_source;

  EXPECT_TRUE(matrix_source == matrix_dest);
}

TEST(Assn, move) {
  s21::S21Matrix matrix_source(2, 2);
  s21::S21Matrix matrix_dest(2, 2);

  s21::S21Matrix moved = std::move(matrix_source);

  EXPECT_TRUE(moved == matrix_dest);

  EXPECT_EQ(matrix_source.GetRows(), 0);
  EXPECT_EQ(matrix_source.GetCols(), 0);
}

TEST(EqMatrixOperator, true) {
  s21::S21Matrix matrix1(2, 2);
  s21::S21Matrix matrix2(2, 2);

  EXPECT_TRUE(matrix1 == matrix2);
}

TEST(EqMatrixOperator, false) {
  s21::S21Matrix matrix1(3, 3);
  s21::S21Matrix matrix2(2, 2);

  EXPECT_FALSE(matrix1 == matrix2);
}

TEST(Staples, normal) {
  s21::S21Matrix matrix1(2, 2);

  EXPECT_EQ(matrix1(1, 1), 0);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
