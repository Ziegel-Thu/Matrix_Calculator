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
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include "ErrorHandler.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    auto centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget); // 使用水平布局
    operationWidget_ = std::make_shared<OperationWidget>(this);
    mainLayout->addWidget(operationWidget_.get()); 
    setCentralWidget(centralWidget);
    setupUi();
    setWindowTitle("矩 阵 计 算 器"); // 设置窗口标题

    // 连接错误处理器
    connect(&ErrorHandler::getInstance(), &ErrorHandler::errorOccurred,
            this, [this](const QString& message) {
                QMessageBox::warning(this, "错误", message, QMessageBox::Ok);
                handleBack();
            });

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
    // 根据内容自动调整大小
    adjustSize();
    // 设置尺寸策略为首选大小
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    operationWidget_->hideFunctionButtons();
    operationWidget_->hideInputButtons();
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
    permutationWidget_ = std::make_shared<BoardWidget>(P.getRows(), P.getCols(), this);
    permutationWidget_->setMatrix(P);

    // 创建一个 QLabel 显示等号
    equalsLabel_ = std::make_shared<QLabel>("=", this);
    equalsLabel_->setAlignment(Qt::AlignCenter);
    equalsLabel_->setFixedSize(20, 50); // 设置等号的大小

    layout->addWidget(equalsLabel_.get()); // 添加等号到布局
    layout->addWidget(permutationWidget_.get()); // 添加 P 矩阵到布局
    QApplication::processEvents(); // 更新界面

    // 显示 L 矩阵
    lowerWidget_ = std::make_shared<BoardWidget>(L.getRows(), L.getCols(), this);
    lowerWidget_->setMatrix(L);
    layout->addWidget(lowerWidget_.get());
    QApplication::processEvents(); // 更新界面

    // 显示 U 矩阵
    upperWidget_ = std::make_shared<BoardWidget>(U.getRows(), U.getCols(), this);
    upperWidget_->setMatrix(U);
    layout->addWidget(upperWidget_.get());

    QApplication::processEvents(); // 更新界面
}

void MainWindow::handleInverse() {
    operationWidget_->hideFunctionButtons();
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

    equalsLabel_ = std::make_shared<QLabel>("=", this);
    equalsLabel_->setAlignment(Qt::AlignCenter);
    equalsLabel_->setFixedSize(20, 50);
    layout->addWidget(equalsLabel_.get());

    Matrix idMatrix(matrix_->getRows(), matrix_->getCols());
    idMatrix.identity(); // 确保 IdMatrix 是单位矩阵

    idWidget_ = std::make_shared<BoardWidget>(idMatrix.getRows(), idMatrix.getCols(), this);
    idWidget_->setMatrix(idMatrix);
    layout->addWidget(idWidget_.get());



    QApplication::processEvents(); // 更新界面

    // 输出布局中部件的数量
}

void MainWindow::handleDeterminant() {
    operationWidget_->hideFunctionButtons();
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
    equalsLabel_ = std::make_shared<QLabel>("=", this);
    equalsLabel_->setAlignment(Qt::AlignCenter);
    equalsLabel_->setFixedSize(20, 50); // 设置等号的大小
    detWidget_ = std::make_shared<BoardWidget>(1, 1, this);
    detWidget_->setMatrix(detMatrix);
    layout->addWidget(equalsLabel_.get());
    layout->addWidget(detWidget_.get());
    QApplication::processEvents(); // 更新界面
    // 计算行列式的逻辑
    
}

void MainWindow::handleQrDecomposition() {
    operationWidget_->hideFunctionButtons();
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    auto [Q, R] = matrix_->qrDecomposition();

    auto [norms,norms_inv] = matrix_->getColumnNormsAndInverse();
    auto centralWidget = this->centralWidget();
    auto layout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    if (!layout) {
        layout = new QHBoxLayout(centralWidget);
        centralWidget->setLayout(layout);
    }
    equalsLabel_ = std::make_shared<QLabel>("=", this);
    equalsLabel_->setAlignment(Qt::AlignCenter);
    equalsLabel_->setFixedSize(20, 50); // 设置等号的大小
    layout->addWidget(equalsLabel_.get());
    qWidget_ = std::make_shared<BoardWidget>(Q.getRows(), Q.getCols(), this);
    layout->addWidget(qWidget_.get());
    qWidget_->setMatrixWithSquarerootRight(Q, norms_inv);
    
    rWidget_ = std::make_shared<BoardWidget>(R.getRows(), R.getCols(), this);
    layout->addWidget(rWidget_.get());
    rWidget_->setMatrixWithSquarerootLeft( norms_inv,R);
}

