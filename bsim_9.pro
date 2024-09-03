QT       += core gui charts serialport serialbus sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    batterymodel.cpp \
    connectionsettingsdialog.cpp \
    devicemodel.cpp \
    doublespinboxdelegate.cpp \
    emulatorsettingsdialog.cpp \
    interpolator.cpp \
    main.cpp \
    mainwindow.cpp \
    modbusmanager.cpp \
    plotmanager.cpp \
    sqlmanager.cpp \
    testmodel.cpp

HEADERS += \
    batterymodel.h \
    connectionsettingsdialog.h \
    devicemodel.h \
    doublespinboxdelegate.h \
    emulatorsettingsdialog.h \
    interpolator.h \
    mainwindow.h \
    modbusmanager.h \
    plotmanager.h \
    sqlmanager.h \
    structs.h \
    testmodel.h

FORMS += \
    connectionsettingsdialog.ui \
    emulatorsettingsdialog.ui \
    mainwindow.ui

TRANSLATIONS = QtTranslation_ru.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    QtTranslation_ru.qm \
    bsim_9.pro.user

TRANSLATIONS += \
    QtTranslation_ru.ts
