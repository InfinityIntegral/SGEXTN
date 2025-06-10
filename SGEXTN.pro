QT = core gui widgets opengl openglwidgets
QMAKE_CXXFLAGS_RELEASE = -O3 -flto -ffunction-sections -fdata-sections
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS = -flto -Wl,--gc-sections
DISTFILES = .gitignore LICENSE.txt README.md
SOURCES = misc/main.cpp \
    primitives/sgxcolourhsla.cpp \
    primitives/sgxcolourrgba.cpp \
    primitives/sgxidentifier.cpp \
    primitives/sgxtimestamp.cpp \
    primitives/sgxvector2.cpp
RESOURCES = assets.qrc

HEADERS += \
    primitives/sgxcolourhsla.h \
    primitives/sgxcolourrgba.h \
    primitives/sgxidentifier.h \
    primitives/sgxtimestamp.h \
    primitives/sgxvector2.h
