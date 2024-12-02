#include "BoardWidget.h"
#include <iostream>
BoardWidget::BoardWidget(int rows, int cols, QWidget *parent)
    : QWidget(parent), rows_(rows), cols_(cols)
{
    gridLayout_ = new QGridLayout(this);
    labels_.resize(rows, std::vector<QLabel *>(cols, nullptr));

    // 初始化每个格子
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            labels_[i][j] = new QLabel("  ", this); // 默认显示空白
            labels_[i][j]->setAlignment(Qt::AlignCenter);
            labels_[i][j]->setStyleSheet("border: 1px dashed black;"); // 设置空心虚线边框
            labels_[i][j]->setFixedSize(100, 50);                      // 设置固定大小为 50x50 像素
            gridLayout_->addWidget(labels_[i][j], i, j);
        }
    }

    setLayout(gridLayout_);
}

BoardWidget::~BoardWidget()
{
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            delete labels_[i][j];
        }
    }
    delete gridLayout_;
}

void BoardWidget::setMatrix(const Matrix &matrix)
{
    for (int i = 0; i < matrix.getRows(); ++i)
    {
        for (int j = 0; j < matrix.getCols(); ++j)
        {
            if (matrix.hasValue(i, j))
            {
                Entry entry = matrix.getEntry(i, j);
                QString text;
                if (entry.getDenominator() == 1)
                {
                    text = QString::number(entry.getNumerator());
                }
                else
                {
                    text = QString("%1/%2").arg(entry.getNumerator()).arg(entry.getDenominator());
                }
                labels_[i][j]->setText(text);
            }
            else
            {
                labels_[i][j]->setText("");
            }
        }
    }
}

