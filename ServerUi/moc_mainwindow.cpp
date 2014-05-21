/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed May 21 14:32:15 2014
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
      31,   14, // methods
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
     171,   11,   11,   11, 0x0a,
     196,   11,   11,   11, 0x0a,
     221,   11,   11,   11, 0x0a,
     251,  245,   11,   11, 0x0a,
     283,  245,   11,   11, 0x0a,
     322,  318,   11,   11, 0x0a,
     356,  349,   11,   11, 0x0a,
     397,  390,   11,   11, 0x0a,
     442,   11,   11,   11, 0x0a,
     478,   11,   11,   11, 0x0a,
     496,   11,   11,   11, 0x0a,
     514,   11,   11,   11, 0x0a,
     535,  245,   11,   11, 0x0a,
     566,  245,   11,   11, 0x0a,
     605,  601,   11,   11, 0x0a,
     628,  601,   11,   11, 0x0a,
     663,  652,   11,   11, 0x0a,
     703,   11,   11,   11, 0x0a,
     717,   11,   11,   11, 0x0a,
     731,   11,   11,   11, 0x0a,
     749,   11,   11,   11, 0x0a,
     762,   11,   11,   11, 0x0a,
     779,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0start_click()\0stop_click()\0"
    "exit_click()\0clearConnectMsg_click()\0"
    "clearDisplayMsg_click()\0generateData_click()\0"
    "sendRequestData_click()\0"
    "startCollectDatas_click()\0"
    "stopCollectDatas_click()\0"
    "saveCollectDatas_click()\0"
    "delCollectDatas_click()\0state\0"
    "startTestCheckStateChanged(int)\0"
    "showReadDataCheckStateChanged(int)\0"
    "buf\0appendStatisticsMsg(char*)\0id,buf\0"
    "showData(ClientType_,const char*)\0"
    "id,msg\0displayStatisicsResult(ClientType_,TESTMSG*)\0"
    "updateFileFromStartToEndPos_click()\0"
    "valueChanged(int)\0alarmChanged(int)\0"
    "setValue_slider(int)\0"
    "sendDataCheckStateChanged(int)\0"
    "collectDatasCheckStateChanged(int)\0"
    "msg\0appendMsg(const char*)\0"
    "appendData(const char*)\0id,msg,len\0"
    "appendData(ClientType_,const BYTE*,int)\0"
    "radioChange()\0freOk_click()\0"
    "freCancel_click()\0rcOk_click()\0"
    "rcCancel_click()\0sendTimer()\0"
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
        case 7: startCollectDatas_click(); break;
        case 8: stopCollectDatas_click(); break;
        case 9: saveCollectDatas_click(); break;
        case 10: delCollectDatas_click(); break;
        case 11: startTestCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: showReadDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: appendStatisticsMsg((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 14: showData((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 15: displayStatisicsResult((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< TESTMSG*(*)>(_a[2]))); break;
        case 16: updateFileFromStartToEndPos_click(); break;
        case 17: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: alarmChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setValue_slider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: sendDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: collectDatasCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: appendMsg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 23: appendData((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 24: appendData((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< const BYTE*(*)>(_a[2])),(*reinterpret_cast< const int(*)>(_a[3]))); break;
        case 25: radioChange(); break;
        case 26: freOk_click(); break;
        case 27: freCancel_click(); break;
        case 28: rcOk_click(); break;
        case 29: rcCancel_click(); break;
        case 30: sendTimer(); break;
        default: ;
        }
        _id -= 31;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
