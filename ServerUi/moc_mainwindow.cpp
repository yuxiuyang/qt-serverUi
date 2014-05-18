/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Sun May 18 23:24:35 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      26,   11,   11,   11, 0x0a,
      39,   11,   11,   11, 0x0a,
      52,   11,   11,   11, 0x0a,
      76,   11,   11,   11, 0x0a,
     100,   11,   11,   11, 0x0a,
     121,   11,   11,   11, 0x0a,
     145,   11,   11,   11, 0x0a,
     176,  170,   11,   11, 0x0a,
     208,  170,   11,   11, 0x0a,
     247,  243,   11,   11, 0x0a,
     281,  274,   11,   11, 0x0a,
     322,  315,   11,   11, 0x0a,
     367,   11,   11,   11, 0x0a,
     385,   11,   11,   11, 0x0a,
     403,   11,   11,   11, 0x0a,
     424,  170,   11,   11, 0x0a,
     455,  170,   11,   11, 0x0a,
     494,  490,   11,   11, 0x0a,
     517,  490,   11,   11, 0x0a,
     549,  541,   11,   11, 0x0a,
     577,   11,   11,   11, 0x0a,
     591,   11,   11,   11, 0x0a,
     605,   11,   11,   11, 0x0a,
     623,   11,   11,   11, 0x0a,
     636,   11,   11,   11, 0x0a,
     653,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0start_click()\0stop_click()\0"
    "exit_click()\0clearConnectMsg_click()\0"
    "clearDisplayMsg_click()\0generateData_click()\0"
    "sendRequestData_click()\0"
    "saveCollectDatas_click()\0state\0"
    "startTestCheckStateChanged(int)\0"
    "showReadDataCheckStateChanged(int)\0"
    "buf\0appendStatisticsMsg(char*)\0id,buf\0"
    "showData(ClientType_,const char*)\0"
    "id,msg\0displayStatisicsResult(ClientType_,TESTMSG*)\0"
    "valueChanged(int)\0alarmChanged(int)\0"
    "setValue_slider(int)\0"
    "sendDataCheckStateChanged(int)\0"
    "collectDatasCheckStateChanged(int)\0"
    "msg\0appendMsg(const char*)\0"
    "appendData(const char*)\0msg,len\0"
    "appendData(const BYTE*,int)\0radioChange()\0"
    "freOk_click()\0freCancel_click()\0"
    "rcOk_click()\0rcCancel_click()\0sendTimer()\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: start_click(); break;
        case 1: stop_click(); break;
        case 2: exit_click(); break;
        case 3: clearConnectMsg_click(); break;
        case 4: clearDisplayMsg_click(); break;
        case 5: generateData_click(); break;
        case 6: sendRequestData_click(); break;
        case 7: saveCollectDatas_click(); break;
        case 8: startTestCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: showReadDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: appendStatisticsMsg((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 11: showData((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 12: displayStatisicsResult((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< TESTMSG*(*)>(_a[2]))); break;
        case 13: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: alarmChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setValue_slider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: sendDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: collectDatasCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: appendMsg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 19: appendData((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 20: appendData((*reinterpret_cast< const BYTE*(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 21: radioChange(); break;
        case 22: freOk_click(); break;
        case 23: freCancel_click(); break;
        case 24: rcOk_click(); break;
        case 25: rcCancel_click(); break;
        case 26: sendTimer(); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
