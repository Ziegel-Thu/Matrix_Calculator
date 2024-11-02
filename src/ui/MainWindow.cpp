#include "MainWindow.h"
#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi();
}
std::shared_ptr<OperationWidget> MainWindow::getOperationWidget() const {
    return operationWidget_;
}
void MainWindow::setupUi(){
    auto centralWidget = new QWidget(this);
    auto mainLayout = new QHBoxLayout(centralWidget);
    operationWidget_ = std::make_shared<OperationWidget>(this);
    mainLayout->addWidget(operationWidget_.get());
    setCentralWidget(centralWidget);
}