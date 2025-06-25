QT = core gui qml quick quickcontrols2
QMAKE_CXXFLAGS_RELEASE += -O3 -flto -ffunction-sections -fdata-sections -std=c++20
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_DEBUG += -std=c++20
QMAKE_LFLAGS = -flto -Wl,--gc-sections
DISTFILES = .gitignore LICENSE.txt README.md \
    vesicles/vesicles.frag \
    vesicles/vesicles.vert
SOURCES = misc/main.cpp \
    misc/sgxcentral.cpp \
    primitives/sgxcolourhsla.cpp \
    primitives/sgxcolourrgba.cpp \
    primitives/sgxidentifier.cpp \
    primitives/sgxtimestamp.cpp \
    primitives/sgxtouchevent.cpp \
    primitives/sgxvector2.cpp \
    quickui/sgxquickresizer.cpp \
    quickui/sgxquickuiinterface.cpp \
    quickui/sgxthemecoloursetting.cpp \
    userDefinedClasses/sgucentralmanagement.cpp \
    vesicles/sgxvesiclesmaterial.cpp \
    vesicles/sgxvesiclesquickuielement.cpp \
    vesicles/sgxvesiclesshader.cpp
RESOURCES = assets.qrc
HEADERS += \
    misc/sgxcentral.h \
    primitives/sgxcolourhsla.h \
    primitives/sgxcolourrgba.h \
    primitives/sgxidentifier.h \
    primitives/sgxtimestamp.h \
    primitives/sgxtouchevent.h \
    primitives/sgxvector2.h \
    quickui/sgxquickresizer.h \
    quickui/sgxquickuiinterface.h \
    quickui/sgxthemecoloursetting.h \
    userDefinedClasses/sgucentralmanagement.h \
    vesicles/sgxvesiclesmaterial.h \
    vesicles/sgxvesiclesquickuielement.h \
    vesicles/sgxvesiclesshader.h
