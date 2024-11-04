#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "Matrix.h" // 引入 Matrix 类

class BoardWidget : public QWidget {
    Q_OBJECT
public:
    BoardWidget(int rows, int cols, QWidget *parent = nullptr);

    void setMatrix(const Matrix& matrix); // 设置矩阵并更新显示

private:
    int rows_; // 行数
    int cols_; // 列数
    QGridLayout *gridLayout_; // 网格布局
    std::vector<std::vector<QLabel*>> labels_; // 存储每个格子的 QLabel
};
