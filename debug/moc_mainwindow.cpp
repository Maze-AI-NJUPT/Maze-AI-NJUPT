/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "ShowWidget"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "moveCharacter"
QT_MOC_LITERAL(4, 37, 17), // "CreateMaze_Layout"
QT_MOC_LITERAL(5, 55, 8), // "ShowPath"
QT_MOC_LITERAL(6, 64, 13), // "ShowAnimation"
QT_MOC_LITERAL(7, 78, 9), // "timeStart"
QT_MOC_LITERAL(8, 88, 12), // "MapStytleSet"
QT_MOC_LITERAL(9, 101, 4), // "quit"
QT_MOC_LITERAL(10, 106, 14), // "GetitemWinshow"
QT_MOC_LITERAL(11, 121, 12), // "FightWinshow"
QT_MOC_LITERAL(12, 134, 17), // "ShowdynamicEffect"
QT_MOC_LITERAL(13, 152, 9), // "OpenStore"
QT_MOC_LITERAL(14, 162, 18), // "ReturnMainMenuPlay"
QT_MOC_LITERAL(15, 181, 11), // "RestartPlay"
QT_MOC_LITERAL(16, 193, 9), // "soundStop"
QT_MOC_LITERAL(17, 203, 13), // "CheckBGMstate"
QT_MOC_LITERAL(18, 217, 12) // "EnterDungeon"

    },
    "MainWindow\0ShowWidget\0\0moveCharacter\0"
    "CreateMaze_Layout\0ShowPath\0ShowAnimation\0"
    "timeStart\0MapStytleSet\0quit\0GetitemWinshow\0"
    "FightWinshow\0ShowdynamicEffect\0OpenStore\0"
    "ReturnMainMenuPlay\0RestartPlay\0soundStop\0"
    "CheckBGMstate\0EnterDungeon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    0,  102,    2, 0x08 /* Private */,
       6,    0,  103,    2, 0x08 /* Private */,
       7,    0,  104,    2, 0x08 /* Private */,
       8,    0,  105,    2, 0x08 /* Private */,
       9,    0,  106,    2, 0x08 /* Private */,
      10,    0,  107,    2, 0x08 /* Private */,
      11,    0,  108,    2, 0x08 /* Private */,
      12,    0,  109,    2, 0x08 /* Private */,
      13,    0,  110,    2, 0x08 /* Private */,
      14,    0,  111,    2, 0x08 /* Private */,
      15,    0,  112,    2, 0x08 /* Private */,
      16,    0,  113,    2, 0x08 /* Private */,
      17,    0,  114,    2, 0x08 /* Private */,
      18,    0,  115,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowWidget(); break;
        case 1: _t->moveCharacter(); break;
        case 2: _t->CreateMaze_Layout(); break;
        case 3: _t->ShowPath(); break;
        case 4: _t->ShowAnimation(); break;
        case 5: _t->timeStart(); break;
        case 6: _t->MapStytleSet(); break;
        case 7: _t->quit(); break;
        case 8: _t->GetitemWinshow(); break;
        case 9: _t->FightWinshow(); break;
        case 10: _t->ShowdynamicEffect(); break;
        case 11: _t->OpenStore(); break;
        case 12: _t->ReturnMainMenuPlay(); break;
        case 13: _t->RestartPlay(); break;
        case 14: _t->soundStop(); break;
        case 15: _t->CheckBGMstate(); break;
        case 16: _t->EnterDungeon(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
