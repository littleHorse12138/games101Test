QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    canvas/fpswidget.cpp \
    canvas/modeltreewgt.cpp \
    canvas/onemodelwidget.cpp \
    canvas/openglwidget.cpp \
    canvas/simopenglwidget.cpp \
    canvas/toolwidget.cpp \
    datas/boundingbox.cpp \
    datas/camera.cpp \
    datas/edge.cpp \
    datas/edgehandle.cpp \
    datas/face.cpp \
    datas/facehandle.cpp \
    datas/light.cpp \
    datas/material.cpp \
    datas/meshdata.cpp \
    datas/model.cpp \
    datas/shaderprogram.cpp \
    datas/vertex.cpp \
    datas/vertexhandle.cpp \
    datas/viewer.cpp \
    main.cpp \
    mainwindow.cpp \
    manager/lightmanager.cpp \
    manager/materialmanager.cpp \
    manager/meshdatamanager.cpp \
    manager/shaderprogrammanager.cpp \
    tool/intersection.cpp \
    tool/tool.cpp

HEADERS += \
    canvas/fpswidget.h \
    canvas/modeltreewgt.h \
    canvas/onemodelwidget.h \
    canvas/openglwidget.h \
    canvas/simopenglwidget.h \
    canvas/toolwidget.h \
    datas/boundingbox.h \
    datas/camera.h \
    datas/edge.h \
    datas/edgehandle.h \
    datas/face.h \
    datas/facehandle.h \
    datas/light.h \
    datas/material.h \
    datas/meshdata.h \
    datas/model.h \
    datas/shaderprogram.h \
    datas/vertex.h \
    datas/vertexhandle.h \
    datas/viewer.h \
    mainwindow.h \
    manager/lightmanager.h \
    manager/materialmanager.h \
    manager/meshdatamanager.h \
    manager/shaderprogrammanager.h \
    tool/intersection.h \
    tool/tool.h

FORMS += \
    canvas/fpswidget.ui \
    canvas/modeltreewgt.ui \
    canvas/onemodelwidget.ui \
    canvas/toolwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resc.qrc
