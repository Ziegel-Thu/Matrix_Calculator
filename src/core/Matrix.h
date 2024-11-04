#pragma once
#include <vector>
#include <stdexcept>

class Matrix {
public:
    Matrix(int rows, int cols); // 构造函数

    // 获取行数
    int getRows() const;

    // 获取列数
    int getCols() const;

    // 获取指定位置的元素
    long long getEntry(int row, int col) const;

    // 设置指定位置的元素
    void setEntry(int row, int col, long long value);

private:
    int rows_; // 行数
    int cols_; // 列数
    std::vector<std::vector<long long>> data_; // 矩阵数据
};