void MainWindow::handleSvdDecomposition() {
    operationWidget_->hideFunctionButtons();
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    auto [U,Sigma,V] = matrix_->getSVDdecomposition();
    auto [norms_U,norms_inv_U] = U.getColumnNormsAndInverse();
    std::cout<<std::endl;
    auto [norms_V,norms_inv_V] = V.getColumnNormsAndInverse();
    auto centralWidget = this->centralWidget();
    auto layout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    if (!layout) {
        layout = new QHBoxLayout(centralWidget);
        centralWidget->setLayout(layout);
    }
    equalsLabel_ = std::make_shared<QLabel>("=", this);
    equalsLabel_->setAlignment(Qt::AlignCenter);
    equalsLabel_->setFixedSize(20, 50); // 设置等号的大小
    layout->addWidget(equalsLabel_.get());
    uWidget_ = std::make_shared<BoardWidget>(U.getRows(), U.getCols(), this);
    layout->addWidget(uWidget_.get());
    uWidget_->setMatrixWithSquarerootRight(U, norms_inv_U);
    sigmaWidget_ = std::make_shared<BoardWidget>(Sigma.getRows(), Sigma.getCols(), this);
    sigmaWidget_->setMatrixWithSVD(Sigma);
    layout->addWidget(sigmaWidget_.get());
    vWidget_ = std::make_shared<BoardWidget>(V.getRows(), V.getCols(), this);
    layout->addWidget(vWidget_.get());
    vWidget_->setTransposeMatrixWithSquarerootRight(V,norms_inv_V);
}

void MainWindow::handleJordanForm() {
    operationWidget_->hideFunctionButtons();
    if(matrix_ == nullptr){
        QMessageBox::warning(this, "输入错误", "请先输入矩阵", QMessageBox::Ok);
        handleBack();
        return;
    }
    auto J = matrix_->getJordanForm();
    equalsLabel_ = std::make_shared<QLabel>("~", this);
    equalsLabel_->setAlignment(Qt::AlignCenter);
    equalsLabel_->setFixedSize(20, 50);
    auto centralWidget = this->centralWidget();
    auto layout = qobject_cast<QHBoxLayout*>(centralWidget->layout());
    layout->addWidget(equalsLabel_.get());
    jordanWidget_ = std::make_shared<BoardWidget>(J.getRows(), J.getCols(), this);
    jordanWidget_->setMatrix(J);
    layout->addWidget(jordanWidget_.get());
}

// 实现 handleBack 槽函数
void MainWindow::handleBack() {
    operationWidget_->showStartButton();
    operationWidget_->showFunctionButtons();
    boardWidget_.reset();
    detWidget_.reset();
    permutationWidget_.reset();
    lowerWidget_.reset();
    upperWidget_.reset();
    invWidget_.reset();
    idWidget_.reset();
    qWidget_.reset();
    rWidget_.reset();
    matrix_.reset();
    uWidget_.reset();
    sigmaWidget_.reset();
    vWidget_.reset();
    jordanWidget_.reset();
    setupUi();
    equalsLabel_.reset();
}

