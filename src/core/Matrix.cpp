#include "Matrix.h"
#include "ErrorHandler.h"
#include <tuple>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
    if (rows <= 0 || cols <= 0) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵维度必须为正数");
        rows_ = 1;
        cols_ = 1;
    }
    data_.resize(rows_, std::vector<Entry>(cols_, Entry(0, 1)));
}
Matrix::~Matrix()
{
    // 不需要手动调用 Entry 的析构函数
}

int Matrix::getRows() const
{
    return rows_; // 返回行数
}

int Matrix::getCols() const
{
    return cols_; // 返回列数
}

std::vector<Entry> Matrix::getRow(int row) const
{
    return data_[row];
}


Entry Matrix::getEntry(int row, int col) const {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        emit ErrorHandler::getInstance().errorOccurred("索引超出范围");
        return Entry(0, 1);
    }
    if (!data_[row][col].hasValue_) {
        emit ErrorHandler::getInstance().errorOccurred("元素未初始化");
        return Entry(0, 1);
    }
    return data_[row][col];
}


std::vector<Entry> Matrix::getColumn(int col) const
{
    std::vector<Entry> result;
    for (int i = 0; i < rows_; i++)
    {
        result.push_back(data_[i][col]);
    }
    return result;
}

void Matrix::setColumn(int col, const std::vector<Entry> &values)
{
    for (int i = 0; i < rows_; i++)
    {
        data_[i][col] = values[i];
        data_[i][col].hasValue_ = true;
    }
}

void Matrix::setRow(int row, const std::vector<Entry> &values)
{
    data_[row] = values;
    for(int i = 0;i<values.size();i++){
        data_[row][i].hasValue_ = true;
    }
}

void Matrix::rowPopBack()
{
    data_.pop_back();
    rows_--;
}

void Matrix::columnPopBack()
{
    for (int i = 0; i < rows_; i++)
    {
        data_[i].pop_back();
    }
    cols_--;
}

bool Matrix::hasValue(int row, int col) const
{
    return data_[row][col].hasValue_;
}

void Matrix::setEntry(int row, int col, const Entry &value) {
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
        emit ErrorHandler::getInstance().errorOccurred("索引超出范围");
        return;
    }
    data_[row][col] = value;
    data_[row][col].hasValue_ = true;
}

void Matrix::reduceAll()
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            if (data_[i][j].hasValue_)
            {
                data_[i][j].reduce();
            } // 对每个元素进行约分
        }
    }
}

void Matrix::identity()
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            setEntry(i, j, (i == j) ? Entry(1, 1) : Entry(0, 1));
        }
    }
}

Matrix Matrix::getMatrixTranspose() const
{
    Matrix result(cols_, rows_);
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            result.setEntry(j, i, getEntry(i, j));
        }
    }
    return result;
}

Matrix Matrix::getIdentityMatrix(int n) const
{
    Matrix result(n, n);
    result.identity();
    return result;
}

Matrix Matrix::LeftMultiply(const Matrix &other) const
{
    if (other.cols_ != rows_) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵维度不匹配");
        return Matrix(1, 1);
    }
    Matrix result(other.rows_, cols_);
    for (int i = 0; i < other.rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            Entry temp(0, 1);
            for (int k = 0; k < other.cols_; ++k) {
                temp = temp + (other.getEntry(i, k) * getEntry(k, j));
            }
            result.setEntry(i, j, temp);
        }
    }

    return result;
}

std::vector<Entry> Matrix::LeftMultiplyVector(const std::vector<Entry> &other) const
{
    std::vector<Entry> result(cols_);
    for (int i = 0; i < cols_; i++)
    {
        result[i] = getInnerProduct(other, getColumn(i));
    }
    return result;
}

Matrix Matrix::RightMultiply(const Matrix &other) const
{
    if (cols_ != other.rows_) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵维度不匹配");
        return Matrix(1, 1);
    }
    Matrix result(rows_, other.cols_);
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < other.cols_; ++j)
        {
            Entry temp(0, 1);
            for (int k = 0; k < cols_; ++k)
            {
                temp = temp + (getEntry(i, k) * other.getEntry(k, j));
            }
            result.setEntry(i, j, temp);
        }
    }
    return result;
}

