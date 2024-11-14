#include "Matrix.h"

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

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
    if (data_[row][col].hasValue_) {
        return data_[row][col]; // 返回指定位置的元素
    } else {
        throw std::invalid_argument("Entry has no value"); // 检查元素是否有值
    }
}

bool Matrix::hasValue(int row, int col) const {
    return data_[row][col].hasValue_;
}

void Matrix::setEntry(int row, int col, const Entry& value) {

    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        throw std::out_of_range("Index out of range"); // 检查索引范围
    }
    data_[row][col] = value; // 设置指定位置的元素
    data_[row][col].hasValue_ = true;
}

void Matrix::reduceAll() {
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (data_[i][j].hasValue_) {
                data_[i][j].reduce();
            } // 对每个元素进行约分
        }
    }
}
void Matrix::identity(){
    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (i == j)
            {
                setEntry(i, j, Entry(1, 1));
            }
            else
            {
                setEntry(i, j, Entry(0, 1));
            }
            
        }
    }
}
std::tuple<Matrix, Matrix, Matrix> Matrix::pluDecomposition() const {
    if (rows_ != cols_) {
        throw std::invalid_argument("PLU decomposition requires a square matrix");
    }

    int n = rows_;
    Matrix L(n, n);
    Matrix U(*this); // 复制当前矩阵到 U
    Matrix P(n, n);

    // 初始化 P 为单位矩阵
    P.identity();

    for (int i = 0; i < n; ++i) {
        // 寻找主元
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (std::abs(U.getEntry(k, i).getNumerator()) > std::abs(U.getEntry(maxRow, i).getNumerator())) {
                maxRow = k;
            }
        }

        // 交换行
        if (i != maxRow) {
            for (int k = 0; k < n; ++k) {
                std::swap(U.data_[i][k], U.data_[maxRow][k]);
                std::swap(P.data_[i][k], P.data_[maxRow][k]);
            }
        }

        // 检查主元是否为零
        if (U.getEntry(i, i).getNumerator() == 0) {
            throw std::runtime_error("Matrix is singular and cannot be decomposed");
        }

        // 计算 L 和 U
        for (int j = i + 1; j < n; ++j) {
            Entry factor = U.getEntry(j, i).operator/( U.getEntry(i, i));
            L.setEntry(j, i, factor);
            for (int k = i; k < n; ++k) {
                U.setEntry(j, k, U.getEntry(j, k).operator-( factor.operator*(  U.getEntry(i, k))));
            }
        }
    }

    // 设置 L 的对角线为 1
    for (int i = 0; i < n; ++i) {
        L.setEntry(i, i, Entry(1, 1));
    }

    return {P, L, U}; // 返回 P, L, U 矩阵
}

Entry Matrix::getDeterminant() const {

    // 基础情况：1x1 矩阵
    if (rows_ == 1) {
        return data_[0][0];
    }

    // 基础情况：2x2 矩阵
    if (rows_ == 2) {
        return data_[0][0].operator*(data_[1][1]).operator-(data_[0][1].operator*(data_[1][0]));
    }

    // 递归计算行列式
    Entry determinant(0, 1);
    for (int col = 0; col < cols_; ++col) {
        Matrix subMatrix(rows_ - 1, cols_ - 1);

        // 创建子矩阵
        for (int subRow = 1; subRow < rows_; ++subRow) {
            int subColIndex = 0;
            for (int subCol = 0; subCol < cols_; ++subCol) {
                if (subCol == col) continue;
                subMatrix.setEntry(subRow - 1, subColIndex, data_[subRow][subCol]);
                subColIndex++;
            }
        }

        // 递归计算子矩阵的行列式
        Entry subDeterminant = subMatrix.getDeterminant();
        Entry cofactor = data_[0][col].operator*(subDeterminant);

        // 根据位置调整符号
        if (col % 2 == 0) {
            determinant = determinant.operator+(cofactor);
        } else {
            determinant = determinant.operator-(cofactor);
        }
    }

    return determinant;
}
Matrix Matrix::inverse() const {

    Entry det = getDeterminant();
    int n = rows_;
    Matrix adjugate(n, n);

    // 计算伴随矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // 创建子矩阵
            Matrix subMatrix(n - 1, n - 1);
            for (int subRow = 0; subRow < n; ++subRow) {
                if (subRow == i) continue;
                for (int subCol = 0; subCol < n; ++subCol) {
                    if (subCol == j) continue;
                    int destRow = subRow < i ? subRow : subRow - 1;
                    int destCol = subCol < j ? subCol : subCol - 1;
                    subMatrix.setEntry(destRow, destCol, data_[subRow][subCol]);
                }
            }

            // 计算余子式
            Entry subDeterminant = subMatrix.getDeterminant();
            Entry cofactor = ((i + j) % 2 == 0) ? subDeterminant : subDeterminant.operator-();

            // 伴随矩阵的元素是余子式的转置
            adjugate.setEntry(j, i, cofactor);
        }
    }

    // 计算逆矩阵
    Matrix inverse(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverse.setEntry(i, j, adjugate.getEntry(i, j).operator/(det));
        }
    }

    return inverse;
}