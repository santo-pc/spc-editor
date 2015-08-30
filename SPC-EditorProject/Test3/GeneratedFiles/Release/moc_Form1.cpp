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
    QByteArrayData data[15];
    char stringdata[324];
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
QT_MOC_LITERAL(6, 109, 27), // "on_buttonTeaPotMesh_clicked"
QT_MOC_LITERAL(7, 137, 28), // "on_value_changed_lightColorR"
QT_MOC_LITERAL(8, 166, 28), // "on_value_changed_lightColorG"
QT_MOC_LITERAL(9, 195, 28), // "on_value_changed_lightColorB"
QT_MOC_LITERAL(10, 224, 25), // "on_slider_ambient_changed"
QT_MOC_LITERAL(11, 250, 5), // "value"
QT_MOC_LITERAL(12, 256, 25), // "on_slider_diffuse_changed"
QT_MOC_LITERAL(13, 282, 21), // "on_refresh_nodeEditor"
QT_MOC_LITERAL(14, 304, 19) // "on_showShaderButton"

    },
    "Form1\0on_button_clicked\0\0"
    "on_buttonCubeMesh_clicked\0"
    "on_buttonSphereMesh_clicked\0"
    "on_buttonCylinderMesh_clicked\0"
    "on_buttonTeaPotMesh_clicked\0"
    "on_value_changed_lightColorR\0"
    "on_value_changed_lightColorG\0"
    "on_value_changed_lightColorB\0"
    "on_slider_ambient_changed\0value\0"
    "on_slider_diffuse_changed\0"
    "on_refresh_nodeEditor\0on_showShaderButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Form1[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      12,    1,   85,    2, 0x08 /* Private */,
      13,    0,   88,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
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
        case 5: _t->on_value_changed_lightColorR(); break;
        case 6: _t->on_value_changed_lightColorG(); break;
        case 7: _t->on_value_changed_lightColorB(); break;
        case 8: _t->on_slider_ambient_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_slider_diffuse_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_refresh_nodeEditor(); break;
        case 11: _t->on_showShaderButton(); break;
        default: ;
        }
    }
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
