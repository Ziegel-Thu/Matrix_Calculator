#pragma once
#include <QString>
#include <QObject>

class ErrorHandler : public QObject {
    Q_OBJECT

public:
    static ErrorHandler& getInstance() {
        static ErrorHandler instance;
        return instance;
    }

signals:
    void errorOccurred(const QString& message);

private:
    ErrorHandler() = default;
    ~ErrorHandler() = default;
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
};
