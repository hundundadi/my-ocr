QT += core gui printsupport
CONFIG -= app_bundle
CONFIG += qt
CONFIG += C++17
QMAKE_CXXFLAGS += -std=c++17 -std=gnu++17
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    tessocrutils.h \
    imageprocess.h


SOURCES += \
        main.cpp \
    tessocrutils.cpp \
    imageprocess.cpp

include(3rdparty/tesseract_ocr/tesseract_dependency.pri)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#INCLUDEPATH +=./head/ \
#LIBS += -L./lib/ -llept -ltesseract \
#LIBS +=  -llept -ltesseract \
#LIBS += -L/data/home/wangcong/wangcong/workspace/qt_workspace/project/my-ocr/lib/ -llept -ltesseract \


LIBS +=  -llept -lopencv_core -lopencv_imgcodecs -lopencv_stitching -lopencv_highgui -lopencv_imgproc \

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/ -ltesseract
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/ -ltesseractd
#else:unix: LIBS += -L$$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/ -ltesseract

#INCLUDEPATH += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/include
#DEPENDPATH += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/include

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/libtesseract.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/libtesseractd.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/tesseract.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/tesseractd.lib
#else:unix: PRE_TARGETDEPS += $$PWD/../../../../../../../../data/home/wangcong/wangcong/workspace/qt_workspace/SourceCode/build-tesseract-unknown-Default/libtesseract.a
