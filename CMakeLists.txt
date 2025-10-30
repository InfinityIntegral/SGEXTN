# CMake file for SGEXTN

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(CMAKE_ERROR_DEPRECATED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_SHARED_LIBRARY_ENABLE_EXPORTS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
if(APPLE)
    set(CMAKE_BUILD_RPATH "@loader_path")
elseif(UNIX)
    set(CMAKE_BUILD_RPATH "$ORIGIN")
endif()
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
set(CMAKE_INCLUDE_CURRENT_DIR OFF)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE OFF)
set(CMAKE_OPTIMIZE_DEPENDENCIES ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set_property(DIRECTORY . PROPERTY GLOBAL_DEPENDS_NO_CYCLES ON)
set_property(DIRECTORY . PROPERTY REPORT_UNDEFINED_PROPERTIES ON)
set_property(DIRECTORY . PROPERTY TARGET_SUPPORTS_SHARED_LIBS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("building in DEBUG mode, this should NOT be released")
endif()

project(SGEXTN
    VERSION 6.0.0
    LANGUAGES CXX
)

add_library(Containers SHARED)
target_compile_definitions(Containers
    PRIVATE SG_BUILDING_CONTAINERS
    PUBLIC SG_USING_CONTAINERS
)
target_include_directories(Containers
    PUBLIC "dll_defines"
    PUBLIC "SG_Containers/include"
)
target_sources(Containers
    PRIVATE "SG_Containers/src/SG_Build_Containers.cpp"
    PRIVATE "SG_Containers/src/SGLCrash.cpp"
)

add_library(Math SHARED)
target_compile_definitions(Math
    PRIVATE SG_BUILDING_MATH
    PUBLIC SG_USING_MATH
)
target_include_directories(Math
    PUBLIC "dll_defines"
    PUBLIC "SG_Math/include"
)
target_sources(Math
    PRIVATE "SG_Math/src/sglfloatconstants.cpp"
    PRIVATE "SG_Math/src/sglfloatlimits.cpp"
    PRIVATE "SG_Math/src/sglfloatmath.cpp"
    PRIVATE "SG_Math/src/sglintlimits.cpp"
    PRIVATE "SG_Math/src/sglintmath.cpp"
    PRIVATE "SG_Math/src/sgllonglonglimits.cpp"
    PRIVATE "SG_Math/src/sgllonglongmath.cpp"
)

add_library(Core SHARED)
target_compile_definitions(Core
    PRIVATE SG_BUILDING_CORE
    PUBLIC SG_USING_CORE
)
target_include_directories(Core
    PUBLIC "dll_defines"
    PUBLIC "SG_Core/include"
)
target_sources(Core
    PRIVATE "SG_Core/src/SGXCentral.cpp"
    PRIVATE "SG_Core/src/SGXChar.cpp"
    PRIVATE "SG_Core/src/SGXColourHSLA.cpp"
    PRIVATE "SG_Core/src/SGXColourRGBA.cpp"
    PRIVATE "SG_Core/src/SGXIdentifier.cpp"
    PRIVATE "SG_Core/src/SGXRandomNumberGenerator.cpp"
    PRIVATE "SG_Core/src/SGXString.cpp"
    PRIVATE "SG_Core/src/SGXTimer.cpp"
    PRIVATE "SG_Core/src/SGXTimerQuickInterface.cpp"
    PRIVATE "SG_Core/src/SGXTimeStamp.cpp"
    PRIVATE "SG_Core/src/SGXVector2.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
target_link_libraries(Core
    PUBLIC Containers
    PUBLIC Math
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
)

add_library(FileSystem SHARED)
target_compile_definitions(FileSystem
    PRIVATE SG_BUILDING_FILESYSTEM
    PUBLIC SG_USING_FILESYSTEM
)
target_include_directories(FileSystem
    PUBLIC "dll_defines"
    PUBLIC "SG_FileSystem/include"
)
target_sources(FileSystem
    PRIVATE "SG_FileSystem/src/SGXFile.cpp"
    PRIVATE "SG_FileSystem/src/SGXFileBinUtilities.cpp"
    PRIVATE "SG_FileSystem/src/SGXFileSystem.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(FileSystem
    PUBLIC Containers
    PUBLIC Core
    PRIVATE Qt6::Core
)

add_library(Widgets SHARED)
target_compile_definitions(Widgets
    PRIVATE SG_BUILDING_WIDGETS
    PUBLIC SG_USING_WIDGETS
)
target_include_directories(Widgets
    PUBLIC "dll_defines"
    PUBLIC "SG_Widgets/include"
)
qt6_add_resources(Widgets SG_Widgets_assets PREFIX "SGEXTN" BASE "SG_Widgets/assets" FILES
    "SG_Widgets/assets/FileDownload.qml"
    "SG_Widgets/assets/FileUpload.qml"
    "SG_Widgets/assets/Root.qml"
    "SG_Widgets/assets/SGWBlankWidget.qml"
    "SG_Widgets/assets/SGWColourPickerWidget.qml"
    "SG_Widgets/assets/SGWIconButton.qml"
    "SG_Widgets/assets/SGWIconLabel.qml"
    "SG_Widgets/assets/SGWLongInput.qml"
    "SG_Widgets/assets/SGWLongLabel.qml"
    "SG_Widgets/assets/SGWMultiTouchReceiver.qml"
    "SG_Widgets/assets/SGWPageBackground.qml"
    "SG_Widgets/assets/SGWParent.qml"
    "SG_Widgets/assets/SGWRoot.qml"
    "SG_Widgets/assets/SGWScrollView.qml"
    "SG_Widgets/assets/SGWSequentialLongLabel.qml"
    "SG_Widgets/assets/SGWSequentialScrollView.qml"
    "SG_Widgets/assets/SGWSingleTouchReceiver.qml"
    "SG_Widgets/assets/SGWStatusBar.qml"
    "SG_Widgets/assets/SGWTextButton.qml"
    "SG_Widgets/assets/SGWTextInput.qml"
    "SG_Widgets/assets/SGWTextLabel.qml"
    "SG_Widgets/assets/SingScript.sg"
)
target_sources(Widgets
    PRIVATE "SG_Widgets/src/SGRImage.cpp"
    PRIVATE "SG_Widgets/src/SGRScreenshotCallback.cpp"
    PRIVATE "SG_Widgets/src/SGWBackground.cpp"
    PRIVATE "SG_Widgets/src/SGWBlankWidget.cpp"
    PRIVATE "SG_Widgets/src/SGWButton.cpp"
    PRIVATE "SG_Widgets/src/SGWCustomisationPageControl.cpp"
    PRIVATE "SG_Widgets/src/SGWDefaultFonts.cpp"
    PRIVATE "SG_Widgets/src/SGWFontSizeCustomisationPage.cpp"
    PRIVATE "SG_Widgets/src/SGWIconButton.cpp"
    PRIVATE "SG_Widgets/src/SGWIconLabel.cpp"
    PRIVATE "SG_Widgets/src/SGWInput.cpp"
    PRIVATE "SG_Widgets/src/SGWLabel.cpp"
    PRIVATE "SG_Widgets/src/SGWLongInput.cpp"
    PRIVATE "SG_Widgets/src/SGWLongLabel.cpp"
    PRIVATE "SG_Widgets/src/SGWMultiTouchReceiver.cpp"
    PRIVATE "SG_Widgets/src/SGWNotify.cpp"
    PRIVATE "SG_Widgets/src/SGWPageBackground.cpp"
    PRIVATE "SG_Widgets/src/SGWParent.cpp"
    PRIVATE "SG_Widgets/src/SGWRoot.cpp"
    PRIVATE "SG_Widgets/src/SGWScrollView.cpp"
    PRIVATE "SG_Widgets/src/SGWSequentialLongLabel.cpp"
    PRIVATE "SG_Widgets/src/SGWSequentialScrollView.cpp"
    PRIVATE "SG_Widgets/src/SGWSingCorrectCustomisationPage.cpp"
    PRIVATE "SG_Widgets/src/SGWSingleTouchReceiver.cpp"
    PRIVATE "SG_Widgets/src/SGWStatusBar.cpp"
    PRIVATE "SG_Widgets/src/SGWTextButton.cpp"
    PRIVATE "SG_Widgets/src/SGWTextInput.cpp"
    PRIVATE "SG_Widgets/src/SGWTextLabel.cpp"
    PRIVATE "SG_Widgets/src/SGWType.cpp"
    PRIVATE "SG_Widgets/src/SGWWidget.cpp"
    PRIVATE "SG_Widgets/src/SGWWidgetInitialisation.cpp"
    PRIVATE "SG_Widgets/src/SGWWidgetQuickInterface.cpp"
    PRIVATE "SG_Widgets/src/SGXFileDownloader.cpp"
    PRIVATE "SG_Widgets/src/SGXFileUploader.cpp"
    PRIVATE "SG_Widgets/src/SGXFontSizeCustomisation.cpp"
    PRIVATE "SG_Widgets/src/SGXQuickInterface.cpp"
    PRIVATE "SG_Widgets/src/SGXQuickResizer.cpp"
    PRIVATE "SG_Widgets/src/SGXResizer.cpp"
    PRIVATE "SG_Widgets/src/SGXSingCorrectCore.cpp"
    PRIVATE "SG_Widgets/src/SGXSingCorrectCustomisation.cpp"
    PRIVATE "SG_Widgets/src/SGXSingCorrectQuickInterface.cpp"
    PRIVATE "SG_Widgets/src/SGXThemeColours.cpp"
    PRIVATE "SG_Widgets/src/SGXThemeColoursCustomisation.cpp"
    PRIVATE "SG_Widgets/src/SGXThemeColoursSetting.cpp"
    PRIVATE "SG_Widgets/src/SGXTouchEvent.cpp"
    PRIVATE "SG_Widgets/include/private_api_Widgets/SGXQuickResizer.h"
    PRIVATE "SG_Widgets/include/private_api_Widgets/SGXThemeColourSetting.h"
    PRIVATE "SG_Widgets/include/private_api_Widgets/SGXSingCorrectQuickInterface.h"
)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)
target_link_libraries(Widgets
    PUBLIC Containers
    PUBLIC Math
    PUBLIC Core
    PUBLIC FileSystem
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
)

add_library(EntryPoint_SG INTERFACE)
target_include_directories(EntryPoint_SG
    INTERFACE "EntryPoint_SG"
)

add_executable(InternalTest WIN32)
target_compile_definitions(InternalTest
    PRIVATE SG_BUILDING_INTERNALTEST
)
target_sources(InternalTest
    PRIVATE "internal_test/src/main.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(InternalTest
    PUBLIC Containers
    PUBLIC Math
    PUBLIC Core
    PUBLIC FileSystem
    PUBLIC Widgets
    PRIVATE EntryPoint_SG
    PRIVATE Qt6::Core
)
