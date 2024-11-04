#include <memory>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QVBoxLayout>
#pragma once

class OperationWidget : public QWidget {
    Q_OBJECT
public:
    explicit OperationWidget(QWidget *parent = nullptr);

    std::shared_ptr<QPushButton> back_;
    std::shared_ptr<QPushButton> modeSelect_;
    std::shared_ptr<QPushButton> inputSelect_;
    std::shared_ptr<QPushButton> luDecompositionButton_;
    std::shared_ptr<QPushButton> inverseButton_;
    std::shared_ptr<QPushButton> determinantButton_;
    std::shared_ptr<QPushButton> qrDecompositionButton_;
    std::shared_ptr<QPushButton> svdDecompositionButton_;
    std::shared_ptr<QPushButton> jordanFormButton_;

signals:
    void luDecompositionRequested();
    void inverseRequested();
    void determinantRequested();
    void qrDecompositionRequested();
    void svdDecompositionRequested();
    void jordanFormRequested();

private:
    std::shared_ptr<QGroupBox> modeBox_;
    std::shared_ptr<QGroupBox> mainBox_;
    void showFunctionButtons();
};
    