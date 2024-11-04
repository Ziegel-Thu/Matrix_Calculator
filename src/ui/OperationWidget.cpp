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
    mainBox_->setFixedSize(150, 150);
    
    auto modeBox_ = new QGroupBox(this);
    auto modeLayout = new QVBoxLayout(modeBox_);
    modeBox_->setFixedSize(150, 300);
    
    auto inputBox_ = new QGroupBox(this);
    auto inputLayout = new QVBoxLayout(inputBox_);


    modeSelect_ = std::make_shared<QPushButton>("功 能 选 择");
    back_ = std::make_shared<QPushButton>("返 回");

    mainLayout->addWidget(modeSelect_.get());
    mainLayout->addWidget(back_.get());
    mainBox_->setLayout(mainLayout);

    inputBox_->setFixedSize(150, 100);
    iostreamInputButton_ = std::make_shared<QPushButton>("标准输入", this);
    fileInputButton_ = std::make_shared<QPushButton>("文件输入", this);
    

    inputLayout->addWidget(iostreamInputButton_.get());
    inputLayout->addWidget(fileInputButton_.get());
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



    QObject::connect(modeSelect_.get(), &QPushButton::clicked, this, &OperationWidget::showFunctionButtons);

    connect(luDecompositionButton_.get(), &QPushButton::clicked, this, &OperationWidget::luDecompositionRequested);
    connect(inverseButton_.get(), &QPushButton::clicked, this, &OperationWidget::inverseRequested);
    connect(determinantButton_.get(), &QPushButton::clicked, this, &OperationWidget::determinantRequested);
    connect(qrDecompositionButton_.get(), &QPushButton::clicked, this, &OperationWidget::qrDecompositionRequested);
    connect(svdDecompositionButton_.get(), &QPushButton::clicked, this, &OperationWidget::svdDecompositionRequested);
    connect(jordanFormButton_.get(), &QPushButton::clicked, this, &OperationWidget::jordanFormRequested);
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
}
void OperationWidget::hideInputButtons(){

    iostreamInputButton_->hide();
    fileInputButton_->hide();
}