void MainWindow::handleFileInputMatrix() {
    operationWidget_->hideInputButtons();
    
    // 创建文件选择对话框
    QMessageBox::information(this,"文件信息格式","第一行：行数 列数。第二行及以后：矩阵元素，元素之间用空格分隔，分数用'a/b'表示",QMessageBox::Ok);
    QFileDialog fileDialog(this, "选择矩阵文件");
    fileDialog.setNameFilter("Text files (*.txt)");
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    
    if (fileDialog.exec()) {
        QStringList files = fileDialog.selectedFiles();
        QString filename = files.at(0);
        QFile file(filename);
        
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "错误", "无法打开文件", QMessageBox::Ok);
            handleBack();
            return;
        }

        QTextStream in(&file);
        
        // 读取矩阵大小
        QString firstLine = in.readLine();
        QStringList sizes = firstLine.split(" ", Qt::SkipEmptyParts);
        if (sizes.size() != 2) {
            QMessageBox::warning(this, "格式错误", "第一行应包含两个数字(行数 列数)", QMessageBox::Ok);
            handleBack();
            return;
        }

        bool ok1, ok2;
        int rows = sizes[0].toInt(&ok1);
        int cols = sizes[1].toInt(&ok2);

        if (!ok1 || !ok2 || rows <= 0 || cols <= 0) {
            QMessageBox::warning(this, "格式错误", "矩阵维度必须为正整数", QMessageBox::Ok);
            handleBack();
            return;
        }

        // 创建矩阵和显示组件
        matrix_ = std::make_shared<Matrix>(rows, cols);
        boardWidget_ = std::make_shared<BoardWidget>(rows, cols, this);
        
        // 读取矩阵元素
        for (int i = 0; i < rows; i++) {
            QString line = in.readLine();
            QStringList elements = line.split(" ", Qt::SkipEmptyParts);
            
            if (elements.size() != cols) {
                QMessageBox::warning(this, "格式错误", 
                    QString("第%1行元素数量不��确").arg(i + 1), QMessageBox::Ok);
                handleBack();
                return;
            }

            for (int j = 0; j < cols; j++) {
                QString element = elements[j];
                if (element.contains("/")) {
                    QStringList fraction = element.split("/");
                    if (fraction.size() != 2) {
                        QMessageBox::warning(this, "格式错误", 
                            QString("第%1行第%2列的分数格式错误").arg(i + 1).arg(j + 1), 
                            QMessageBox::Ok);
                        handleBack();
                        return;
                    }
                    bool okNum, okDen;
                    long long num = fraction[0].toLongLong(&okNum);
                    long long den = fraction[1].toLongLong(&okDen);
                    if (!okNum || !okDen || den == 0) {
                        QMessageBox::warning(this, "格式错误", 
                            QString("第%1行第%2列的数值无效").arg(i + 1).arg(j + 1), 
                            QMessageBox::Ok);
                        handleBack();
                        return;
                    }
                    matrix_->setEntry(i, j, Entry(num, den));
                } else {
                    bool ok;
                    long long value = element.toLongLong(&ok);
                    if (!ok) {
                        QMessageBox::warning(this, "格式错误", 
                            QString("第%1行第%2列的数值无效").arg(i + 1).arg(j + 1), 
                            QMessageBox::Ok);
                        handleBack();
                        return;
                    }
                    matrix_->setEntry(i, j, Entry(value, 1));
                }
            }
        }

        // 添加到布局并显示
        auto centralWidget = this->centralWidget();
        auto mainLayout = centralWidget->layout();
        mainLayout->addWidget(boardWidget_.get());
        boardWidget_->setMatrix(*matrix_);
        
        file.close();
        operationWidget_->showFunctionButtons();
        QMessageBox::information(this, "文件输入", "读取矩阵信息完毕", QMessageBox::Ok);
    }
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
                        QMessageBox::warning(this, "输入错误", "输入不能为空，���重新输入。", QMessageBox::Ok);
                        j--; // 重新输入当前元素
                        continue; // 跳过当前循环，等待用户重新输入
                    }

                    // 检查输入是否为分数
                    if (input.contains("/")) {
                        QStringList parts = input.split("/");
                        if (parts.size() != 2) {
                            QMessageBox::warning(this, "输入错误", "分格式不正确，请输入如 'a/b' 的格式。", QMessageBox::Ok);
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
                            matrix.setEntry(i, j, Entry(numerator, denominator)); // 使用 setEntry 方法设置矩阵素
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
