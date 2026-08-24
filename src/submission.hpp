#pragma once

#include <cstddef>
#include <vector>

class Grid {
private:
  std::vector<double> grid;
  std::size_t rows_;
  std::size_t cols_;

public:
  Grid(std::size_t rows, std::size_t cols) {
    grid.resize(rows * cols);
    this->rows_ = rows;
    this->cols_ = cols;
  }
  double &operator()(std::size_t i, std::size_t j) {
    return grid[i * cols_ + j];
  };

  double operator()(std::size_t i, std::size_t j) const {
    return grid[i * cols_ + j];
  };

  int rows() const { return rows_; }
  int cols() const { return cols_; }
};

void apply_stencil(const Grid &old_grid, Grid &new_grid) {
  int rows = old_grid.rows();
  int cols = old_grid.cols();

  for (int i = 0; i < cols; i++) {
    new_grid(0, i) = old_grid(0, i);
    new_grid(rows - 1, i) = old_grid(rows - 1, i);
  }

  for (int i = 0; i < rows; i++) {
    new_grid(i, 0) = old_grid(i, 0);
    new_grid(i, cols - 1) = old_grid(i, cols - 1);
  }
  for (int i = 1; i < rows - 1; i++) {

    for (int j = 1; j < cols - 1; j++) {
      new_grid(i, j) = 0.5 * old_grid(i, j) +
                       0.125 * (old_grid(i - 1, j) + old_grid(i + 1, j) +
                                old_grid(i, j - 1) + old_grid(i, j + 1));
    }
  }
}