std::vector<Entry> Matrix::RightMultiplyVector(const std::vector<Entry> &other) const
{
    std::vector<Entry> result(rows_);
    for (int i = 0; i < rows_; i++)
    {
        result[i] = getInnerProduct(other, getRow(i));
    }
    return result;
}

Entry Matrix::norm(const std::vector<Entry> &a)
{
    Entry result(0, 1);
    for (Entry i : a)
    {
        result = result + i * i;
    }
    return result;
}

std::pair<std::vector<Entry>, std::vector<Entry>> Matrix::getColumnNormsAndInverse() const
{
    std::vector<Entry> result(cols_);
    std::vector<Entry> result_inverse(rows_);
    for (int i = 0; i < rows_; i++)
    {
        Entry temp = norm(getColumn(i));
        if (temp.getNumerator() != 0)
        {
            result[i]=temp;
            result_inverse[i]=Entry(temp.getDenominator(), temp.getNumerator());
        }
        else
        {
            emit ErrorHandler::getInstance().errorOccurred("正交矩阵不能有零向量");
            return std::make_pair(std::vector<Entry>(), std::vector<Entry>());
        }
    }
    return std::make_pair(result, result_inverse);
}

std::tuple<Matrix, Matrix, Matrix> Matrix::pluDecomposition() const
{
    if (rows_ != cols_) {
        emit ErrorHandler::getInstance().errorOccurred("PLU分解需要方阵");
        return std::make_tuple(Matrix(1,1), Matrix(1,1), Matrix(1,1));
    }

    int n = rows_;
    Matrix L(n, n);
    Matrix U(*this); // 复制当前矩阵到 U
    Matrix P(n, n);

    // 初始化 P 为单位矩阵
    P.identity();

    for (int i = 0; i < n; ++i)
    {
        // 寻找主元
        int maxRow = i;
        for (int k = i + 1; k < n; ++k)
        {
            if (std::abs(U.getEntry(k, i).getNumerator()) > std::abs(U.getEntry(maxRow, i).getNumerator()))
            {
                maxRow = k;
            }
        }

        // 交换行
        if (i != maxRow)
        {
            for (int k = 0; k < n; ++k)
            {
                std::swap(U.data_[i][k], U.data_[maxRow][k]);
                std::swap(P.data_[i][k], P.data_[maxRow][k]);
            }
        }

        // 检查主元是否为零
        if (U.getEntry(i, i).getNumerator() == 0) {
            emit ErrorHandler::getInstance().errorOccurred("矩阵是奇异的，无法进行PLU分解");
            return std::make_tuple(Matrix(1,1), Matrix(1,1), Matrix(1,1));
        }

        // 计算 L 和 U
        for (int j = i + 1; j < n; ++j)
        {
            Entry factor = U.getEntry(j, i) / U.getEntry(i, i);
            L.setEntry(j, i, factor);
            for (int k = i; k < n; ++k)
            {
                U.setEntry(j, k, U.getEntry(j, k) - (factor * U.getEntry(i, k)));
            }
        }
    }

    // 设置 L 的对角线为 1
    for (int i = 0; i < n; ++i)
    {
        L.setEntry(i, i, Entry(1, 1));
    }
    Matrix U_reduced(n,n);
    for(int i = 0;i<n;i++){
        for(int j=i ;j<n;j++){
            U_reduced.setEntry(i,j,U.getEntry(i,j));
        }
    }

    return {P, L, U_reduced}; // 返回 P, L, U 矩阵
}

