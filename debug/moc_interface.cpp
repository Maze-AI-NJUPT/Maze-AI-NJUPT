/****************************************************************************
** Meta object code from reading C++ file 'interface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../interface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'interface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_interface_t {
    QByteArrayData data[8];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_interface_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_interface_t qt_meta_stringdata_interface = {
    {
QT_MOC_LITERAL(0, 0, 9), // "interface"
QT_MOC_LITERAL(1, 10, 14), // "classicalStart"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "DungeonStart"
QT_MOC_LITERAL(4, 39, 7), // "loading"
QT_MOC_LITERAL(5, 47, 4), // "Quit"
QT_MOC_LITERAL(6, 52, 13), // "CheckBGMstate"
QT_MOC_LITERAL(7, 66, 9) // "AboutShow"

    },
    "interface\0classicalStart\0\0DungeonStart\0"
    "loading\0Quit\0CheckBGMstate\0AboutShow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_interface[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x0a /* Public */,
       3,    0,   45,    2, 0x0a /* Public */,
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void interface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        interface *_t = static_cast<interface *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->classicalStart(); break;
        case 1: _t->DungeonStart(); break;
        case 2: _t->loading(); break;
        case 3: _t->Quit(); break;
        case 4: _t->CheckBGMstate(); break;
        case 5: _t->AboutShow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject interface::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_interface.data,
      qt_meta_data_interface,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *interface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *interface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_interface.stringdata0))
        return static_cast<void*>(const_cast< interface*>(this));
    return QWidget::qt_metacast(_clname);
}

int interface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
