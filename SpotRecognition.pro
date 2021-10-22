#-------------------------------------------------
#
# Project created by QtCreator 2018-12-17T06:54:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = SpotRecognition
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    FrameGenerator.cpp \
    Histogram.cpp \
    Spot.cpp \
    mythread.cpp

HEADERS += \
        mainwindow.h \
    FrameGenerator.h \
    Histogram.h \
    main.h \
    Spot.h \
    mythread.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += D:/Downloads/opencv/build/include/
LIBS += D:/Downloads/opencv/build/bin/opencv_ffmpeg340.dll


RESOURCES += \
    path.qrc

win32:CONFIG(release, debug|release): LIBS += -LD:/Downloads/opencv/build/x64/vc15/lib/ -lopencv_world340
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Downloads/opencv/build/x64/vc15/lib/ -lopencv_world340d
else:unix: LIBS += -LD:/Downloads/opencv/build/x64/vc15/lib/ -lopencv_world340

INCLUDEPATH += D:/Downloads/opencv/build/x64/vc15
DEPENDPATH += D:/Downloads/opencv/build/x64/vc15

win32:CONFIG(release, debug|release): LIBS += -LD:/Downloads/opencv/build/x64/vc15/lib/ -lopencv_world340
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Downloads/opencv/build/x64/vc15/lib/ -lopencv_world340d
else:unix: LIBS += -LD:/Downloads/opencv/build/x64/vc15/lib/ -lopencv_world340

INCLUDEPATH += D:/Downloads/opencv/build/x64/vc15
DEPENDPATH += D:/Downloads/opencv/build/x64/vc15
