#include "OperationWidget.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

OperationWidget::OperationWidget(QWidget *parent) : QWidget(parent) {
    auto layout = new QVBoxLayout(this);
    label_ = std::make_shared<QLabel>("矩 阵 计 算 器");
    modeSelect_ = std::make_shared<QPushButton>("功 能 选 择");
    back_ = std::make_shared<QPushButton>("返 回");

    luDecompositionButton_ = std::make_shared<QPushButton>("LU分解");
    inverseButton_ = std::make_shared<QPushButton>("求逆");
    determinantButton_ = std::make_shared<QPushButton>("行列式");
    qrDecompositionButton_ = std::make_shared<QPushButton>("QR分解");
    svdDecompositionButton_ = std::make_shared<QPushButton>("SVD分解");
    jordanFormButton_ = std::make_shared<QPushButton>("Jordan标准型");

    layout->addWidget(label_.get());
    layout->addWidget(modeSelect_.get());
    layout->addWidget(luDecompositionButton_.get());
    layout->addWidget(inverseButton_.get());
    layout->addWidget(determinantButton_.get());
    layout->addWidget(qrDecompositionButton_.get());
    layout->addWidget(svdDecompositionButton_.get());
    layout->addWidget(jordanFormButton_.get());
    layout->addWidget(back_.get());

    setLayout(layout);

    luDecompositionButton_->hide();
    inverseButton_->hide();
    determinantButton_->hide();
    qrDecompositionButton_->hide();
    svdDecompositionButton_->hide();
    jordanFormButton_->hide();
}

void OperationWidget::showFunctionButtons() {
    modeSelect_->hide();
    luDecompositionButton_->show();
    inverseButton_->show();
    determinantButton_->show();
    qrDecompositionButton_->show();
    svdDecompositionButton_->show();
    jordanFormButton_->show();
}
