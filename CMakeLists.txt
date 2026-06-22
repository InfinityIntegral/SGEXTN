cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
set(CMAKE_FIND_NO_INSTALL_PREFIX true)
project(SGEXTN LANGUAGES CXX VERSION 7.0.0 DESCRIPTION "SGEXTN - Singaporean-made Extension to the C++ Core Language, currently work in progress, is written to provide an alternative to the Standard Template Library that is easy to use, more consistent between different platforms, faster to lint and compile, and provides a cross platform framework for developing applications using the capabilities of Simple DirectMedia Layer 3 and AccessKit" HOMEPAGE_URL "https://infinityintegral.github.io/SGEXTN/readme/readme")
set(BuildLah_internal_v_installFolder "${CMAKE_SOURCE_DIR}/cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuildLah.cmake")
BuildLah_addComponent(
    NAME Containers
    TYPE LIBRARY
    ROOT_FOLDER "Containers"
)
BuildLah_addComponent(
    NAME Math
    TYPE LIBRARY
    ROOT_FOLDER "Math"
)
BuildLah_addComponent(
    NAME CoreText
    TYPE LIBRARY
    ROOT_FOLDER "CoreText"
    DEPENDENCIES INTERNAL Math FORWARD Containers
)
BuildLah_addComponent(
    NAME SingEmbed
    TYPE LIBRARY
    ROOT_FOLDER "SingEmbed"
    DEPENDENCIES INTERNAL Containers FORWARD CoreText
)
BuildLah_addComponent(
    NAME Utilities
    TYPE LIBRARY
    ROOT_FOLDER "Utilities"
    DEPENDENCIES INTERNAL Math FORWARD Containers CoreText
)
BuildLah_addComponent(
    NAME SeerattraNum
    TYPE LIBRARY
    ROOT_FOLDER "SeerattraNum"
    DEPENDENCIES FORWARD Containers
)
BuildLah_addComponent(
    NAME InternalTest
    TYPE GUI_APP
    ROOT_FOLDER "InternalTest"
    DEPENDENCIES INTERNAL Containers Math CoreText SingEmbed Utilities SeerattraNum
)
BuildLah_finaliseProject()
