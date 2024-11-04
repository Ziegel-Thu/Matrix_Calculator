#include "MainWindow.h"
#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
    setWindowTitle("矩 阵 计 算 器"); // 设置窗口标题

    // 连接 OperationWidget 的信号到 MainWindow 的槽
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
    boardWidget_ = std::make_shared<BoardWidget>(3, 3, this); // 创建 3x3 的棋盘
    mainLayout->addWidget(boardWidget_.get()); 
    mainLayout->addWidget(operationWidget_.get()); 

    setCentralWidget(centralWidget);

    // 连接 back 按钮的信号
    connect(operationWidget_->back_.get(), &QPushButton::clicked, this, &MainWindow::handleBack);
}

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
    // 处理返回逻辑，例如隐藏功能按钮并显示模式选择按钮
    operationWidget_->modeSelect_->show();
    operationWidget_->luDecompositionButton_->hide();
    operationWidget_->inverseButton_->hide();
    operationWidget_->determinantButton_->hide();
    operationWidget_->qrDecompositionButton_->hide();
    operationWidget_->svdDecompositionButton_->hide();
    operationWidget_->jordanFormButton_->hide();
}