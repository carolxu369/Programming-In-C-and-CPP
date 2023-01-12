#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!

template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c) {
    std::vector<T> curr(c);
    for (int i = 0; i < r; i++) {
      std::vector<T> curr(c);
      rows.push_back(curr);
    }
  }

  Matrix(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
  }

  ~Matrix() { rows.clear(); }

  Matrix<T> & operator=(const Matrix<T> & rhs) {
    if (this != &rhs) {
      rows.clear();
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = rhs.rows;
    }

    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const std::vector<T> & operator[](int index) const {
    assert(index >= 0);
    assert(index < numRows);
    return rows[index];
  }
  std::vector<T> & operator[](int index) {
    assert(index >= 0);
    assert(index < numRows);
    return rows[index];
  }

  bool operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows) {
      return false;
    }

    if (numColumns != rhs.numColumns) {
      return false;
    }

    if (rows != rhs.rows) {
      return false;
    }
    return true;
  }

  Matrix<T> operator+(const Matrix<T> & rhs) const {
    assert(this->numRows == rhs.numRows);
    assert(this->numColumns == rhs.numColumns);

    Matrix<T> result(this->numRows, this->numColumns);

    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        result[i][j] = rows[i][j] + rhs.rows[i][j];
      }
    }

    return result;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[ "
      << " ]";
    return s;
  }

  s << "[ ";

  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << "," << std::endl;
  }

  s << rhs[rhs.getRows() - 1] << " ]";

  return s;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() == 0) {
    s << "{"
      << "}";
    return s;
  }
  s << "{";

  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }

  s << rhs[rhs.size() - 1] << "}";

  return s;
}
#endif
