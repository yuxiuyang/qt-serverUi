/****************************************************************************
** Meta object code from reading C++ file 'groupwindow.h'
**
** Created: Mon Jun 2 15:58:05 2014
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "groupwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'groupwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_GroupBasicWindow[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      43,   17,   17,   17, 0x0a,
      67,   17,   17,   17, 0x0a,
      92,   17,   17,   17, 0x0a,
     110,   17,   17,   17, 0x0a,
     128,   17,   17,   17, 0x0a,
     149,   17,   17,   17, 0x0a,
     170,   17,   17,   17, 0x0a,
     191,   17,   17,   17, 0x0a,
     212,   17,   17,   17, 0x0a,
     248,   17,   17,   17, 0x0a,
     275,  269,   17,   17, 0x0a,
     307,  269,   17,   17, 0x0a,
     342,  269,   17,   17, 0x0a,
     373,   17,   17,   17, 0x0a,
     399,   17,   17,   17, 0x0a,
     424,   17,   17,   17, 0x0a,
     449,   17,   17,   17, 0x0a,
     473,   17,   17,   17, 0x0a,
     487,   17,   17,   17, 0x0a,
     505,   17,   17,   17, 0x0a,
     518,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_GroupBasicWindow[] = {
    "GroupBasicWindow\0\0clearTextBrowser_click()\0"
    "sendRequestData_click()\0"
    "generateTestData_click()\0valueChanged(int)\0"
    "alarmChanged(int)\0addValueToCb_click()\0"
    "delValueToCb_click()\0addAlarmToCb_click()\0"
    "delAlarmToCb_click()\0"
    "updateFileFromStartToEndPos_click()\0"
    "setValue_slider(int)\0state\0"
    "startTestCheckStateChanged(int)\0"
    "showReadDataCheckStateChanged(int)\0"
    "sendDataCheckStateChanged(int)\0"
    "startCollectDatas_click()\0"
    "stopCollectDatas_click()\0"
    "saveCollectDatas_click()\0"
    "delCollectDatas_click()\0freOk_click()\0"
    "freCancel_click()\0rcOk_click()\0"
    "rcCancel_click()\0"
};

const QMetaObject GroupBasicWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_GroupBasicWindow,
      qt_meta_data_GroupBasicWindow, 0 }
};

const QMetaObject *GroupBasicWindow::metaObject() const
{
    return &staticMetaObject;
}

void *GroupBasicWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GroupBasicWindow))
	return static_cast<void*>(const_cast< GroupBasicWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int GroupBasicWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: clearTextBrowser_click(); break;
        case 1: sendRequestData_click(); break;
        case 2: generateTestData_click(); break;
        case 3: valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: alarmChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: addValueToCb_click(); break;
        case 6: delValueToCb_click(); break;
        case 7: addAlarmToCb_click(); break;
        case 8: delAlarmToCb_click(); break;
        case 9: updateFileFromStartToEndPos_click(); break;
        case 10: setValue_slider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: startTestCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: showReadDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: sendDataCheckStateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: startCollectDatas_click(); break;
        case 15: stopCollectDatas_click(); break;
        case 16: saveCollectDatas_click(); break;
        case 17: delCollectDatas_click(); break;
        case 18: freOk_click(); break;
        case 19: freCancel_click(); break;
        case 20: rcOk_click(); break;
        case 21: rcCancel_click(); break;
        }
        _id -= 22;
    }
    return _id;
}