Entry Matrix::getDeterminant() const
{
    // 基础情况：1x1 矩阵
    if (rows_ == 1)
    {
        return data_[0][0];
    }

    // 基础情况：2x2 矩阵
    if (rows_ == 2)
    {
        return data_[0][0] * data_[1][1] - data_[0][1] * data_[1][0];
    }

    // 递归计算行列式
    Entry determinant(0, 1);
    for (int col = 0; col < cols_; ++col)
    {
        Matrix subMatrix(rows_ - 1, cols_ - 1);

        // 创建子矩阵
        for (int subRow = 1; subRow < rows_; ++subRow)
        {
            int subColIndex = 0;
            for (int subCol = 0; subCol < cols_; ++subCol)
            {
                if (subCol == col)
                    continue;
                subMatrix.setEntry(subRow - 1, subColIndex, data_[subRow][subCol]);
                subColIndex++;
            }
        }

        // 递归计算子矩阵的行列式
        Entry subDeterminant = subMatrix.getDeterminant();
        Entry cofactor = data_[0][col] * subDeterminant;

        // 根据位置调整符号
        if (col % 2 == 0)
        {
            determinant = determinant + cofactor;
        }
        else
        {
            determinant = determinant - cofactor;
        }
    }

    return determinant;
}

Matrix Matrix::inverse() const
{
    Entry det = getDeterminant();
    int n = rows_;
    if(det.getNumerator()==0){
        emit ErrorHandler::getInstance().errorOccurred("矩阵是奇异的，无法求逆");
        return Matrix(rows_, cols_);
    }
    if(n==1){
        Matrix result(1,1);
        result.setEntry(0,0,Entry(det.getDenominator(),det.getNumerator()));
        return result;
    }
    Matrix adjugate(n, n);

    // 计算伴随矩阵
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // 创建子矩阵
            Matrix subMatrix(n - 1, n - 1);
            for (int subRow = 0; subRow < n; ++subRow)
            {
                if (subRow == i)
                    continue;
                for (int subCol = 0; subCol < n; ++subCol)
                {
                    if (subCol == j)
                        continue;
                    int destRow = subRow < i ? subRow : subRow - 1;
                    int destCol = subCol < j ? subCol : subCol - 1;
                    subMatrix.setEntry(destRow, destCol, data_[subRow][subCol]);
                }
            }

            // 计算余子式
            Entry subDeterminant = subMatrix.getDeterminant();
            Entry cofactor = ((i + j) % 2 == 0) ? subDeterminant : -subDeterminant;

            // 伴随矩阵的元素是余子式的转置
            adjugate.setEntry(j, i, cofactor);
        }
    }

    // 计算逆矩阵
    Matrix inverse(n, n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            inverse.setEntry(i, j, adjugate.getEntry(i, j) / det);
        }
    }

    return inverse;
}

std::pair<Matrix, Matrix> Matrix::qrDecomposition() const
{
    int m = rows_;
    int n = cols_;
    Matrix Q(m, m);
    Matrix R(*this); // 复制当前矩阵到 R
    Q.identity();

    for (int j = 0; j < n; ++j)
    {
        for (int i = m - 1; i > j; --i)
        {
            Entry a = R.getEntry(i - 1, j);
            Entry b = R.getEntry(i, j);

            if (b.getNumerator() != 0)
            {
                // 使用 a 和 b 直接计算
                Entry c = a;
                Entry s = b;

                // 应用 Givens 旋转到 R
                for (int k = 0; k < n; ++k)
                {
                    Entry temp1 = c * R.getEntry(i - 1, k) + s * R.getEntry(i, k);
                    Entry temp2 = a * R.getEntry(i, k) - b * R.getEntry(i - 1, k);
                    R.setEntry(i - 1, k, temp1);
                    R.setEntry(i, k, temp2);
                }

                // 应用 Givens 旋转到 Q
                for (int k = 0; k < m; ++k)
                {
                    Entry temp1 = c * Q.getEntry(k, i - 1) + s * Q.getEntry(k, i);
                    Entry temp2 = a * Q.getEntry(k, i) - b * Q.getEntry(k, i - 1);
                    Q.setEntry(k, i - 1, temp1);
                    Q.setEntry(k, i, temp2);
                }
            }
        }
    }
    Matrix R_reduced(m,n);
    for(int i = 0;i<m;i++){
        for(int j=i ;j<n;j++){
            R_reduced.setEntry(i,j,R.getEntry(i,j));
        }
    }

    return {Q, R_reduced};
}