void BoardWidget::setMatrixWithSquarerootLeft(const std::vector<Entry> &norms,const Matrix &matrix)//等效于左乘对角阵
{
    for (int i = 0; i < matrix.getRows(); ++i)
    {
        Entry norm = norms[i];
        if (norm.getNumerator() == 0)
        {
            for (int j = 0; j < matrix.getCols(); j++)
            {
                labels_[i][j]->setText("0");
            }
        }
        else
        {
            std::pair<Entry, long long> result = norm.getSquareroot();
            for (int j = 0; j < matrix.getCols(); ++j)
            {
                if (matrix.hasValue(i, j))
                {
                    Entry entry = matrix.getEntry(i, j);
                    entry = entry * result.first;
                    long long root = result.second;
                    QString text;
                    if (entry.getNumerator() == 0)
                    {
                        text = QString("0");
                    }
                    else if (root == 1)
                    {
                        if (entry.getDenominator() == 1)
                        {
                            text = QString::number(entry.getNumerator());
                        }
                        else
                        {
                            text = QString("%1/%2").arg(entry.getNumerator()).arg(entry.getDenominator());
                        }
                    }
                    else
                    {
                        if (entry.getDenominator() == 1)
                        {
                            if (entry.getNumerator() == 1)
                            {
                                text = QString("√%1").arg(root);
                            }
                            else
                            {
                                text = QString("%1√%2").arg(entry.getNumerator()).arg(root);
                            }
                        }
                        else
                        {
                            text = QString("%1/%2√%3").arg(entry.getNumerator()).arg(entry.getDenominator()).arg(root);
                        }
                    }
                    labels_[i][j]->setText(text);
                }
                else
                {
                    labels_[i][j]->setText("");
                }
            }
        }
    }
}
void BoardWidget::setMatrixWithSquarerootRight(const Matrix &matrix,const std::vector<Entry>& norms)//等效于右乘对角阵
{
    for (int j = 0; j < matrix.getCols(); ++j)
    {
        Entry norm = norms[j];
        if (norm.getNumerator() == 0)
        {
            for (int i = 0; i < matrix.getRows(); ++i)
            {
                labels_[i][j]->setText("0");
            }
        }
        else
        {
            std::pair<Entry, long long> result = norm.getSquareroot();
            for (int i = 0; i < matrix.getRows(); ++i)
            {
                if (matrix.hasValue(i, j))
                {
                    Entry entry = matrix.getEntry(i, j);
                    entry = entry * result.first;
                    long long root = result.second;
                    QString text;
                    if (entry.getNumerator() == 0)
                    {
                        text = QString("0");
                    }
                    else if (root == 1)
                    {
                        if (entry.getDenominator() == 1)
                        {
                            text = QString::number(entry.getNumerator());
                        }
                        else
                        {
                            text = QString("%1/%2").arg(entry.getNumerator()).arg(entry.getDenominator());
                        }
                    }
                    else
                    {
                        if (entry.getDenominator() == 1)
                        {
                            if (entry.getNumerator() == 1)
                            {
                                text = QString("√%1").arg(root);
                            }
                            else
                            {
                                text = QString("%1√%2").arg(entry.getNumerator()).arg(root);
                            }
                        }
                        else
                        {
                            text = QString("%1/%2√%3").arg(entry.getNumerator()).arg(entry.getDenominator()).arg(root);
                        }
                    }
                    labels_[i][j]->setText(text);
                }
                else
                {
                    labels_[i][j]->setText("");
                }
            }
        }
    }
}
void BoardWidget::setTransposeMatrixWithSquarerootRight(const Matrix &matrix,const std::vector<Entry>& norms)//等效于"右乘对角阵"的转置
{
    for (int j = 0; j < matrix.getCols(); j++)
    {
        Entry norm = norms[j];
        if (norm.getNumerator() == 0)
        {
            for (int i = 0; i < matrix.getRows(); ++i)
            {
                labels_[j][i]->setText("0");
            }
        }
        else
        {
            std::pair<Entry, long long> result = norm.getSquareroot();
            for (int i = 0; i < matrix.getRows(); ++i)
            {
                if (matrix.hasValue(i, j))
                {
                    Entry entry = matrix.getEntry(i, j);
                    entry = entry * result.first;
                    long long root = result.second;
                    QString text;
                    if (entry.getNumerator() == 0)
                    {
                        text = QString("0");
                    }
                    else if (root == 1)
                    {
                        if (entry.getDenominator() == 1)
                        {
                            text = QString::number(entry.getNumerator());
                        }
                        else
                        {
                            text = QString("%1/%2").arg(entry.getNumerator()).arg(entry.getDenominator());
                        }
                    }
                    else
                    {
                        if (entry.getDenominator() == 1)
                        {
                            if (entry.getNumerator() == 1)
                            {
                                text = QString("√%1").arg(root);
                            }
                            else
                            {
                                text = QString("%1√%2").arg(entry.getNumerator()).arg(root);
                            }
                        }
                        else
                        {
                            text = QString("%1/%2√%3").arg(entry.getNumerator()).arg(entry.getDenominator()).arg(root);
                        }
                    }
                    labels_[j][i]->setText(text);
                }
                else
                {
                    labels_[j][i]->setText("");
                }
            }
        }
    }
}

void BoardWidget::setMatrixWithSVD(const Matrix &matrix)
{
    for (int i = 0; i < matrix.getRows(); i++)
    {
        for (int j = 0; j < matrix.getCols(); j++)
        {
            if (matrix.hasValue(i, j))
            {
                Entry norm = matrix.getEntry(i,j);
                std::pair<Entry, long long> result = norm.getSquareroot();
                Entry entry = Entry(1, 1);
                entry = entry * result.first;
                long long root = result.second;
                QString text;
                if (entry.getNumerator() == 0||root == 0)
                {
                    text = QString("0");
                }
                else if (root == 1)
                {
                    if (entry.getDenominator() == 1)
                    {
                        text = QString::number(entry.getNumerator());
                    }
                    else
                    {
                        text = QString("%1/%2").arg(entry.getNumerator()).arg(entry.getDenominator());
                    }
                }
                else
                {
                    if (entry.getDenominator() == 1)
                    {
                        if (entry.getNumerator() == 1)
                        {
                            text = QString("√%1").arg(root);
                        }
                        else
                        {
                            text = QString("%1√%2").arg(entry.getNumerator()).arg(root);
                        }
                    }
                    else
                    {
                        text = QString("%1/%2√%3").arg(entry.getNumerator()).arg(entry.getDenominator()).arg(root);
                    }
                }
                labels_[i][j]->setText(text);
            }
            else
            {
                labels_[i][j]->setText("");
            }
        }
    }
}
