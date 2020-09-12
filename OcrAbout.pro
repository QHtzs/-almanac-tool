QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDE_ROOT_PATH = $$PWD/3rd/include
LIB_ROOT_PATH = $$PWD/3rd/lib


INCLUDEPATH += \
        $$INCLUDE_ROOT_PATH/opencv \
        $$INCLUDE_ROOT_PATH/pvt.leptonica \
        $$INCLUDE_ROOT_PATH/tesseract \
        $$INCLUDE_ROOT_PATH/tesseract/src  \
        $$INCLUDE_ROOT_PATH/tesseract/src/api \
        $$INCLUDE_ROOT_PATH/tesseract/src/arch \
        $$INCLUDE_ROOT_PATH/tesseract/src/ccmain \
        $$INCLUDE_ROOT_PATH/tesseract/src/ccstruct \
        $$INCLUDE_ROOT_PATH/tesseract/src/ccutil \
        $$INCLUDE_ROOT_PATH/tesseract/src/classify \
        $$INCLUDE_ROOT_PATH/tesseract/src/cutil \
        $$INCLUDE_ROOT_PATH/tesseract/src/dict \
        $$INCLUDE_ROOT_PATH/tesseract/src/lstm \
        $$INCLUDE_ROOT_PATH/tesseract/src/opencl \
        $$INCLUDE_ROOT_PATH/tesseract/src/textord \
        $$INCLUDE_ROOT_PATH/tesseract/src/training \
        $$INCLUDE_ROOT_PATH/tesseract/src/viewer \
        $$INCLUDE_ROOT_PATH/tesseract/src/vs2010 \
        $$INCLUDE_ROOT_PATH/tesseract/src/wordrec

LIBS += \
    -L$${LIB_ROOT_PATH} \
    -lopencv_world400 \
    -lpvt.cppan.demo.danbloomberg.leptonica-1.76.0 \
    -ltesseract40


SOURCES += \
    cv_tool/cvtools.cpp \
    main.cpp \
    mainwindow.cpp \
    protocol/frame.cpp \
    protocol/protobase.cpp \
    protocol/protodirect.cpp \
    protocol/prototcp.cpp \
    shapes/linehist.cpp \
    shapes/linevert.cpp \
    shapes/rectlike.cpp \
    shapes/shape.cpp \
    shapes/shapebase.cpp \
    shapes/shapecreator.cpp \
    widgets/cavas.cpp \
    widgets/dataeditwindow.cpp \
    widgets/hookedimagesave.cpp \
    widgets/modelserverselector.cpp

HEADERS += \
    cv_tool/cvtools.h \
    mainwindow.h \
    protocol/frame.h \
    protocol/protobase.h \
    protocol/protodirect.h \
    protocol/prototcp.h \
    shapes/linehist.h \
    shapes/linevert.h \
    shapes/rectlike.h \
    shapes/shape.h \
    shapes/shapebase.h \
    shapes/shapecreator.h \
    widgets/cavas.h \
    widgets/dataeditwindow.h \
    widgets/hookedimagesave.h \
    widgets/modelserverselector.h

FORMS += \
    mainwindow.ui \
    widgets/cavas.ui \
    widgets/dataeditwindow.ui \
    widgets/hookedimagesave.ui \
    widgets/modelserverselector.ui

TRANSLATIONS += \
    OcrAbout_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc
