QT = core gui widgets opengl openglwidgets
QMAKE_CXXFLAGS_RELEASE = -O3 -flto -ffunction-sections -fdata-sections
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS = -flto -Wl,--gc-sections
DISTFILES = .gitignore LICENSE.txt README.md
SOURCES = misc/main.cpp
RESOURCES = assets.qrc

HEADERS +=