Entry Matrix::getInnerProduct(const std::vector<Entry> &a, const std::vector<Entry> &b)
{
    if (a.size() != b.size()) {
        emit ErrorHandler::getInstance().errorOccurred("向量长度不一致");
        return Entry(0, 1);
    }
    Entry result(0, 1);
    for (int i = 0; i < static_cast<int>(a.size()); i++)
    {
        result = result + a[i] * b[i];
    }
    return result;
}

std::vector<Entry> Matrix::entryMultiplyOnVector(const Entry &coefficient, const std::vector<Entry> &a) const
{
    std::vector<Entry> result(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        result[i] = coefficient * a[i];
    }
    return result;
}

bool Matrix::isZeroVector(const std::vector<Entry> &a)
{
    for (int i = 0; i < static_cast<int>(a.size()); i++)
    {
        if (a[i].getNumerator() != 0)
        {
            return false;
        }
    }
    return true;
}

std::tuple<Matrix, Matrix, std::vector<int>, std::vector<int>> Matrix::getGramSchimdtQRDecomposition() const
{
    if (rows_ != cols_) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵不是方阵");
        return std::make_tuple(Matrix(1,1), Matrix(1,1), std::vector<int>(), std::vector<int>());
    }
    Matrix Q(*this);
    Matrix R(rows_, cols_);
    std::vector<int> pivotIndex;
    std::vector<int> nullIndex;
    for (int i = 0; i < cols_; ++i)
    {
        if (isZeroVector(Q.getColumn(i)))
        {
            nullIndex.push_back(i);
            continue;
        }
        pivotIndex.push_back(i);
        R.setEntry(pivotIndex.size() - 1, pivotIndex.size() - 1, Entry(1, 1));
        for(int k = 0;k<static_cast<int>(pivotIndex.size())-1;k++){
            R.setEntry(pivotIndex.size()-1, k, Entry(0, 1));
        }
        for (int j = i + 1; j < cols_; ++j)
        {
            Entry temp = getInnerProduct(Q.getColumn(i), Q.getColumn(j)) / norm(Q.getColumn(i));
            R.setEntry(pivotIndex.size() - 1, j, temp);
            for (int k = 0; k < rows_; k++)
            {
                Q.setEntry(k, j, Q.getEntry(k, j) - temp * Q.getEntry(k, i));
            }
        }
    }
    while (R.getRows() > static_cast<int>(pivotIndex.size()))
    {
        R.rowPopBack();
    }
    return {Q, R, pivotIndex, nullIndex};
}

EntryPolynomial Matrix::getCharacteristicPolynomial() const
{
    if (rows_ != cols_) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵不是方阵");
        return EntryPolynomial();
    }

    int n = rows_;
    // 创建一个多项式矩阵 A - λI
    std::vector<std::vector<EntryPolynomial>> polyMatrix(n, std::vector<EntryPolynomial>(n, EntryPolynomial({Entry(0, 1)})));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == j)
            {
                // 对角线元素为 A[i][i] - λ
                polyMatrix[i][j] = EntryPolynomial({data_[i][j], Entry(-1, 1)});
            }
            else
            {
                // 非对角线元素为 A[i][j]
                polyMatrix[i][j] = EntryPolynomial({data_[i][j]});
            }
        }
    }

    // 计算多项式矩阵的行列式
    return calculateDeterminant(polyMatrix);
}

