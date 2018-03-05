#-------------------------------------------------
#
# Project created by QtCreator 2018-03-02T21:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        MainWindow.cpp \
    SaveAsDialog.cpp \
    PreferencesDialog.cpp \
    AboutDialog.cpp

HEADERS += \
        MainWindow.h \
    SaveAsDialog.h \
    PreferencesDialog.h \
    AboutDialog.h

FORMS += \
        MainWindow.ui \
    SaveAsDialog.ui \
    PreferencesDialog.ui \
    AboutDialog.ui

DISTFILES += \
    config.txt \
    Resources/copyIcon.png \
    Resources/cutIcon.png \
    Resources/newFileIcon.png \
    Resources/openFileIcon.png \
    Resources/pasteIcon.png \
    Resources/redoIcon.png \
    Resources/saveAsIcon.png \
    Resources/saveFileIcon.png \
    Resources/undoIcon.png

RESOURCES += \
    Resources.qrc
