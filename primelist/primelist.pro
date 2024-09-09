TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    primefunctions.h

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
