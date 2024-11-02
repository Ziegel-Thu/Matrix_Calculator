#include <QMainWindow>
#include <memory>
#include "OperationWidget.h"
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    std::shared_ptr<OperationWidget> getOperationWidget() const;

private:
    void setupUi();
    std::shared_ptr<OperationWidget> operationWidget_;
    QHBoxLayout *sideLayout;
};
