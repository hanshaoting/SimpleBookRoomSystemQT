QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addbook.cpp \
    addreader.cpp \
    books.cpp \
    deletebook.cpp \
    library.cpp \
    loannum.cpp \
    main.cpp \
    mainwindow.cpp \
    reader.cpp \
    register.cpp \
    registernumber.cpp \
    table.cpp

HEADERS += \
    addbook.h \
    addreader.h \
    books.h \
    deletebook.h \
    library.h \
    loannum.h \
    mainwindow.h \
    reader.h \
    register.h \
    registernumber.h \
    table.h

FORMS += \
    addbook.ui \
    addreader.ui \
    deletebook.ui \
    loannum.ui \
    mainwindow.ui \
    registernumber.ui \
    table.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../../../.qrc
