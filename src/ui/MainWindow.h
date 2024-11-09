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
