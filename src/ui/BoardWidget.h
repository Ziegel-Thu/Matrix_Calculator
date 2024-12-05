#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "../core/Matrix.h" // 引入 Matrix 类

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    BoardWidget(int rows, int cols, QWidget *parent = nullptr);
    ~BoardWidget();
    void setMatrix(const Matrix& matrix); // 设置矩阵并更新显示
    void setMatrixWithSquarerootLeft(const std::vector<Entry>& norms,const Matrix& matrix); 
    void setMatrixWithSquarerootRight(const Matrix& matrix,const std::vector<Entry>& norms); 
    void setTransposeMatrixWithSquarerootRight(const Matrix& matrix,const std::vector<Entry>& norms); 
    void setMatrixWithSVD(const Matrix& matrix); 

private:
    int rows_; // 行数
    int cols_; // 列数
    QGridLayout *gridLayout_; // 网格布局
    std::vector<std::vector<QLabel*>> labels_; // 存储每个格子的 QLabel
};
