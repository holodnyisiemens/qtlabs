QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp

HEADERS += \
    dialog.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) { BUILDTYPE = release }
CONFIG(debug, debug|release) { BUILDTYPE = debug }
QMAKE_POST_LINK = windeployqt $$shell_quote($${OUT_PWD}/$${BUILDTYPE}/$${TARGET}.exe)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-primelist_library-Desktop-All/release/ -lprimelist_library
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-primelist_library-Desktop-All/debug/ -lprimelist_library
else:unix: LIBS += -L$$PWD/../build-primelist_library-Desktop-All/ -lprimelist_library

INCLUDEPATH += $$PWD/../primelist_library
DEPENDPATH += $$PWD/../primelist_library

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-primelist_library-Desktop-All/release/libprimelist_library.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-primelist_library-Desktop-All/debug/libprimelist_library.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-primelist_library-Desktop-All/release/primelist_library.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-primelist_library-Desktop-All/debug/primelist_library.lib
else:unix: PRE_TARGETDEPS += $$PWD/../build-primelist_library-Desktop-All/libprimelist_library.a

DISTFILES += \
    .astylerc \
    .git/hooks/pre-commit
