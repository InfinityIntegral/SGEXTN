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
target_compile_definitions(Containers PRIVATE SG_BUILDING_CONTAINERS)
target_include_directories(Containers
    PUBLIC "private_api"
    PUBLIC "SG_Containers/include"
)
target_sources(Containers
    PRIVATE "SG_Containers/src/SG_Build_Containers.cpp"
    PRIVATE "SG_Containers/src/SGLCrash.cpp"
)

add_library(Math SHARED)
target_compile_definitions(Math PRIVATE SG_BUILDING_MATH)
target_include_directories(Math
    PUBLIC "private_api"
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
target_compile_definitions(Core PRIVATE SG_BUILDING_CORE)
target_include_directories(Core
    PUBLIC "private_api"
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

add_executable(InternalTest WIN32)
target_compile_definitions(InternalTest PRIVATE SG_BUILDING_INTERNALTEST)
target_sources(InternalTest
    PRIVATE "internal_test/src/main.cpp"
)
find_package(Qt6 REQUIRED COMPONENTS Core)
target_link_libraries(InternalTest
    PUBLIC Containers
    PUBLIC Math
    PUBLIC Core
    PRIVATE Qt6::Core
)
