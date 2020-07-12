/****************************************************************************
** Meta object code from reading C++ file 'UdpSocketListener.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/UdpSocketListener.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UdpSocketListener.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UdpSocketListener_t {
    QByteArrayData data[11];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpSocketListener_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpSocketListener_t qt_meta_stringdata_UdpSocketListener = {
    {
QT_MOC_LITERAL(0, 0, 17), // "UdpSocketListener"
QT_MOC_LITERAL(1, 18, 5), // "error"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "printString"
QT_MOC_LITERAL(4, 37, 14), // "runApplication"
QT_MOC_LITERAL(5, 52, 15), // "applicationPath"
QT_MOC_LITERAL(6, 68, 20), // "applicationArguments"
QT_MOC_LITERAL(7, 89, 12), // "dataInSignal"
QT_MOC_LITERAL(8, 102, 4), // "Data"
QT_MOC_LITERAL(9, 107, 9), // "readyRead"
QT_MOC_LITERAL(10, 117, 3) // "run"

    },
    "UdpSocketListener\0error\0\0printString\0"
    "runApplication\0applicationPath\0"
    "applicationArguments\0dataInSignal\0"
    "Data\0readyRead\0run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpSocketListener[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,
       4,    2,   50,    2, 0x06 /* Public */,
       7,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UdpSocketListener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UdpSocketListener *_t = static_cast<UdpSocketListener *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->printString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->runApplication((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->dataInSignal((*reinterpret_cast< Data(*)>(_a[1]))); break;
        case 4: _t->readyRead(); break;
        case 5: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UdpSocketListener::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocketListener::error)) {
                *result = 0;
            }
        }
        {
            typedef void (UdpSocketListener::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocketListener::printString)) {
                *result = 1;
            }
        }
        {
            typedef void (UdpSocketListener::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocketListener::runApplication)) {
                *result = 2;
            }
        }
        {
            typedef void (UdpSocketListener::*_t)(Data );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UdpSocketListener::dataInSignal)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject UdpSocketListener::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_UdpSocketListener.data,
      qt_meta_data_UdpSocketListener,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *UdpSocketListener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpSocketListener::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_UdpSocketListener.stringdata0))
        return static_cast<void*>(const_cast< UdpSocketListener*>(this));
    return QThread::qt_metacast(_clname);
}

int UdpSocketListener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void UdpSocketListener::error(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UdpSocketListener::printString(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UdpSocketListener::runApplication(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void UdpSocketListener::dataInSignal(Data _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
