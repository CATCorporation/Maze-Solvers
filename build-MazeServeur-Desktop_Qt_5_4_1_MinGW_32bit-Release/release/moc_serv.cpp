/****************************************************************************
** Meta object code from reading C++ file 'serv.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MazeServeur/serv.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_serv_t {
    QByteArrayData data[15];
    char stringdata[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_serv_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_serv_t qt_meta_stringdata_serv = {
    {
QT_MOC_LITERAL(0, 0, 4), // "serv"
QT_MOC_LITERAL(1, 5, 6), // "niveau"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 3), // "niv"
QT_MOC_LITERAL(4, 17, 6), // "nombre"
QT_MOC_LITERAL(5, 24, 2), // "nb"
QT_MOC_LITERAL(6, 27, 19), // "handleNewConnection"
QT_MOC_LITERAL(7, 47, 18), // "clientDisconnected"
QT_MOC_LITERAL(8, 66, 10), // "readClient"
QT_MOC_LITERAL(9, 77, 14), // "timeoutCommand"
QT_MOC_LITERAL(10, 92, 8), // "commands"
QT_MOC_LITERAL(11, 101, 2), // "UP"
QT_MOC_LITERAL(12, 104, 4), // "DOWN"
QT_MOC_LITERAL(13, 109, 4), // "LEFT"
QT_MOC_LITERAL(14, 114, 5) // "RIGHT"

    },
    "serv\0niveau\0\0niv\0nombre\0nb\0"
    "handleNewConnection\0clientDisconnected\0"
    "readClient\0timeoutCommand\0commands\0"
    "UP\0DOWN\0LEFT\0RIGHT"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_serv[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       1,   54, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   50,    2, 0x09 /* Protected */,
       7,    0,   51,    2, 0x09 /* Protected */,
       8,    0,   52,    2, 0x09 /* Protected */,
       9,    0,   53,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, flags, count, data
      10, 0x0,    4,   58,

 // enum data: key, value
      11, uint(serv::UP),
      12, uint(serv::DOWN),
      13, uint(serv::LEFT),
      14, uint(serv::RIGHT),

       0        // eod
};

void serv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        serv *_t = static_cast<serv *>(_o);
        switch (_id) {
        case 0: _t->niveau((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->nombre((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->handleNewConnection(); break;
        case 3: _t->clientDisconnected(); break;
        case 4: _t->readClient(); break;
        case 5: _t->timeoutCommand(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (serv::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serv::niveau)) {
                *result = 0;
            }
        }
        {
            typedef void (serv::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&serv::nombre)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject serv::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_serv.data,
      qt_meta_data_serv,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *serv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *serv::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_serv.stringdata))
        return static_cast<void*>(const_cast< serv*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int serv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void serv::niveau(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void serv::nombre(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
