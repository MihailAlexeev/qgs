QT       += core gui xml network printsupport sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mcl.cpp

HEADERS += \
    mainwindow.h \
    mcl.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/../apps_2/lib/ -lqgis_app

INCLUDEPATH += $$PWD/../apps_2/include/qgis
DEPENDPATH += $$PWD/../apps_2/include/qgis

unix:!macx: LIBS += -L$$PWD/../apps_2/lib/ -lqgis_core

INCLUDEPATH += $$PWD/../apps_2/include/qgis
DEPENDPATH += $$PWD/../apps_2/include/qgis

unix:!macx: LIBS += -L$$PWD/../apps_2/lib/ -lqgis_gui

INCLUDEPATH += $$PWD/../apps_2/include/qgis
DEPENDPATH += $$PWD/../apps_2/include/qgis

unix:!macx: LIBS += -L$$PWD/../apps_2/lib/ -lqgis_native

INCLUDEPATH += $$PWD/../apps_2/include/qgis
DEPENDPATH += $$PWD/../apps_2/include/qgis

unix:!macx: LIBS += -L$$PWD/../../../usr/lib/ -lgdal

INCLUDEPATH += $$PWD/../../../usr/include/gdal
DEPENDPATH += $$PWD/../../../usr/include/gdal