// 计算多项式矩阵的行列式
EntryPolynomial Matrix::calculateDeterminant(const std::vector<std::vector<EntryPolynomial>> &polyMatrix) const
{
    int n = polyMatrix.size();
    if (n == 1)
    {
        return polyMatrix[0][0];
    }

    EntryPolynomial determinant({Entry(0, 1)});
    for (int col = 0; col < n; ++col)
    {
        std::vector<std::vector<EntryPolynomial>> subMatrix(n - 1, std::vector<EntryPolynomial>(n - 1));

        for (int subRow = 1; subRow < n; ++subRow)
        {
            int subColIndex = 0;
            for (int subCol = 0; subCol < n; ++subCol)
            {
                if (subCol == col)
                    continue;
                subMatrix[subRow - 1][subColIndex] = polyMatrix[subRow][subCol];
                subColIndex++;
            }
        }
        if(polyMatrix[0][col].getDegree()==0&&polyMatrix[0][col].getIthCoefficient(0).getNumerator()==0){
            continue;
        }
        EntryPolynomial subDeterminant = calculateDeterminant(subMatrix);

        EntryPolynomial cofactor = subDeterminant * polyMatrix[0][col];
        if (col % 2 == 0)
        {
            determinant = determinant + cofactor;
        }
        else
        {
            determinant = determinant - cofactor;
        }
    }
    if (determinant.getIthCoefficient(determinant.getDegree() - 1).getNumerator() == -1)
    {
        determinant = -determinant;
    }
    return determinant;
}

std::vector<std::pair<Entry, int>> Matrix::getEigenvalues() const
{
    return getCharacteristicPolynomial().solveRationalRoots();
}

Matrix Matrix::getOrthogonalEigenBasis(const std::vector<std::pair<Entry, int> >&eigenvalues) const
{
    if (rows_ != cols_) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵不是方阵");
        return Matrix(1, 1);
    }
    Matrix result(rows_, rows_);
    int generatedCount = 0;
    std::vector<std::pair<Entry, int>> eigenvaluesTodo = eigenvalues;
    while (eigenvaluesTodo.size() > 0)
    {
        Matrix temp = *this;
        Entry eigenvalue = eigenvaluesTodo.back().first;
        int count = eigenvaluesTodo.back().second;
        for (int i = 0; i < rows_; i++)
        {
            temp.setEntry(i, i, temp.getEntry(i, i) - eigenvalue);
        }
        auto decomp = temp.getGramSchimdtQRDecomposition();
        const Matrix& R = std::get<1>(decomp);
        const std::vector<int>& pivotIndex = std::get<2>(decomp);
        const std::vector<int>& nullIndex = std::get<3>(decomp);

        int rank = R.getRows();
        if (rank + count != rows_) {
            emit ErrorHandler::getInstance().errorOccurred("矩阵不可对角化");
            return Matrix(1, 1);
        }
        Matrix U(rank, rank);
        for (int i = 0; i < rank; i++)
        {
            for (int j = 0; j < rank; j++)
            {
                U.setEntry(i, j, R.getEntry(i, pivotIndex[j]));
            }
        }
        Matrix V = U.inverse();
        for (int i = 0; i < count; i++)
        {
            std::vector<Entry> pivotCoefficients = V.RightMultiplyVector(R.getColumn(nullIndex[i])); // 计算出主元列系数
            std::vector<Entry> eigenVector(rows_, Entry(0, 1));
            for (int j = 0; j < rank; j++)
            {
                eigenVector[pivotIndex[j]] = pivotCoefficients[j];
            }
            eigenVector[nullIndex[i]] = Entry(-1, 1);
            for (int k = 0; k < i; k++)
            {                

                Entry innerProduct = getInnerProduct(eigenVector, result.getColumn(generatedCount + k)); // G-S正交化
                for (int j = 0; j < rows_; j++)
                {
                    
                    eigenVector[j] = eigenVector[j] - innerProduct/norm(result.getColumn(generatedCount+k)) * result.getEntry(j, generatedCount + k);
                }
            }
            result.setColumn(generatedCount + i, eigenVector);
        }
        generatedCount += count; // 累加生成的特征向量个��
        eigenvaluesTodo.pop_back();
    }
    return result;
}

