######################################################################
# Automatically generated by qmake (3.1) Tue Jul 1 15:59:29 2025
######################################################################

TEMPLATE = app
TARGET = LibreriaMultimediale
INCLUDEPATH += .
QT += widgets

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += io/JSONFileHandler.h \
           io/JSONSerializer.h \
           io/JSONVisitor.h \
           logic/Book.h \
           logic/Film.h \
           logic/Item.h \
           logic/Library.h \
           logic/Music.h \
           logic/ObserverInterface.h \
           logic/VisitorInterface.h \
           visual/BookForm.h \
           visual/FilmForm.h \
           visual/Form.h \
           visual/FormWidget.h \
           visual/ImageHandler.h \
           visual/ItemCard.h \
           visual/MainWidget.h \
           visual/ModifyWidgetVisitor.h \
           visual/MusicForm.h \
           visual/OverviewWidgetVisitor.h \
           visual/QFlowLayout.h \
           visual/SearchWidget.h \
           visual/TopBar.h
SOURCES += main.cpp \
           io/JSONFileHandler.cpp \
           io/JSONSerializer.cpp \
           io/JSONVisitor.cpp \
           logic/Book.cpp \
           logic/Film.cpp \
           logic/Item.cpp \
           logic/Library.cpp \
           logic/Music.cpp \
           visual/BookForm.cpp \
           visual/FilmForm.cpp \
           visual/Form.cpp \
           visual/FormWidget.cpp \
           visual/ImageHandler.cpp \
           visual/ItemCard.cpp \
           visual/MainWidget.cpp \
           visual/ModifyWidgetVisitor.cpp \
           visual/MusicForm.cpp \
           visual/OverviewWidgetVisitor.cpp \
           visual/QFlowLayout.cpp \
           visual/SearchWidget.cpp \
           visual/TopBar.cpp
RESOURCES += application.qrc
