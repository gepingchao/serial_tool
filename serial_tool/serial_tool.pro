#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T17:06:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = serial_tool
TEMPLATE = app


SOURCES += main.cpp\
        serial_tool.cpp \
    qextserialport_win.cpp \
    qextserialport.cpp \
    cmd.cpp \
    config.cpp \
    crc.cpp \
    protocol.cpp

HEADERS  += serial_tool.h \
    myhelper.h \
    qextserialport_p.h \
    qextserialport_global.h \
    qextserialport.h \
    cmd.h \
    crc.h \
    protocol.h

FORMS    += serial_tool.ui
