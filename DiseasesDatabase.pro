QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database_manager.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    database_manager.hpp \
    mainwindow.hpp

FORMS += \
    mainwindow.ui

RC_ICONS = icon.ico

qm_files.files = $$[QT_INSTALL_TRANSLATIONS]/
RESOURCES += \
    qm_files

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
