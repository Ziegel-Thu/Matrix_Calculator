#pragma once
#include <QMainWindow>
#include <memory>
#include "OperationWidget.h"
#include "BoardWidget.h"
#include <QHBoxLayout>



class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    std::shared_ptr<OperationWidget> getOperationWidget() const;
    

private:
    void setupUi();
    std::shared_ptr<OperationWidget> operationWidget_;
    std::shared_ptr<BoardWidget> boardWidget_;
    std::shared_ptr<Matrix> matrix_; // 添加这一行声明 matrix_
    std::shared_ptr<Matrix> idMatrix_;
    std::shared_ptr<BoardWidget> detWidget_;
    std::shared_ptr<BoardWidget> permutationWidget_;
    std::shared_ptr<BoardWidget> lowerWidget_;
    std::shared_ptr<BoardWidget> upperWidget_;
    std::shared_ptr<BoardWidget> invWidget_;
    std::shared_ptr<BoardWidget> idWidget_;
    std::shared_ptr<BoardWidget> qWidget_;
    std::shared_ptr<BoardWidget> rWidget_;
    std::shared_ptr<BoardWidget> uWidget_;
    std::shared_ptr<BoardWidget> sigmaWidget_;
    std::shared_ptr<BoardWidget> vWidget_;


    QHBoxLayout *sideLayout;

    // 添加槽函数声明
private slots:
    //void startHandle();
    void handleLuDecomposition();
    void handleInverse();
    void handleDeterminant();
    void handleQrDecomposition();
    void handleSvdDecomposition();
    void handleJordanForm();
    void handleBack();
    void handleFileInputMatrix();
    void handleBoxInputMatrix();
    void handleIostreamInputMatrix();
    void handleStart();
};
