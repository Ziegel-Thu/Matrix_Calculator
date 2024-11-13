#include "BoardWidget.h"

BoardWidget::BoardWidget(int rows, int cols, QWidget *parent)
    : QWidget(parent), rows_(rows), cols_(cols) {
    gridLayout_ = new QGridLayout(this);
    labels_.resize(rows, std::vector<QLabel*>(cols, nullptr));

    // 初始化每个格子
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            labels_[i][j] = new QLabel("  ", this); // 默认显示空白
            labels_[i][j]->setAlignment(Qt::AlignCenter);
            labels_[i][j]->setStyleSheet("border: 1px dashed black;"); // 设置空心虚线边框
            labels_[i][j]->setFixedSize(50, 50); // 设置固定大小为 50x50 像素
            gridLayout_->addWidget(labels_[i][j], i, j);
        }
    }

    setLayout(gridLayout_);
}

void BoardWidget::setMatrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.getRows(); ++i) {
        for (int j = 0; j < matrix.getCols(); ++j) {
            if (matrix.hasValue(i, j)) {
                Entry entry = matrix.getEntry(i, j);
                QString text;
                if (entry.getDenominator() == 1) {
                    text = QString::number(entry.getNumerator());
                } else {
                    text = QString("%1/%2").arg(entry.getNumerator()).arg(entry.getDenominator());
                }
                labels_[i][j]->setText(text);
            } else {
                labels_[i][j]->setText("");
            }
        }
    }
}


