TEMPLATE = app
TARGET = AppName

QT = core gui widgets opengl openglwidgets

DISTFILES += \
    .gitignore \
    LICENSE.txt \
    README.md

SOURCES += \
    main.cpp \
    sgcentralmanagement.cpp \
    sggenerallibrary.cpp \
    sgrootwindow.cpp \
    sgsignalsemitter.cpp \
    sgstatusbarmanagement.cpp \
    sgtext022221131.cpp \
    sgwidget000411102.cpp \
    sgwidget000451103.cpp

HEADERS += \
    sgcentralmanagement.h \
    sggenerallibrary.h \
    sgrootwindow.h \
    sgsignalsemitter.h \
    sgstatusbarmanagement.h \
    sgtext022221131.h \
    sgwidget000411102.h \
    sgwidget000451103.h

RESOURCES += \
    assets.qrc
