#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    data_.resize(rows, std::vector<long long>(cols, 0)); // 初始化矩阵，默认值为0
}

int Matrix::getRows() const {
    return rows_; // 返回行数
}

int Matrix::getCols() const {
    return cols_; // 返回列数
}

long long Matrix::getEntry(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range"); // 检查索引范围
    }
    return data_[row][col]; // 返回指定位置的元素
}

void Matrix::setEntry(int row, int col, long long value) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range"); // 检查索引范围
    }
    data_[row][col] = value; // 设置指定位置的元素
}
