/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "openFileAction"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 11), // "closeAction"
QT_MOC_LITERAL(4, 39, 20), // "interpolationChanged"
QT_MOC_LITERAL(5, 60, 16), // "renderingChanged"
QT_MOC_LITERAL(6, 77, 15), // "rotationChanged"
QT_MOC_LITERAL(7, 93, 16), // "setRotationSpeed"
QT_MOC_LITERAL(8, 110, 1), // "s"
QT_MOC_LITERAL(9, 112, 6), // "moveUp"
QT_MOC_LITERAL(10, 119, 8), // "moveDown"
QT_MOC_LITERAL(11, 128, 8), // "moveLeft"
QT_MOC_LITERAL(12, 137, 9), // "moveRight"
QT_MOC_LITERAL(13, 147, 4), // "zoom"
QT_MOC_LITERAL(14, 152, 5), // "value"
QT_MOC_LITERAL(15, 158, 6), // "useGPU"
QT_MOC_LITERAL(16, 165, 22), // "changeSamplingStepsize"
QT_MOC_LITERAL(17, 188, 20) // "setFirstHitThreshold"

    },
    "MainWindow\0openFileAction\0\0closeAction\0"
    "interpolationChanged\0renderingChanged\0"
    "rotationChanged\0setRotationSpeed\0s\0"
    "moveUp\0moveDown\0moveLeft\0moveRight\0"
    "zoom\0value\0useGPU\0changeSamplingStepsize\0"
    "setFirstHitThreshold"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x09 /* Protected */,
       3,    0,   85,    2, 0x09 /* Protected */,
       4,    0,   86,    2, 0x0a /* Public */,
       5,    0,   87,    2, 0x0a /* Public */,
       6,    0,   88,    2, 0x0a /* Public */,
       7,    1,   89,    2, 0x0a /* Public */,
       9,    0,   92,    2, 0x0a /* Public */,
      10,    0,   93,    2, 0x0a /* Public */,
      11,    0,   94,    2, 0x0a /* Public */,
      12,    0,   95,    2, 0x0a /* Public */,
      13,    1,   96,    2, 0x0a /* Public */,
      15,    1,   99,    2, 0x0a /* Public */,
      16,    1,  102,    2, 0x0a /* Public */,
      17,    1,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   14,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openFileAction(); break;
        case 1: _t->closeAction(); break;
        case 2: _t->interpolationChanged(); break;
        case 3: _t->renderingChanged(); break;
        case 4: _t->rotationChanged(); break;
        case 5: _t->setRotationSpeed((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->moveUp(); break;
        case 7: _t->moveDown(); break;
        case 8: _t->moveLeft(); break;
        case 9: _t->moveRight(); break;
        case 10: _t->zoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->useGPU((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 12: _t->changeSamplingStepsize((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->setFirstHitThreshold((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
