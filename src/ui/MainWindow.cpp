#include "MainWindow.h"
#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <iostream>
#include <QApplication>
#include <unistd.h>
#include <string>
#include <sstream>
#include <limits>
#include <thread>
#include <chrono>
#include <vector>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget); // 使用水平布局
    operationWidget_ = std::make_shared<OperationWidget>(this);
    //boardWidget_ = std::make_shared<BoardWidget>(3, 3, this); // 创建 3x3 的棋盘
    //mainLayout->addWidget(boardWidget_.get()); 
    mainLayout->addWidget(operationWidget_.get()); 
    setCentralWidget(centralWidget);
    setupUi();
    setWindowTitle("矩 阵 计 算 器"); // 设置窗口标题

    // 连接 OperationWidget 的信号到 MainWindow 的槽

    connect(operationWidget_.get(), &OperationWidget::startRequested, this, &MainWindow::handleStart);
    connect(operationWidget_.get(), &OperationWidget::backRequested, this, &MainWindow::handleBack);
    connect(operationWidget_.get(), &OperationWidget::iostreamInputMatrixRequested, this, &MainWindow::handleIostreamInputMatrix);
    connect(operationWidget_.get(), &OperationWidget::fileInputMatrixRequested, this, &MainWindow::handleFileInputMatrix);
    connect(operationWidget_.get(), &OperationWidget::luDecompositionRequested, this, &MainWindow::handleLuDecomposition);
    connect(operationWidget_.get(), &OperationWidget::inverseRequested, this, &MainWindow::handleInverse);
    connect(operationWidget_.get(), &OperationWidget::determinantRequested, this, &MainWindow::handleDeterminant);
    connect(operationWidget_.get(), &OperationWidget::qrDecompositionRequested, this, &MainWindow::handleQrDecomposition);
    connect(operationWidget_.get(), &OperationWidget::svdDecompositionRequested, this, &MainWindow::handleSvdDecomposition);
    connect(operationWidget_.get(), &OperationWidget::jordanFormRequested, this, &MainWindow::handleJordanForm);
    connect(operationWidget_.get(), &OperationWidget::backRequested, this, &MainWindow::handleBack);
    connect(operationWidget_.get(), &OperationWidget::boxInputMatrixRequested, this, &MainWindow::handleBoxInputMatrix);    

}

void MainWindow::handleStart(){
    operationWidget_->hideStartButton();
    operationWidget_->showInputButtons();
    operationWidget_->hideFunctionButtons();
}

void MainWindow::setupUi(){

    operationWidget_->hideFunctionButtons();
    operationWidget_->hideInputButtons();

    // 连接 back 按钮的信号
}

// 槽函数实现
void MainWindow::handleLuDecomposition() {
    operationWidget_->hideFunctionButtons();
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    // 使用用户输入的矩阵进行 PLU 分解
    auto [P, L, U] = matrix_->pluDecomposition(); // 调用 PLU 分解

    // 获取 centralWidget 的现有布局
    auto centralWidget = this->centralWidget();
    auto layout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    if (!layout) {
        layout = new QHBoxLayout(centralWidget);
        centralWidget->setLayout(layout);
    }

    QApplication::processEvents(); // 更新界面

    // 显示 P 矩阵
    pWidget_ = std::make_shared<BoardWidget>(P.getRows(), P.getCols(), this);
    pWidget_->setMatrix(P);

    // 创建一个 QLabel 显示等号
    QLabel* equalsLabel = new QLabel("=", this);
    equalsLabel->setAlignment(Qt::AlignCenter);
    equalsLabel->setFixedSize(20, 50); // 设置等号的大小

    layout->addWidget(equalsLabel); // 添加等号到布局
    layout->addWidget(pWidget_.get()); // 添加 P 矩阵到布局
    QApplication::processEvents(); // 更新界面

    // 显示 L 矩阵
    lWidget_ = std::make_shared<BoardWidget>(L.getRows(), L.getCols(), this);
    lWidget_->setMatrix(L);
    layout->addWidget(lWidget_.get());
    QApplication::processEvents(); // 更新界面

    // 显示 U 矩阵
    uWidget_ = std::make_shared<BoardWidget>(U.getRows(), U.getCols(), this);
    uWidget_->setMatrix(U);
    layout->addWidget(uWidget_.get());
    QApplication::processEvents(); // 更新界面
}

