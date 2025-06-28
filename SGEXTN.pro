QT = core gui qml quick quickcontrols2
QMAKE_CXXFLAGS_RELEASE += -O3 -flto -ffunction-sections -fdata-sections -std=c++20
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_DEBUG += -std=c++20
QMAKE_LFLAGS = -flto -Wl,--gc-sections
DISTFILES = .gitignore LICENSE.txt README.md \
    compilecommands.txt
SOURCES = SGEXTN/misc/main.cpp \
    SGEXTN/cutevesicles/sgxrendercutevesiclesmaterial.cpp \
    SGEXTN/cutevesicles/sgxrendercutevesiclesquickuielement.cpp \
    SGEXTN/cutevesicles/sgxrendercutevesiclesshader.cpp \
    SGEXTN/filesystem/sgxfilesystem.cpp \
    SGEXTN/misc/sgxcentral.cpp \
    SGEXTN/primitives/sgxcolourhsla.cpp \
    SGEXTN/primitives/sgxcolourrgba.cpp \
    SGEXTN/primitives/sgxidentifier.cpp \
    SGEXTN/primitives/sgxtimestamp.cpp \
    SGEXTN/primitives/sgxtouchevent.cpp \
    SGEXTN/primitives/sgxvector2.cpp \
    SGEXTN/quickui/sgxquickresizer.cpp \
    SGEXTN/quickui/sgxquickuiinterface.cpp \
    SGEXTN/quickui/sgxthemecoloursetting.cpp \
    SGEXTN/userDefinedClasses/sgucentralmanagement.cpp
RESOURCES = SGEXTN/assets.qrc
HEADERS += \
    SGEXTN/cutevesicles/sgxrendercutevesiclesmaterial.h \
    SGEXTN/cutevesicles/sgxrendercutevesiclesquickuielement.h \
    SGEXTN/cutevesicles/sgxrendercutevesiclesshader.h \
    SGEXTN/filesystem/sgxfilesystem.h \
    SGEXTN/misc/sgxcentral.h \
    SGEXTN/primitives/sgxcolourhsla.h \
    SGEXTN/primitives/sgxcolourrgba.h \
    SGEXTN/primitives/sgxidentifier.h \
    SGEXTN/primitives/sgxtimestamp.h \
    SGEXTN/primitives/sgxtouchevent.h \
    SGEXTN/primitives/sgxvector2.h \
    SGEXTN/quickui/sgxquickresizer.h \
    SGEXTN/quickui/sgxquickuiinterface.h \
    SGEXTN/quickui/sgxthemecoloursetting.h \
    SGEXTN/userDefinedClasses/sgucentralmanagement.h
