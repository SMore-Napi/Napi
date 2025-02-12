#-------------------------------------------------
#
# Project created by QtCreator 2018-01-28T18:04:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Napi
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


INCLUDEPATH += C:\Qt\opencv3_2_0\opencv\opencv-build\install\include

LIBS += C:\Qt\opencv3_2_0\opencv\opencv-build\bin\libopencv_core320.dll
LIBS += C:\Qt\opencv3_2_0\opencv\opencv-build\bin\libopencv_highgui320.dll
LIBS += C:\Qt\opencv3_2_0\opencv\opencv-build\bin\libopencv_imgcodecs320.dll
LIBS += C:\Qt\opencv3_2_0\opencv\opencv-build\bin\libopencv_imgproc320.dll
LIBS += C:\Qt\opencv3_2_0\opencv\opencv-build\bin\libopencv_calib3d320.dll


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scan.cpp \
    addlibrary.cpp \
    editsettings.cpp \
    settings.cpp \
    createframe.cpp \
    film.cpp

HEADERS += \
        mainwindow.h \
    scan.h \
    addlibrary.h \
    editsettings.h \
    settings.h \
    createframe.h \
    film.h

FORMS += \
        mainwindow.ui \
    scan.ui \
    addlibrary.ui \
    editsettings.ui \
    film.ui

RESOURCES +=


