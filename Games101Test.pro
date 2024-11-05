QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas/openglwidget.cpp \
    datas/camera.cpp \
    datas/face.cpp \
    datas/facehandle.cpp \
    datas/meshdata.cpp \
    datas/model.cpp \
    datas/shaderprogram.cpp \
    datas/vertex.cpp \
    datas/vertexhandle.cpp \
    main.cpp \
    mainwindow.cpp \
    manager/meshdatamanager.cpp \
    manager/shaderprogrammanager.cpp \
    tool/tool.cpp

HEADERS += \
    canvas/openglwidget.h \
    datas/camera.h \
    datas/face.h \
    datas/facehandle.h \
    datas/meshdata.h \
    datas/model.h \
    datas/shaderprogram.h \
    datas/vertex.h \
    datas/vertexhandle.h \
    mainwindow.h \
    manager/meshdatamanager.h \
    manager/shaderprogrammanager.h \
    tool/tool.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resc.qrc
