/****************************************************************************
** Meta object code from reading C++ file 'Form1.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Form1.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Form1.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Form1_t {
    QByteArrayData data[7];
    char stringdata[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Form1_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Form1_t qt_meta_stringdata_Form1 = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Form1"
QT_MOC_LITERAL(1, 6, 17), // "on_button_clicked"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 25), // "on_buttonCubeMesh_clicked"
QT_MOC_LITERAL(4, 51, 27), // "on_buttonSphereMesh_clicked"
QT_MOC_LITERAL(5, 79, 29), // "on_buttonCylinderMesh_clicked"
QT_MOC_LITERAL(6, 109, 27) // "on_buttonTeaPotMesh_clicked"

    },
    "Form1\0on_button_clicked\0\0"
    "on_buttonCubeMesh_clicked\0"
    "on_buttonSphereMesh_clicked\0"
    "on_buttonCylinderMesh_clicked\0"
    "on_buttonTeaPotMesh_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Form1::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Form1 *_t = static_cast<Form1 *>(_o);
        switch (_id) {
        case 0: _t->on_button_clicked(); break;
        case 1: _t->on_buttonCubeMesh_clicked(); break;
        case 2: _t->on_buttonSphereMesh_clicked(); break;
        case 3: _t->on_buttonCylinderMesh_clicked(); break;
        case 4: _t->on_buttonTeaPotMesh_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Form1::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Form1.data,
      qt_meta_data_Form1,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Form1::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Form1::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Form1.stringdata))
        return static_cast<void*>(const_cast< Form1*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Form1::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
