#include "Matrix.h"

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    data_.resize(rows, std::vector<Entry>(cols, Entry(0, 1))); // 初始化矩阵，默认值为 0/1
}

int Matrix::getRows() const {
    return rows_; // 返回行数
}

int Matrix::getCols() const {
    return cols_; // 返回列数
}

Entry Matrix::getEntry(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range"); // 检查索引范围
    }
    return data_[row][col]; // 返回指定位置的元素
}

void Matrix::setEntry(int row, int col, const Entry& value) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range"); // 检查索引范围
    }
    data_[row][col] = value; // 设置指定位置的元素
}

void Matrix::reduceAll() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            data_[i][j].reduce(); // 对每个元素进行约分
        }
    }
}

