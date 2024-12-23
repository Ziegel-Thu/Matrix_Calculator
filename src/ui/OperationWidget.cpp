#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QLineEdit>

OperationWidget::OperationWidget(QWidget *parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    
    auto mainBox_ = new QGroupBox(this);
    auto mainLayout = new QVBoxLayout(mainBox_);
    mainBox_->setFixedSize(150, 100);
    
    auto modeBox_ = new QGroupBox(this);
    auto modeLayout = new QVBoxLayout(modeBox_);
    modeBox_->setFixedSize(150, 300);
    
    auto inputBox_ = new QGroupBox(this);
    auto inputLayout = new QVBoxLayout(inputBox_);


    startButton_ = std::make_shared<QPushButton>("开 始");
    back_ = std::make_shared<QPushButton>("返 回");

    mainLayout->addWidget(startButton_.get());
    mainLayout->addWidget(back_.get());
    mainBox_->setLayout(mainLayout);

    inputBox_->setFixedSize(150, 120);
    iostreamInputButton_ = std::make_shared<QPushButton>("输入流输入", this);
    fileInputButton_ = std::make_shared<QPushButton>("文件输入", this);
    boxInputButton_ = std::make_shared<QPushButton>("输入框输入", this);
    

    inputLayout->addWidget(iostreamInputButton_.get());
    inputLayout->addWidget(fileInputButton_.get());
    inputLayout->addWidget(boxInputButton_.get());
    inputBox_->setLayout(inputLayout);

    luDecompositionButton_ = std::make_shared<QPushButton>("LU分解");
    inverseButton_ = std::make_shared<QPushButton>("求逆");
    determinantButton_ = std::make_shared<QPushButton>("行列式");
    qrDecompositionButton_ = std::make_shared<QPushButton>("QR分解");
    svdDecompositionButton_ = std::make_shared<QPushButton>("SVD分解");
    jordanFormButton_ = std::make_shared<QPushButton>("Jordan标准型");

    modeLayout->addWidget(luDecompositionButton_.get());
    modeLayout->addWidget(inverseButton_.get());
    modeLayout->addWidget(determinantButton_.get());
    modeLayout->addWidget(qrDecompositionButton_.get());
    modeLayout->addWidget(svdDecompositionButton_.get());
    modeLayout->addWidget(jordanFormButton_.get());
    modeBox_->setLayout(modeLayout);

    layout->addWidget(mainBox_);
    layout->addWidget(modeBox_);
    layout->addWidget(inputBox_);
    setLayout(layout);



    connect(startButton_.get(), &QPushButton::clicked, this, &OperationWidget::startRequested);
    connect(iostreamInputButton_.get(),&QPushButton::clicked,this,&OperationWidget::iostreamInputMatrixRequested);
    connect(fileInputButton_.get(),&QPushButton::clicked,this,&OperationWidget::fileInputMatrixRequested);
    connect(luDecompositionButton_.get(), &QPushButton::clicked, this, &OperationWidget::luDecompositionRequested);
    connect(inverseButton_.get(), &QPushButton::clicked, this, &OperationWidget::inverseRequested);
    connect(determinantButton_.get(), &QPushButton::clicked, this, &OperationWidget::determinantRequested);
    connect(qrDecompositionButton_.get(), &QPushButton::clicked, this, &OperationWidget::qrDecompositionRequested);
    connect(svdDecompositionButton_.get(), &QPushButton::clicked, this, &OperationWidget::svdDecompositionRequested);
    connect(jordanFormButton_.get(), &QPushButton::clicked, this, &OperationWidget::jordanFormRequested);
    connect(back_.get(), &QPushButton::clicked, this, &OperationWidget::backRequested);
    connect(boxInputButton_.get(), &QPushButton::clicked, this, &OperationWidget::boxInputMatrixRequested);
}

void OperationWidget::showFunctionButtons() {
    luDecompositionButton_->show();
    inverseButton_->show();
    determinantButton_->show();
    qrDecompositionButton_->show();
    svdDecompositionButton_->show();
    jordanFormButton_->show();
}
void OperationWidget::hideFunctionButtons() {
    luDecompositionButton_->hide();
    inverseButton_->hide();
    determinantButton_->hide();
    qrDecompositionButton_->hide();
    svdDecompositionButton_->hide();
    jordanFormButton_->hide();
}
void OperationWidget::showInputButtons(){
    iostreamInputButton_->show();
    fileInputButton_->show();
    boxInputButton_->show();
}
void OperationWidget::hideInputButtons(){

    iostreamInputButton_->hide();
    fileInputButton_->hide();
    boxInputButton_->hide();
}
void OperationWidget::hideStartButton(){
    startButton_->hide();
}
void OperationWidget::showStartButton(){
    startButton_->show();
}
void OperationWidget::hideBackButton(){
    back_->hide();
}
void OperationWidget::showBackButton(){
    back_->show();
}