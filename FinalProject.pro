TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
INCLUDEPATH +=/usr/include/poppler/cpp
INCLUDEPATH +=/use/include/poppler/qt5
LIBS += -lpoppler-cpp
LIBS += -ltiff

SOURCES += \
    DSString.cpp \
    tests.cpp \
    AVLTree.cpp \
    textstream.cpp \
    hashtable.cpp \
    porter2_stemmer.cpp \
    indexinterface.cpp \
    AVLTreeString.cpp \
    pdfreader.cpp \
    main.cpp \
    search.cpp

HEADERS += \
    catch.hpp \
    DSString.h \
    linkedlist.h \
    queue.h \
    stack.h \
    Vector.h \
    AVLTree.h \
    main.h \
    textstream.h \
    hashtable.h \
    indexinterface.h \
    porter2_stemmer.h \
    AVLTreeString.h \
    pdfreader.h \
    search.h

DISTFILES += \
    stopwords.txt
