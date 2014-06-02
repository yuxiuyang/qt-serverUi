# -------------------------------------------------
# Project created by QtCreator 2014-05-30T23:27:19
# -------------------------------------------------
TARGET = simulator
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    groupwindow.cpp \
    narcomgr.cpp \
    network_server.cpp \
    nibpmgr.cpp \
    ibpmgr.cpp \
    linkmgr.cpp \
    ecgmgr.cpp \
    datamgr.cpp \
    co2mgr.cpp \
    basicmgr.cpp \
    common/state.cpp \
    common/recvobject.cpp \
    common/queue.cpp \
    common/fltkLog.cpp \
    common/file.cpp \
    common/datadev.cpp \
    spo2mgr.cpp \
    common/global.cpp
HEADERS += mainwindow.h \
    groupwindow.h \
    narcomgr.h \
    network_server.h \
    nibpmgr.h \
    ibpmgr.h \
    linkmgr.h \
    ecgmgr.h \
    datamgr.h \
    co2mgr.h \
    basicmgr.h \
    common/state.h \
    common/recvobject.h \
    common/queue.h \
    common/fltkLog.h \
    common/file.h \
    common/datadev.h \
    include/define.h \
    spo2mgr.h \
    common/global.h
FORMS += mainwindow.ui
INCLUDEPATH += $$quote(thread_task)
INCLUDEPATH += $$quote(common)
LIBS += -Lthread_task/Debug \
    -lthread_task