std::tuple<Matrix, Matrix, Matrix> Matrix::getSVDdecomposition() const
{
    Matrix A = *this;
    Matrix AT = getMatrixTranspose();
    Matrix ATA = AT.RightMultiply(A);
    Matrix AAT = A.RightMultiply(AT);
    Matrix V(ATA.getRows(), ATA.getCols());
    Matrix U(AAT.getRows(), AAT.getCols());
    Matrix Sigma(rows_, cols_);
    std::vector<std::pair<Entry, int>> eigenvalues1 = AAT.getEigenvalues();
    if(eigenvalues1.size()==0){
        return std::make_tuple(Matrix(1,1), Matrix(1,1), Matrix(1,1));
    }
    U = AAT.getOrthogonalEigenBasis(eigenvalues1);
    std::vector<std::pair<Entry, int>> eigenvalues2 = ATA.getEigenvalues();
    if(eigenvalues2.size()==0){
        return std::make_tuple(Matrix(1,1), Matrix(1,1), Matrix(1,1));
    }
    V = ATA.getOrthogonalEigenBasis(eigenvalues2);
    std::vector<std::pair<Entry, int>> eigenvalues = rows_ < cols_ ? eigenvalues1 : eigenvalues2;
    int pos = 0;

    for (int i = 0; i < static_cast<int>(eigenvalues.size()); i++)
    {
        Entry eigenvalue = eigenvalues[i].first;
        int count = eigenvalues[i].second;
        for (int j = 0; j < count; j++)
        {
            Sigma.setEntry(pos, pos, eigenvalue);
            pos++;
        }
        
    }
    return {U, Sigma, V};
}

int Matrix::getRank() const{
    Matrix temp = *this;
    int rank = 0;
    for(int i = 0;i<rows_;i++){

        if(isZeroVector(temp.getRow(i))){
            continue;
        }
        for(int j = i+1;j<rows_;j++){
            Entry innerProduct = getInnerProduct(temp.getRow(i),temp.getRow(j));
            if(innerProduct.getNumerator()==0){
            }
            for(int k = 0;k<cols_;k++){
                temp.setEntry(j,k,temp.getEntry(j,k)-innerProduct/norm(temp.getRow(i))*temp.getEntry(i,k));
            }
        }
        rank++;

    }
    
    return rank;
}

Matrix Matrix::getJordanForm() const
{
    if (rows_ != cols_) {
        emit ErrorHandler::getInstance().errorOccurred("矩阵不是方阵");
        return Matrix(1, 1);
    }
    Matrix result(rows_,cols_);
    std::vector<std::pair<Entry,int>> eigenvalues = getEigenvalues();
    if(eigenvalues.size()==0){
        return Matrix(1,1);
    }
    int currentCol = 0;
    while(eigenvalues.size()>0){
        Entry eigenvalue = eigenvalues.back().first;
        int count = eigenvalues.back().second;
        std::vector<int> blockSize;
        Matrix temp = *this;
        for(int i = 0;i<rows_;i++){
            for(int j = 0;j<cols_;j++){
                if(i == j){
                    temp.setEntry(i,j,temp.getEntry(i,j)-eigenvalue);                    
                }
                else{
                    temp.setEntry(i,j,temp.getEntry(i,j));
                }
            }
        }
        Matrix Product = temp;
        int geometricMultiplicity = rows_ - Product.getRank();

        for(int i = 0; i<geometricMultiplicity;i++){
            blockSize.push_back(1);
        }
        while(geometricMultiplicity<count){
            Product = Product.RightMultiply(temp);
            int NewGeometricMultiplicity = rows_ - Product.getRank();
            for(int i = 0;i<NewGeometricMultiplicity-geometricMultiplicity;i++){
                blockSize[i]++;
            }
            geometricMultiplicity = NewGeometricMultiplicity;
        }
        for(int i = 0;i<blockSize.size();i++){
            for(int j = 0;j<blockSize[i];j++){
                result.setEntry(currentCol,currentCol,eigenvalue);
                if(j > 0){
                    result.setEntry(currentCol-1,currentCol,Entry(1,1));
                }
                currentCol++;
            }
        }
        eigenvalues.pop_back();
    }
    return result;
}