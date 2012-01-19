### eqmake4 was here ###
TEMPLATE = app
CONFIG += console

LIBS += -lIvy
LIBS += -L/usr/lib64

SOURCES += main.cpp \
    view.cpp \
    button.cpp \
    article.cpp \
    topbar.cpp \
    settings.cpp \
	IvyBinder.cpp \
    IvyLoop.cpp

HEADERS += \
    view.hpp \
    button.hpp \
    article.hpp \
    topbar.hpp \
    settings.hpp \
	IvyBinder.hpp \
    IvyLoop.hpp

RESOURCES += \
    images.qrc

