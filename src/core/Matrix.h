#pragma once
#include <vector>
#include <stdexcept>
#include "Entry.h" // 引入 Entry 类
#include "EntryPolynomial.h"
class Matrix {
public:
    Matrix(int rows, int cols); // 构造函数
    ~Matrix();
    // 获取行列数
    int getRows() const;
    int getCols() const;

    Entry getEntry(int row, int col) const;
    void setEntry(int row, int col, const Entry& value);
    // 获取行列向量
    std::vector<Entry> getRow(int row) const;
    std::vector<Entry> getColumn(int col) const;
    void setRow(int row, const std::vector<Entry>& values);
    void setColumn(int col, const std::vector<Entry>& values);
    void rowPopBack();
    void columnPopBack();

    void reduceAll();
    void identity();
    bool hasValue(int row, int col) const;
    Matrix getIdentityMatrix(int n) const;
    Matrix RightMultiply(const Matrix& other) const;
    std::vector<Entry> RightMultiplyVector(const std::vector<Entry>& other) const;
    Matrix LeftMultiply(const Matrix& other) const;
    std::vector<Entry> LeftMultiplyVector(const std::vector<Entry>& other) const;
    Matrix getMatrixTranspose() const;
    static Entry getInnerProduct(const std::vector<Entry>& a,const std::vector<Entry>& b);
    static Entry norm(const std::vector<Entry>& a) ;
    std::pair<std::vector<Entry>,std::vector<Entry> > getColumnNormsAndInverse() const;
    std::vector<Entry> entryMultiplyOnVector(const Entry& coefficient,const std::vector<Entry>& a) const;
    std::tuple<Matrix,Matrix,Matrix> pluDecomposition() const;
    Entry getDeterminant() const;
    Matrix inverse() const;
    std::pair<Matrix, Matrix> qrDecomposition() const;
    std::tuple<Matrix,Matrix,std::vector<int>,std::vector<int> > getGramSchimdtQRDecomposition() const;
    EntryPolynomial getCharacteristicPolynomial() const;
    std::tuple<Matrix,Matrix,Matrix> getSVDdecomposition() const;
    Matrix getJordanForm() const;
    int getRank() const;
    EntryPolynomial calculateDeterminant(const std::vector<std::vector<EntryPolynomial> >& polyMatrix) const;
    static bool isZeroVector(const std::vector<Entry>& a);
private:
    int rows_; // 行数
    int cols_; // 列数

    std::vector<std::vector<Entry> > data_; // 矩阵数据，使用 Entry 类型
    std::vector<std::pair<Entry,int> > getEigenvalues() const;
    Matrix getOrthogonalEigenBasis(const std::vector<std::pair<Entry,int> >& eigenvalues) const;
};
