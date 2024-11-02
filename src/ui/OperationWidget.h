#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#pragma once

class OperationWidget : public QWidget {
    Q_OBJECT
public:
    OperationWidget(QWidget *parent = nullptr);
    void showFunctionButtons();
    
private:
    std::shared_ptr<QLabel> label_;
    std::shared_ptr<QPushButton> modeSelect_;
    std::shared_ptr<QPushButton> back_;
    std::shared_ptr<QPushButton> luDecompositionButton_;
    std::shared_ptr<QPushButton> inverseButton_;
    std::shared_ptr<QPushButton> determinantButton_;
    std::shared_ptr<QPushButton> qrDecompositionButton_;
    std::shared_ptr<QPushButton> svdDecompositionButton_;
    std::shared_ptr<QPushButton> jordanFormButton_;
};
    