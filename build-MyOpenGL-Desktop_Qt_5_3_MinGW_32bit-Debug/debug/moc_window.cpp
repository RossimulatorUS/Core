/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Core/window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[14];
    char stringdata[293];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Window_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 34),
QT_MOC_LITERAL(2, 42, 0),
QT_MOC_LITERAL(3, 43, 30),
QT_MOC_LITERAL(4, 74, 30),
QT_MOC_LITERAL(5, 105, 21),
QT_MOC_LITERAL(6, 127, 27),
QT_MOC_LITERAL(7, 155, 4),
QT_MOC_LITERAL(8, 160, 22),
QT_MOC_LITERAL(9, 183, 22),
QT_MOC_LITERAL(10, 206, 19),
QT_MOC_LITERAL(11, 226, 22),
QT_MOC_LITERAL(12, 249, 21),
QT_MOC_LITERAL(13, 271, 21)
    },
    "Window\0on_m_boutonStartSimulation_clicked\0"
    "\0on_m_boutonSimulation1_clicked\0"
    "on_m_boutonSimulation4_clicked\0"
    "on_pushButton_clicked\0on_currentScale_textChanged\0"
    "arg1\0on_xOffset_textChanged\0"
    "on_yOffset_textChanged\0on_offsetUp_clicked\0"
    "on_offsetRight_clicked\0on_offsetDown_clicked\0"
    "on_offsetLeft_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
       9,    1,   79,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        switch (_id) {
        case 0: _t->on_m_boutonStartSimulation_clicked(); break;
        case 1: _t->on_m_boutonSimulation1_clicked(); break;
        case 2: _t->on_m_boutonSimulation4_clicked(); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->on_currentScale_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_xOffset_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_yOffset_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->on_offsetUp_clicked(); break;
        case 8: _t->on_offsetRight_clicked(); break;
        case 9: _t->on_offsetDown_clicked(); break;
        case 10: _t->on_offsetLeft_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, 0, 0}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
