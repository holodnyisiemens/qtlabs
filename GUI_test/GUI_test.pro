QT += testlib
QT += gui
QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_test_sample.cpp \
    ../lab2/dialog.cpp

DEPLOY_TARGET = $$shell_quote($$shell_path($$OUT_PWD/release/$$TARGET.exe))

DISTFILES += \
    .astylerc

FORMS += \
    ../lab2/dialog.ui

HEADERS += \
    ../lab2/dialog.h

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
