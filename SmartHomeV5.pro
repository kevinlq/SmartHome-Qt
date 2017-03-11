#-------------------------------------------------
#
# Project created by QtCreator 2016-01-17 T17:07:36
#
#-------------------------------------------------

QT  += core gui
QT  += printsupport
QT  += sql
#QT  += phonon

CONFIG  += debug serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHomeV5
TEMPLATE = app

TRANSLATIONS += images/qt_zh_CN.ts

include(src/mainwidget/mainwidget.pri)
include(src/help/help.pri)
include(src/Serialport/serialport.pri)
include(src/ui/ui.pri)
include(src/module/module.pri)
include(src/qcustomplot/qcustomplot.pri)      #第三方绘图图
include(src/database/database.pri)
include(src/protocol/protocol.pri)
include(src/login/loginwidget.pri)

INCLUDEPATH += $$PWD/src/Serialport
INCLUDEPATH += $$PWD/src/mainwidget
INCLUDEPATH += $$PWD/src/help
INCLUDEPATH += $$PWD/src/ui
INCLUDEPATH += $$PWD/src/module
INCLUDEPATH += $$PWD/src/qcustomplot
INCLUDEPATH += $$PWD/src/database
INCLUDEPATH += $$PWD/src/protocol
INCLUDEPATH += $$PWD/src/login

MOC_DIR = temp/moc
RCC_DIR = temp/rccr
OBJECTS_DIR = temp/obj
UI_HEADERS_DIR = temp/ui
DESTDIR = bin

win32:RC_FILE = SmartHome.rc
RESOURCES += \
    image.qrc
