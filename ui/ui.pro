QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/task.cpp \
    ../src/testSpline.cpp \
    customview.cpp \
    main.cpp \
    mainwindow.cpp \
    taskui.cpp

HEADERS += \
    ../include/task.h \
    ../include/testSpline.h \
    customview.h \
    mainwindow.h \
    taskui.h

FORMS += \
    mainwindow.ui \
    taskui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
