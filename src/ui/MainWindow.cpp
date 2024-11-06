#include "MainWindow.h"
#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    setWindowTitle("矩 阵 计 算 器"); // 设置窗口标题

    // 连接 OperationWidget 的信号到 MainWindow 的槽
    connect(operationWidget_.get(), &OperationWidget::iostreamInputMatrixRequested, this, &MainWindow::handleIostreamInputMatrix);
    connect(operationWidget_.get(), &OperationWidget::fileInputMatrixRequested, this, &MainWindow::handleFileInputMatrix);
    connect(operationWidget_.get(), &OperationWidget::luDecompositionRequested, this, &MainWindow::handleLuDecomposition);
    connect(operationWidget_.get(), &OperationWidget::inverseRequested, this, &MainWindow::handleInverse);
    connect(operationWidget_.get(), &OperationWidget::determinantRequested, this, &MainWindow::handleDeterminant);
    connect(operationWidget_.get(), &OperationWidget::qrDecompositionRequested, this, &MainWindow::handleQrDecomposition);
    connect(operationWidget_.get(), &OperationWidget::svdDecompositionRequested, this, &MainWindow::handleSvdDecomposition);
    connect(operationWidget_.get(), &OperationWidget::jordanFormRequested, this, &MainWindow::handleJordanForm);
}

void MainWindow::setupUi(){
    auto centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget); // 使用水平布局
    operationWidget_ = std::make_shared<OperationWidget>(this);
    //boardWidget_ = std::make_shared<BoardWidget>(3, 3, this); // 创建 3x3 的棋盘
    //mainLayout->addWidget(boardWidget_.get()); 
    mainLayout->addWidget(operationWidget_.get()); 
    operationWidget_->hideFunctionButtons();
    operationWidget_->hideInputButtons();
    setCentralWidget(centralWidget);

    // 连接 back 按钮的信号
    connect(operationWidget_->back_.get(), &QPushButton::clicked, this, &MainWindow::handleBack);
}
//void MainWindow::startHandle(){
    //operationWidget_->hideFunctionButtons();
    //operationWidget_->hideInputButtons();

//}
// 槽函数实现
void MainWindow::handleLuDecomposition() {

    
}

void MainWindow::handleInverse() {
    // 执行求逆的逻辑
    
}

void MainWindow::handleDeterminant() {
    // 计算行列式的逻辑
}

void MainWindow::handleQrDecomposition() {
    // 执行 QR 分解的逻辑
}

void MainWindow::handleSvdDecomposition() {
    // 执行 SVD 分解的逻辑
}

void MainWindow::handleJordanForm() {
    // 计算 Jordan 标准型的逻辑
}

// 实现 handleBack 槽函数
void MainWindow::handleBack() {
    setupUi();


}
void MainWindow::handleFileInputMatrix() {
    operationWidget_->hideInputButtons();
    operationWidget_->showFunctionButtons();
    QMessageBox::information(this,"文件输入","读取矩阵信息完毕",QMessageBox::Ok);



}
void MainWindow::handleIostreamInputMatrix() {



    // 使用 QInputDialog 获取矩阵的大小
    bool ok;
    QString sizeInput = QInputDialog::getText(this, "输入矩阵大小", "请输入矩阵的行数和列数（用空格分隔）:", QLineEdit::Normal, "", &ok);

    if (ok && !sizeInput.isEmpty()) {
        QStringList sizes = sizeInput.split(" ");
        bool rowsOk, colsOk;
        int rows = sizes[0].toInt(&rowsOk);
        int cols = sizes[1].toInt(&colsOk);

        if (!rowsOk || !colsOk || rows <= 0 || cols <= 0) {
            QMessageBox::warning(this, "输入错误", "请输入有效的行数和列数（必须为正整数）", QMessageBox::Ok);
            return; // 退出函数，等待用户重新输入
        }

        // 创建一个矩阵并读取元素
        std::vector<std::vector<Entry>> matrix(rows, std::vector<Entry>(cols, Entry(0, 1)));
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                bool ok2;
                QString input = QInputDialog::getText(this, "输入矩阵元素", QString("请输入第 %1 行第 %2 列的元素:").arg(i + 1).arg(j + 1), QLineEdit::Normal, "", &ok2);
                if (ok2) {
                    if (input.isEmpty()) {
                        // 处理只输入一个数的情况
                        // 这里可以添加对空输入的处理
                        QMessageBox::warning(this, "输入错误", "输入不能为空，请重新输入。", QMessageBox::Ok);
                        j--; // 重新输入当前元素
                        continue; // 跳过当前循环，等待用户重新输入
                    }

                    // 检查输入是否为分数
                    if (input.contains("/")) {
                        QStringList parts = input.split("/");
                        if (parts.size() != 2) {
                            QMessageBox::warning(this, "输入错误", "分数格式不正确，请输入如 'a/b' 的格式。", QMessageBox::Ok);
                            j--; // 重新输入当前元素
                            continue; // 跳过当前循环，等待用户重新输入
                        }

                        bool numeratorOk, denominatorOk;
                        long long numerator = parts[0].toLongLong(&numeratorOk);
                        long long denominator = parts[1].toLongLong(&denominatorOk);

                        if (!numeratorOk || !denominatorOk || denominator == 0) {
                            QMessageBox::warning(this, "输入错误", "分母不能为0，请重新输入。", QMessageBox::Ok);
                            j--; // 重新输入当前元素
                            continue; // 跳过当前循环，等待用户重新输入
                        }

                        matrix[i][j] = Entry(numerator, denominator);
                    } else {
                        // 只输入一个数，视为整数
                        bool integerOk;
                        long long numerator = input.toLongLong(&integerOk);
                        if (!integerOk) {
                            QMessageBox::warning(this, "输入错误", "请输入有效的整数。", QMessageBox::Ok);
                            j--; // 重新输入当前元素
                            continue; // 跳过当前循环，等待用户重新输入
                        }
                        long long denominator = 1; // 分母设为1
                        matrix[i][j] = Entry(numerator, denominator);
                    }
                } else {
                    // 弹出对话框询问用户是否退出
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "输入流", "读取输入矩阵信息失败，是否退出？", QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::Yes) {
                        return; // 用户选择退出
                    } else {
                        j--; // 重新输入当前元素
                    }
                }
            }
        }

        QMessageBox::information(this, "输入流", "读取输入矩阵信息完毕", QMessageBox::Ok);
        operationWidget_->hideInputButtons();
        operationWidget_->showFunctionButtons();
    }
}