#pragma once
#include <vector>
#include <stdexcept>
#include "Entry.h" // 引入 Entry 类

class Matrix {
public:
    Matrix(int rows, int cols); // 构造函数

    // 获取行数
    int getRows() const;

    // 获取列数
    int getCols() const;

    // 获取指定位置的元素
    Entry getEntry(int row, int col) const;

    // 设置指定位置的元素
    void setEntry(int row, int col, const Entry& value);

    // 整体约分操作
    void reduceAll();
    void identity();

    // PLU 分解
    std::tuple<Matrix, Matrix, Matrix> pluDecomposition() const;
    Entry getDeterminant() const;
    Matrix inverse() const;
    bool hasValue(int row, int col) const;
    

private:
    int rows_; // 行数
    int cols_; // 列数

    std::vector<std::vector<Entry>> data_; // 矩阵数据，使用 Entry 类型
};
