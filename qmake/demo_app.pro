QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h \
    src/common.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += ./src
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#DEFINES += LOG2FILE

RESOURCES += \
    res/res.qrc

GIT_HASH = $$system(git --git-dir $$PWD/.git log -1 --pretty=format:%h)
DEFINES += GIT_HASH=\\\"$$GIT_HASH\\\"

GIT_DATE = $$system(git --git-dir $$PWD/.git --work-tree $$PWD log -1 --format=%cs )
DEFINES += GIT_DATE=\\\"$$GIT_DATE\\\"

VERSION = 0.02
DEFINES += SOFT_VERSION=\"\\\"$$VERSION\\\"\"

TARGET = demo_app$$VERSION"_"$$GIT_DATE"_"$$GIT_HASH

DESTDIR = $$absolute_path($${_PRO_FILE_PWD_}/bin/)
OBJECTS_DIR = $$absolute_path($${_PRO_FILE_PWD_}/obj/)
MOC_DIR = $$absolute_path($${_PRO_FILE_PWD_}/obj/moc)
UI_DIR = $$absolute_path($${_PRO_FILE_PWD_}/obj/ui)

include($$PWD/changelog.pri)
include($$PWD/deploy.pri)
