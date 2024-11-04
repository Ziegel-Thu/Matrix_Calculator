/****************************************************************************
** Meta object code from reading C++ file 'OperationWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/ui/OperationWidget.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'OperationWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSOperationWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSOperationWidgetENDCLASS = QtMocHelpers::stringData(
    "OperationWidget",
    "luDecompositionRequested",
    "",
    "inverseRequested",
    "determinantRequested",
    "qrDecompositionRequested",
    "svdDecompositionRequested",
    "jordanFormRequested",
    "fileInputMatrixRequested",
    "iostreamInputMatrixRequested"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSOperationWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,
       5,    0,   65,    2, 0x06,    4 /* Public */,
       6,    0,   66,    2, 0x06,    5 /* Public */,
       7,    0,   67,    2, 0x06,    6 /* Public */,
       8,    0,   68,    2, 0x06,    7 /* Public */,
       9,    0,   69,    2, 0x06,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject OperationWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSOperationWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSOperationWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSOperationWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<OperationWidget, std::true_type>,
        // method 'luDecompositionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'inverseRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'determinantRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'qrDecompositionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'svdDecompositionRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'jordanFormRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'fileInputMatrixRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'iostreamInputMatrixRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void OperationWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<OperationWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->luDecompositionRequested(); break;
        case 1: _t->inverseRequested(); break;
        case 2: _t->determinantRequested(); break;
        case 3: _t->qrDecompositionRequested(); break;
        case 4: _t->svdDecompositionRequested(); break;
        case 5: _t->jordanFormRequested(); break;
        case 6: _t->fileInputMatrixRequested(); break;
        case 7: _t->iostreamInputMatrixRequested(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::luDecompositionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::inverseRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::determinantRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::qrDecompositionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::svdDecompositionRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::jordanFormRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::fileInputMatrixRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (OperationWidget::*)();
            if (_t _q_method = &OperationWidget::iostreamInputMatrixRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 7;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *OperationWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *OperationWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSOperationWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int OperationWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void OperationWidget::luDecompositionRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void OperationWidget::inverseRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void OperationWidget::determinantRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void OperationWidget::qrDecompositionRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void OperationWidget::svdDecompositionRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void OperationWidget::jordanFormRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void OperationWidget::fileInputMatrixRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void OperationWidget::iostreamInputMatrixRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
