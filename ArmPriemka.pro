#-------------------------------------------------
#
# Project created by QtCreator 2018-02-11T18:06:26
#
#-------------------------------------------------

QT       += core gui widgets sql axcontainer printsupport

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArmPriemka
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
        mmainwindow.cpp \
    mentrydialog.cpp \
    mabiturtablewindow.cpp \
    maddabiturdialog.cpp \
    maddabiturdocsdialog.cpp \
    maddspecdialog.cpp \
    maddexamdialog.cpp \
    othertableswindow.cpp \
    madddisciplinedialog.cpp \
    maddbenifitdialog.cpp \
    madddocumenttypedialog.cpp \
    maddspecialitiessetsdialog.cpp \
    maddspecialitiesdialog.cpp \
    mspecsetdiscadddialog.cpp

HEADERS += \
        mmainwindow.h \
    mentrydialog.h \
    precompileconstants.h \
    mabiturtablewindow.h \
    maddabiturdialog.h \
    maddabiturdocsdialog.h \
    maddspecdialog.h \
    maddexamdialog.h \
    othertableswindow.h \
    madddisciplinedialog.h \
    maddbenifitdialog.h \
    madddocumenttypedialog.h \
    maddspecialitiessetsdialog.h \
    maddspecialitiesdialog.h \
    mspecsetdiscadddialog.h

FORMS += \
        mmainwindow.ui \
    mentrydialog.ui \
    mabiturtablewindow.ui \
    maddabiturdialog.ui \
    maddabiturdocsdialog.ui \
    maddspecdialog.ui \
    maddexamdialog.ui \
    othertableswindow.ui \
    madddisciplinedialog.ui \
    maddbenifitdialog.ui \
    madddocumenttypedialog.ui \
    maddspecialitiessetsdialog.ui \
    maddspecialitiesdialog.ui \
    mspecsetdiscadddialog.ui

INCLUDEPATH += "C:\include" \
#    "C:\Users\Arhon\Documents\ArmPriemka\include\QtXlsx"

LIBS += "-LC:\bin" -llibeay32 -llibintl-8 -llibpq -lssleay32 \
#    "-LC:\Users\Arhon\Documents\ArmPriemka\lib" \
#    -lib\Qt5Xlsx -lib\Qt5Xlsxd

RESOURCES += \
    assets.qrc
#
