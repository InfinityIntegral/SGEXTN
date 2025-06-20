QT = core gui widgets opengl openglwidgets
QMAKE_CXXFLAGS_RELEASE += -O3 -flto -ffunction-sections -fdata-sections -std=c++20
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_DEBUG += -std=c++20
QMAKE_LFLAGS = -flto -Wl,--gc-sections
DISTFILES = .gitignore LICENSE.txt README.md
SOURCES = misc/main.cpp \
    misc/sgxcentral.cpp \
    primitives/sgxcolourhsla.cpp \
    primitives/sgxcolourrgba.cpp \
    primitives/sgxidentifier.cpp \
    primitives/sgxtimestamp.cpp \
    primitives/sgxvector2.cpp \
    userDefinedClasses/sgucentralmanagement.cpp \
    userDefinedClasses/sgusignalemitter.cpp \
    widgets/sgxicon.cpp \
    widgets/sgxiconbutton.cpp \
    widgets/sgxinputfield.cpp \
    widgets/sgxlayout.cpp \
    widgets/sgxlongtext.cpp \
    widgets/sgxlongtextinternal.cpp \
    widgets/sgxparentwidget.cpp \
    widgets/sgxrootwidget.cpp \
    widgets/sgxscrollbar.cpp \
    widgets/sgxscrollview.cpp \
    widgets/sgxtext.cpp \
    widgets/sgxtextbutton.cpp \
    widgets/sgxwidget.cpp
RESOURCES = assets.qrc
HEADERS += \
    misc/sgxcentral.h \
    primitives/sgxcolourhsla.h \
    primitives/sgxcolourrgba.h \
    primitives/sgxidentifier.h \
    primitives/sgxtimestamp.h \
    primitives/sgxvector2.h \
    userDefinedClasses/sgucentralmanagement.h \
    userDefinedClasses/sgusignalemitter.h \
    widgets/sgxicon.h \
    widgets/sgxiconbutton.h \
    widgets/sgxinputfield.h \
    widgets/sgxlayout.h \
    widgets/sgxlongtext.h \
    widgets/sgxlongtextinternal.h \
    widgets/sgxparentwidget.h \
    widgets/sgxrootwidget.h \
    widgets/sgxscrollbar.h \
    widgets/sgxscrollview.h \
    widgets/sgxtext.h \
    widgets/sgxtextbutton.h \
    widgets/sgxwidget.h
