/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Fri May 23 22:58:02 2014
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
      33,   14, // methods
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
     245,   11,   11,   11, 0x0a,
     266,   11,   11,   11, 0x0a,
     287,   11,   11,   11, 0x0a,
     308,   11,   11,   11, 0x0a,
     333,  329,   11,   11, 0x0a,
     362,  356,   11,   11, 0x0a,
     394,  356,   11,   11, 0x0a,
     433,  429,   11,   11, 0x0a,
     467,  460,   11,   11, 0x0a,
     508,  501,   11,   11, 0x0a,
     553,   11,   11,   11, 0x0a,
     589,   11,   11,   11, 0x0a,
     607,   11,   11,   11, 0x0a,
     625,   11,   11,   11, 0x0a,
     646,  356,   11,   11, 0x0a,
     677,  356,   11,   11, 0x0a,
     712,   11,   11,   11, 0x0a,
     726,   11,   11,   11, 0x0a,
     740,   11,   11,   11, 0x0a,
     758,   11,   11,   11, 0x0a,
     771,   11,   11,   11, 0x0a,
     788,   11,   11,   11, 0x0a,

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
    "delCollectDatas_click()\0addValueToCb_click()\0"
    "delValueToCb_click()\0addAlarmToCb_click()\0"
    "delAlarmToCb_click()\0msg\0"
    "appendMsg(const char*)\0state\0"
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
        case 11: addValueToCb_click(); break;
        case 12: delValueToCb_click(); break;
        case 13: addAlarmToCb_click(); break;
        case 14: delAlarmToCb_click(); break;
        case 15: appendMsg((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 16: startTestCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: showReadDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: appendStatisticsMsg((*reinterpret_cast< char*(*)>(_a[1]))); break;
        case 19: showData((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< const char*(*)>(_a[2]))); break;
        case 20: displayStatisicsResult((*reinterpret_cast< ClientType_(*)>(_a[1])),(*reinterpret_cast< TESTMSG*(*)>(_a[2]))); break;
        case 21: updateFileFromStartToEndPos_click(); break;
        case 22: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: alarmChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: setValue_slider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: sendDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: collectDatasCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: radioChange(); break;
        case 28: freOk_click(); break;
        case 29: freCancel_click(); break;
        case 30: rcOk_click(); break;
        case 31: rcCancel_click(); break;
        case 32: sendTimer(); break;
        default: ;
        }
        _id -= 33;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
