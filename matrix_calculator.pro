QT       += core gui widgets

TARGET = matrix_calculator
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/ui/MainWindow.cpp \
    src/ui/OperationWidget.cpp \
    src/ui/BoardWidget.cpp \
    src/core/Matrix.cpp \
    src/core/MatrixOperations.cpp \
    src/core/Board.cpp \
    src/core/Entry.cpp

HEADERS += \
    src/ui/MainWindow.h \
    src/ui/OperationWidget.h \
    src/ui/BoardWidget.h \
    src/core/Matrix.h \
    src/core/MatrixOperations.h \
    src/core/Board.h \
    src/core/Entry.h

INCLUDEPATH += \
    src \
    src/core \
    src/ui

# 默认规则
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

