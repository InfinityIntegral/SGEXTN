# CMake file for SGEXTN

cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

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
set(QT_NO_PRIVATE_MODULE_WARNING ON)

set_property(DIRECTORY . PROPERTY GLOBAL_DEPENDS_NO_CYCLES ON)
set_property(DIRECTORY . PROPERTY REPORT_UNDEFINED_PROPERTIES ON)
set_property(DIRECTORY . PROPERTY TARGET_SUPPORTS_SHARED_LIBS ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("building in DEBUG mode, this should NOT be released")
else()
   add_compile_definitions(QT_NO_DEBUG_OUTPUT)
endif()

project(SGEXTN
    VERSION 6.0.0
    LANGUAGES CXX
)

add_library(SG_Containers SHARED)
target_compile_definitions(SG_Containers
    PRIVATE SG_BUILDING_CONTAINERS
    PUBLIC SG_USING_CONTAINERS
)
target_include_directories(SG_Containers
    PUBLIC "dll_defines"
    PUBLIC "SG_Containers/include"
)
target_sources(SG_Containers
    PRIVATE "SG_Containers/src/SG_Build_Containers.cpp"
    PRIVATE "SG_Containers/src/SGLCrash.cpp"
)

add_library(SG_Math SHARED)
target_compile_definitions(SG_Math
    PRIVATE SG_BUILDING_MATH
    PUBLIC SG_USING_MATH
)
target_include_directories(SG_Math
    PUBLIC "dll_defines"
    PUBLIC "SG_Math/include"
)
target_sources(SG_Math
    PRIVATE "SG_Math/src/sglfloatconstants.cpp"
    PRIVATE "SG_Math/src/sglfloatlimits.cpp"
    PRIVATE "SG_Math/src/sglfloatmath.cpp"
    PRIVATE "SG_Math/src/sglintlimits.cpp"
    PRIVATE "SG_Math/src/sglintmath.cpp"
    PRIVATE "SG_Math/src/sgllonglonglimits.cpp"
    PRIVATE "SG_Math/src/sgllonglongmath.cpp"
)

add_library(SG_Core SHARED)
target_compile_definitions(SG_Core
    PRIVATE SG_BUILDING_CORE
    PUBLIC SG_USING_CORE
)
target_include_directories(SG_Core
    PUBLIC "dll_defines"
    PUBLIC "SG_Core/include"
)
target_sources(SG_Core
    PRIVATE "SG_Core/src/SGXCentral.cpp"
    PRIVATE "SG_Core/src/SGXChar.cpp"
    PRIVATE "SG_Core/src/SGXColourHSLA.cpp"
    PRIVATE "SG_Core/src/SGXColourRGBA.cpp"
    PRIVATE "SG_Core/src/SGXDebug.cpp"
    PRIVATE "SG_Core/src/SGXIdentifier.cpp"
    PRIVATE "SG_Core/src/SGXRandomNumberGenerator.cpp"
    PRIVATE "SG_Core/src/SGXString.cpp"
    PRIVATE "SG_Core/src/SGXTimer.cpp"
    PRIVATE "SG_Core/src/SGXTimerQuickInterface.cpp"
    PRIVATE "SG_Core/src/SGXTimeStamp.cpp"
    PRIVATE "SG_Core/src/SGXVector2.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core Gui)
target_link_libraries(SG_Core
    PUBLIC SG_Containers
    PUBLIC SG_Math
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
)

add_library(SG_FileSystem SHARED)
target_compile_definitions(SG_FileSystem
    PRIVATE SG_BUILDING_FILESYSTEM
    PUBLIC SG_USING_FILESYSTEM
)
target_include_directories(SG_FileSystem
    PUBLIC "dll_defines"
    PUBLIC "SG_FileSystem/include"
)
target_sources(SG_FileSystem
    PRIVATE "SG_FileSystem/src/SGXFile.cpp"
    PRIVATE "SG_FileSystem/src/SGXFileBinUtilities.cpp"
    PRIVATE "SG_FileSystem/src/SGXFileSystem.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(SG_FileSystem
    PUBLIC SG_Containers
    PUBLIC SG_Core
    PRIVATE Qt6::Core
)

add_library(SG_Widgets SHARED)
target_compile_definitions(SG_Widgets
    PRIVATE SG_BUILDING_WIDGETS
    PUBLIC SG_USING_WIDGETS
)
target_include_directories(SG_Widgets
    PUBLIC "dll_defines"
    PUBLIC "SG_Widgets/include"
)
qt6_add_resources(SG_Widgets SG_Widgets_assets PREFIX "SGEXTN" BASE "SG_Widgets/assets" FILES
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
target_sources(SG_Widgets
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
target_link_libraries(SG_Widgets
    PUBLIC SG_Containers
    PUBLIC SG_Math
    PUBLIC SG_Core
    PUBLIC SG_FileSystem
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
)

add_library(SG_RI SHARED)
target_compile_definitions(SG_RI
    PRIVATE SG_BUILDING_RI
    PUBLIC SG_USING_RI
)
target_include_directories(SG_RI
    PUBLIC "dll_defines"
    PUBLIC "SG_RI/include"
)
find_package(Qt6 REQUIRED COMPONENTS ShaderTools)
qt6_add_shaders(SG_RI SG_RI_shaders PREFIX "SGEXTN" BASE "SG_RI/assets" FILES
    "SG_RI/assets/colourpicker.vert"
    "SG_RI/assets/colourpicker.frag"
    "SG_RI/assets/transparencyindicator.vert"
    "SG_RI/assets/transparencyindicator.frag"
)
target_sources(SG_RI
    PRIVATE "SG_RI/src/SGRBaseRenderer.cpp"
    PRIVATE "SG_RI/src/SGRColourPickerRenderer.cpp"
    PRIVATE "SG_RI/src/SGRColourPickerSyncer.cpp"
    PRIVATE "SG_RI/src/SGRCommandRequest.cpp"
    PRIVATE "SG_RI/src/SGRDataBuffer.cpp"
    PRIVATE "SG_RI/src/SGRElementBufferObject.cpp"
    PRIVATE "SG_RI/src/SGRRendererGenerator.cpp"
    PRIVATE "SG_RI/src/SGRRendererNode.cpp"
    PRIVATE "SG_RI/src/SGRRendererWidget.cpp"
    PRIVATE "SG_RI/src/SGRRenderingProgramme.cpp"
    PRIVATE "SG_RI/src/SGRTexture.cpp"
    PRIVATE "SG_RI/src/SGRTransparencyIndicatorRenderer.cpp"
    PRIVATE "SG_RI/src/SGRVertexBufferObject.cpp"
    PRIVATE "SG_RI/src/SGRVertexProperty.cpp"
    PRIVATE "SG_RI/src/SGWColourPicker.cpp"
    PRIVATE "SG_RI/src/SGWColourPickerWidget.cpp"
    PRIVATE "SG_RI/src/SGWColourPickerWidgetQuickInterface.cpp"
    PRIVATE "SG_RI/src/SGWThemeCustomisationPage.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 GuiPrivate)
target_link_libraries(SG_RI
    PUBLIC SG_Containers
    PUBLIC SG_Math
    PUBLIC SG_Core
    PUBLIC SG_FileSystem
    PUBLIC SG_Widgets
    PRIVATE Qt6::Core
    PRIVATE Qt6::Gui
    PRIVATE Qt6::Qml
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::GuiPrivate
)

add_library(EntryPoint_SG INTERFACE)
target_include_directories(EntryPoint_SG
    INTERFACE "EntryPoint_SG"
)

add_executable(InternalTest WIN32)
target_sources(InternalTest
    PRIVATE "internal_test/src/main.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(InternalTest
    PUBLIC SG_Containers
    PUBLIC SG_Math
    PUBLIC SG_Core
    PUBLIC SG_FileSystem
    PUBLIC SG_Widgets
    PUBLIC SG_RI
    PRIVATE EntryPoint_SG
    PRIVATE Qt6::Core
)