void MainWindow::handleInverse() {
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    if(matrix_->getRows() != matrix_->getCols()){
        QMessageBox::warning(this, "输入错误", "请输入方阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    if(matrix_->getDeterminant() == Entry(0, 1)){
        QMessageBox::warning(this, "输入错误", "请输入非奇异矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }

    Matrix inv = matrix_->inverse();
    invWidget_ = std::make_shared<BoardWidget>(inv.getRows(), inv.getCols(), this);
    invWidget_->setMatrix(inv);

    // 获取 centralWidget 的现有布局
    auto centralWidget = this->centralWidget();
    auto layout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    if (!layout) {
        layout = new QHBoxLayout(centralWidget);
        centralWidget->setLayout(layout);
    }

    

    layout->addWidget(invWidget_.get());

    QLabel* equalsLabel = new QLabel("=", this);
    equalsLabel->setAlignment(Qt::AlignCenter);
    equalsLabel->setFixedSize(20, 50);
    layout->addWidget(equalsLabel);

    Matrix idMatrix(matrix_->getRows(), matrix_->getCols());
    idMatrix.identity(); // 确保 IdMatrix 是单位矩阵

    idWidget_ = std::make_shared<BoardWidget>(idMatrix.getRows(), idMatrix.getCols(), this);
    idWidget_->setMatrix(idMatrix);
    layout->addWidget(idWidget_.get());



    QApplication::processEvents(); // 更新界面

    // 输出布局中部件的数量
}

void MainWindow::handleDeterminant() {
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    if(matrix_->getRows() != matrix_->getCols()){
        QMessageBox::warning(this, "输入错误", "请输入方阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    Entry det = matrix_->getDeterminant();
    Matrix detMatrix(1, 1);
    detMatrix.setEntry(0, 0, det);
    auto centralWidget = this->centralWidget();
    auto layout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    if (!layout) {
        layout = new QHBoxLayout(centralWidget);
        centralWidget->setLayout(layout);
    }
    QLabel* equalsLabel = new QLabel("=", this);
    equalsLabel->setAlignment(Qt::AlignCenter);
    equalsLabel->setFixedSize(20, 50); // 设置等号的大小
    detWidget_ = std::make_shared<BoardWidget>(1, 1, this);
    detWidget_->setMatrix(detMatrix);
    layout->addWidget(equalsLabel);
    layout->addWidget(detWidget_.get());
    QApplication::processEvents(); // 更新界面
    // 计算行列式的逻辑
    
}

void MainWindow::handleQrDecomposition() {
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    auto [Q, R] = matrix_->qrDecomposition();
    std::vector<Entry> norms;
    std::vector<Entry> norms_inv;
    for (int i = 0; i < Q.getRows(); i++)
    {
        Entry norm = Entry(0,1);
        for (int j = 0; j < Q.getCols(); j++)
        {
            norm = norm + Q.getEntry(i, j)*Q.getEntry(i, j);
        }
        if(norm.getNumerator() != 0){
            norms.push_back(norm);
            norms_inv.push_back(Entry(norm.getDenominator(), norm.getNumerator()));
        }
        else{
            QMessageBox::warning(this, "系统错误", "系统不能处理该矩阵", QMessageBox::Ok);
            handleBack();
            return;
        }
    }
    
    qWidget_ = std::make_shared<BoardWidget>(Q.getRows(), Q.getCols(), this);
    qWidget_->setMatrixWithSquareroot(Q, norms_inv);
    rWidget_ = std::make_shared<BoardWidget>(R.getRows(), R.getCols(), this);
    rWidget_->setMatrixWithSquareroot(R, norms);
    rWidget_->setMatrix(R);

    
    
}

void MainWindow::handleSvdDecomposition() {
    // 执行 SVD 分解的逻辑
}

void MainWindow::handleJordanForm() {
    // 计算 Jordan 标准型的逻辑
}

// 实现 handleBack 槽函数
void MainWindow::handleBack() {
    operationWidget_->showStartButton();
    boardWidget_=nullptr;
    detWidget_=nullptr;
    pWidget_=nullptr;
    lWidget_=nullptr;
    uWidget_=nullptr;
    invWidget_=nullptr;
    idWidget_=nullptr;
    matrix_=nullptr;

    setupUi();



}
void MainWindow::handleFileInputMatrix() {
    operationWidget_->hideInputButtons();
    operationWidget_->showFunctionButtons();
    QMessageBox::information(this,"文件输入","读取矩阵信息完毕",QMessageBox::Ok);



}
void MainWindow::handleBoxInputMatrix() {
    operationWidget_->hideStartButton();
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
            handleBack();
            return; // 退出函数，等待用户重新输入
        }

        // 建 BoardWidget 并添加到布局
        boardWidget_ = std::make_shared<BoardWidget>(rows, cols, this);
        auto centralWidget = this->centralWidget();
        auto mainLayout = centralWidget->layout();
        mainLayout->addWidget(boardWidget_.get()); // 将 boardWidget 添加到布局中
        QApplication::processEvents(); // 处理事件，更新界面
        
        // 使用 make_shared 创建 Matrix 实例
        matrix_ = std::make_shared<Matrix>(rows, cols);

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                bool ok2;
                QString input = QInputDialog::getText(this, "输入矩阵元素", QString("请输入第 %1 行第 %2 列的元素:").arg(i + 1).arg(j + 1), QLineEdit::Normal, "", &ok2);
                if (ok2) {
                    if (input.isEmpty()) {
                        QMessageBox::warning(this, "输入错误", "输入不能为空，请重新输入。", QMessageBox::Ok);
                        j--; // 重新输入当前元素
                        continue; // 跳过当前循环，等待用户重新输入
                    }

                    // 检查输入是否为分数
                    if (input.contains("/")) {
                        QStringList parts = input.split("/");
                        if (parts.size() != 2) {
                            QMessageBox::warning(this, "输入错误", "分数格式不正确，请输入如 'a/b' 的格式。", QMessageBox::Ok);
                            j--;
                            continue; // 跳过当前循环，等待用户重新输入
                        }

                        bool numeratorOk, denominatorOk;
                        long long numerator = parts[0].toLongLong(&numeratorOk);
                        long long denominator = parts[1].toLongLong(&denominatorOk);

                        if (!numeratorOk || !denominatorOk || denominator == 0) {
                            QMessageBox::warning(this, "输入错误", "分母不能为0，请重新输入。", QMessageBox::Ok);
                            j--;
                            continue; // 跳过当前循环，等待用户重新输入
                        }

                        matrix_->setEntry(i, j, Entry(numerator, denominator)); // 使用 setEntry 方法设置矩阵元素
                    } else {
                        // 只输入一个数，视为整数
                        bool integerOk;
                        long long numerator = input.toLongLong(&integerOk);
                        if (!integerOk) {
                            QMessageBox::warning(this, "输入错误", "请输入有效的整数。", QMessageBox::Ok);
                            j--;
                            continue; // 跳过当前循环，等待用户重新输入
                        }

                        matrix_->setEntry(i, j, Entry(numerator, 1)); // 分母设为1
                    }
                    // 每次输入后更新 BoardWidget
                    boardWidget_->setMatrix(*matrix_); // 更新 BoardWidget 显示矩阵
                } else {
                    // 弹出对话框询问用户是否退出
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "输入流", "读取输入矩阵信息失败，是否退出？", QMessageBox::Yes | QMessageBox::No);
                    if (reply == QMessageBox::Yes) {
                        boardWidget_ = nullptr; // 将指针设置为 nullptr，避免悬空指针
                        handleBack();
                        return; // 用户选择退出
                    } else {
                        j--;
                        continue; // 重新输入当前元素
                    }
                }
            }
        }

        QMessageBox::information(this, "输入流", "读取输入矩阵信息完毕", QMessageBox::Ok);
        operationWidget_->hideInputButtons();
        operationWidget_->showFunctionButtons();
    }
    else{
        handleBack();
        return;
    }
}
void MainWindow::handleIostreamInputMatrix() {
    operationWidget_->hideStartButton();

    std::string input;
    int rows, cols;

    while (true) {
        std::cout << "请输入矩阵的行数和列数（用空格分隔）: ";
        std::getline(std::cin, input); // 读取整行输入

        std::istringstream iss(input);
        if (iss >> rows >> cols) { // 尝试将输入转换为整数
            if (rows > 0 && cols > 0) {
                break; // 输入有效，退出循环
            }
        }

        std::cout << "输入错误: 请输入有效的行数和列数（必须为正整数）" << std::endl;
        std::cout << "输入 1 退出，输入 2 重试: ";
        int choice;
        std::getline(std::cin, input); // 读取用户选择
        std::istringstream choiceStream(input);
        if (choiceStream >> choice) {
            if (choice == 1) {
                handleBack();
                return; // 退出函数
            } else if (choice != 2) {
                std::cout << "无效输入，请重新输入。" << std::endl;
            }
        } else {
            std::cout << "无效输入，请重新输入。" << std::endl;
        }
    }

    // 创建 BoardWidget 并添加到布局

    boardWidget_ = std::make_shared<BoardWidget>(rows, cols, this);
    auto centralWidget = this->centralWidget();
    auto mainLayout = centralWidget->layout();
    mainLayout->addWidget(boardWidget_.get()); // 将 boardWidget 添加到布局中
    std::this_thread::sleep_for(std::chrono::milliseconds(500));    
    QApplication::processEvents(); // 处理事件，更新界面
    QApplication::processEvents(); // 处理事件，更新界面

    // 创建一个 Matrix 实例
    Matrix matrix(rows, cols); // 使用原构造函数创建 Matrix 实例


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
                while (true)
                {
                
                std::cout << QString("请输入第 %1 行第 %2 列的元素:").arg(i + 1).arg(j + 1).toStdString();
                std::string input;
                std::cin >> input;
                std::cout<<std::endl;
                if (input.empty()) {
                    std::cout << "输入错误: 输入不能为空，请重新输入。" << std::endl;
                    j--;
                    continue; // 跳过当前环，等待用户重新输入
                }
                
                

                // 检查输入是否为分数
                if (input.find("/") != std::string::npos) {
                    QStringList parts = QString::fromStdString(input).split("/");
                    if (parts.size() != 2) {
                        std::cout << "输入错误: 分数格式不正确，请输入如 'a/b' 的格式。" << std::endl;
                    } else {
                        bool numeratorOk, denominatorOk;
                        long long numerator = parts[0].toLongLong(&numeratorOk);
                        long long denominator = parts[1].toLongLong(&denominatorOk);

                        if (numeratorOk && denominatorOk && denominator != 0) {
                            matrix.setEntry(i, j, Entry(numerator, denominator)); // 使用 setEntry 方法设置矩阵元素
                            boardWidget_->setMatrix(matrix); // 更新 BoardWidget 显示矩阵
                            QApplication::processEvents(); // 处理事件，更新界面
                            break; // 输入有效，退出循环
                        } else {
                            std::cout << "输入错误: 分母不能为0，请重新输入。" << std::endl;
                        }
                    }
                } else {
                    // 只输入一数，视为整数
                    bool integerOk;
                    long long numerator = QString::fromStdString(input).toLongLong(&integerOk);
                    if (integerOk) {
                        matrix.setEntry(i, j, Entry(numerator, 1)); // 分母设为1
                        boardWidget_->setMatrix(matrix); // 更新 BoardWidget 显示矩阵
                        QApplication::processEvents(); // 处理事件，更新界面
                        break; // 输入有效，退出循环
                    } else {
                        std::cout << "输入错误: 请输入有效的整数。" << std::endl;
                        
                    }
                


            }
                std::cout << "输入 1 退出，输入 2 重试: ";
                int choice;
                std::cin >> choice;

                std::cout<<std::endl;
                if (choice == 1) {
                    
                    handleBack();
                    return; // 退出函数
                } else if (choice != 2) {
                    std::cout << "无效输入，请重新输入。" << std::endl;
                }
            }
        }
    }

    std::cout << "读取输入矩阵信息完毕" << std::endl;
    operationWidget_->hideInputButtons();
    operationWidget_->showFunctionButtons();
}
