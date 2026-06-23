QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src

SOURCES += \
    src/backup/backupmanager.cpp \
    src/server/bedrockserver.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/server/bedrockservermodel.cpp \
    src/widgets/onlineplayerwidget.cpp \
    src/widgets/playerinfowidget.cpp \
    src/widgets/serverconsolewidget.cpp \
    src/database/databasemanager.cpp \
    src/addons/packmanifest.cpp \
    src/addons/archiveextractor.cpp \
    src/addons/addoninstaller.cpp \
    src/addons/addonvalidator.cpp \
    src/addons/addonregistry.cpp \
    src/addons/addonmanager.cpp \
    src/widgets/addoninstallwidget.cpp

HEADERS += \
    src/backup/backupmanager.h \
    src/server/bedrockserver.h \
    src/mainwindow.h \
    src/server/bedrockservermodel.h \
    src/widgets/onlineplayerwidget.h \
    src/widgets/playerinfowidget.h \
    src/widgets/serverconsolewidget.h \
    src/database/databasemanager.h \
    src/addons/packmanifest.h \
    src/addons/archiveextractor.h \
    src/addons/addoninstaller.h \
    src/addons/addonvalidator.h \
    src/addons/addonregistry.h \
    src/addons/addonmanager.h \
    src/widgets/addoninstallwidget.h

FORMS += \
    src/mainwindow.ui \
    src/widgets/playerinfowidget.ui \
    src/widgets/serverconsolewidget.ui \
    src/widgets/addoninstallwidget.ui

# TRANSLATIONS += \
#     lang/mcbc_en.ts \
#     lang/mcbc_en_GB.ts

win32:CONFIG(release, debug|release) {
    QMAKE_POST_LINK = if not exist dist mkdir dist && copy /Y release\\*.exe dist\\ && "C:/Qt/6.11.1/mingw_64/bin/windeployqt.exe" --compiler-runtime dist
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    LICENCE \
    README.md
