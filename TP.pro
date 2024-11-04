QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/diagramwidget.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/Scheduler.cpp \
    src/Server.cpp \
    src/Sensor/Temperature.cpp \
    src/Sensor/Humidity.cpp \
    src/Sensor/Light.cpp \
    src/Sensor/Sound.cpp \
    src/Sensor/Sensor.cpp \

HEADERS += \
    headers/mainwindow.h \
    headers/diagramwidget.h \
    headers/Scheduler.hpp \
    headers/Server.hpp \
    headers/Temperature.hpp \
    headers/Humidity.hpp \
    headers/Light.hpp \
    headers/Sound.hpp \
    src/Sensor/Sensor.hpp \

FORMS += \
    form/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/resources.qrc
