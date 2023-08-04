#include "s21_matrix_oop.h"

#include <cmath>
#include <stdexcept>

namespace s21 {
void S21Matrix::CreateMatrix_(int rows, int cols) {
  rows_ = rows;
  cols_ = cols;

  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix() { CreateMatrix_(1, 1); }

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Invalid values");
  }

  CreateMatrix_(rows, cols);
}

S21Matrix::S21Matrix(const S21Matrix &other) {
  CreateMatrix_(other.rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;

    rows_ = 0;
    cols_ = 0;
    matrix_ = nullptr;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    return false;
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > keps) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Invalid input, wrong size");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Invalid input, wrong size");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "The number of cols is not equal to the number "
        "of rows of the second matrix");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      for (int k = 0; k < other.cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }

  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Is not square matrix");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor_matrix = MinorMatrix_(i, j);
      result.matrix_[i][j] = std::pow((-1), i + j) * minor_matrix.Determinant();
    }
  }

  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Is not square matrix");
  }

  double result = 0.0;

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor_matrix = MinorMatrix_(0, j);
      result += matrix_[0][j] * pow(-1, j) * minor_matrix.Determinant();
    }
  }

  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = Determinant();
  if (fabs(det) < keps) {
    throw std::invalid_argument("Matrix determinant = 0");
  }

  S21Matrix result(rows_, cols_);

  if (rows_ == 1) {
    result.matrix_[0][0] = 1 / matrix_[0][0];
  } else {
    S21Matrix tmp = CalcComplements();
    result = tmp.Transpose();
    result.MulNumber(1 / det);
  }

  return result;
}

int S21Matrix::GetRows() const { return rows_; }

void S21Matrix::SetRows(const int rows) {
  if (rows < 1) {
    throw std::invalid_argument("Matrix must have rows");
  }

  S21Matrix result(rows, cols_);

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (i < rows_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }

  *this = result;
}

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetCols(const int cols) {
  if (cols < 1) {
    throw std::invalid_argument("Matrix must have cols");
  }

  S21Matrix result(rows_, cols);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j < cols_) {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }

  *this = result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  S21Matrix result(*this);

  result.SumMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  S21Matrix result(*this);

  result.SubMatrix(other);
  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  S21Matrix result(*this);

  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix result(*this);

  result.MulNumber(num);
  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (&other != this) {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
      this->~S21Matrix();
      CreateMatrix_(other.rows_, other.cols_);
    }

    rows_ = other.rows_;
    cols_ = other.cols_;

    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }

  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (&other != this) {
    this->~S21Matrix();

    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;

    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

double &S21Matrix::operator()(const int i, const int j) {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::invalid_argument("Incorrect index");
  }

  return matrix_[i][j];
}

const double &S21Matrix::operator()(const int i, const int j) const {
  if ((i < 0 || i >= rows_) || (j < 0 || j >= cols_)) {
    throw std::invalid_argument("Incorrect index");
  }

  return matrix_[i][j];
}

S21Matrix S21Matrix::MinorMatrix_(int row, int col) const {
  S21Matrix result(rows_ - 1, cols_ - 1);

  for (int i = 0, min_i = 0; min_i < result.rows_; ++min_i) {
    (row == i) ? ++i : i;
    for (int j = 0, min_j = 0; min_j < result.cols_; ++min_j) {
      (col == j) ? ++j : j;
      result.matrix_[min_i][min_j] = matrix_[i][j];
      ++j;
    }
    ++i;
  }

  return result;
}
}  // namespace s21
