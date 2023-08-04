#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

namespace s21 {
const double keps = 1e-7;

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  int GetRows() const;
  void SetRows(int rows);
  int GetCols() const;
  void SetCols(int cols);

  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);

  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);

  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix operator*(double num) const;

  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);

  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator=(S21Matrix &&other) noexcept;

  bool operator==(const S21Matrix &other) const;
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;

 private:
  int rows_, cols_;
  double **matrix_;

  S21Matrix MinorMatrix_(int rows, int cols) const;
  void CreateMatrix_(int rows, int cols);
};
}  // namespace s21

#endif  // SRC_S21_MATRIX_OOP_H_
