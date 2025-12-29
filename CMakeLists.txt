include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/buildlah.cmake")
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
BuildLah_use_default_settings()
project(SGEXTN VERSION 6.2.0 LANGUAGES CXX)
BuildLah_find_dependencies()
BuildLah_add_component(SG_Containers DLL "SG_Containers" SG_BUILDING_CONTAINERS SG_USING_CONTAINERS "SGEXTN")
BuildLah_add_component(SG_Math DLL "SG_Math" SG_BUILDING_MATH SG_USING_MATH "SGEXTN")
BuildLah_add_component(SG_Core DLL "SG_Core" SG_BUILDING_CORE SG_USING_CORE "SGEXTN" SG_Containers SG_Math Qt6::Core Qt6::Gui)
BuildLah_add_component(SG_FileSystem DLL "SG_FileSystem" SG_BUILDING_FILESYSTEM SG_USING_FILESYSTEM "SGEXTN" SG_Containers SG_Core Qt6::Core)
BuildLah_add_component(SG_Widgets DLL "SG_Widgets" SG_BUILDING_WIDGETS SG_USING_WIDGETS "SGEXTN" SG_Containers SG_Math SG_Core SG_FileSystem Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::QuickDialogs2)
BuildLah_add_component(SG_RI DLL "SG_RI" SG_BUILDING_RI SG_USING_RI "SGEXTN" SG_Containers SG_Math SG_Core SG_FileSystem SG_Widgets Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::QuickDialogs2 Qt6::GuiPrivate)
qt6_add_library(EntryPoint_SG INTERFACE MANUAL_FINALIZATION)
target_include_directories(EntryPoint_SG
    INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint_SG>"
    INTERFACE "$<INSTALL_INTERFACE:include/EntryPoint_SG>"
)
qt6_finalize_target(EntryPoint_SG)
BuildLah_add_component(InternalTest GUI "internal_test" "" "" "SGEXTN" SG_Containers SG_Math SG_Core SG_FileSystem SG_Widgets SG_RI EntryPoint_SG)
install(TARGETS SG_Containers SG_Math SG_Core SG_FileSystem SG_Widgets SG_RI EntryPoint_SG
    EXPORT SG_ALL_Targets
    RUNTIME DESTINATION lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    FRAMEWORK DESTINATION lib
    INCLUDES DESTINATION include
)
install(DIRECTORY dll_defines/ DESTINATION include/dll_defines)
install(DIRECTORY SG_Containers/include/ DESTINATION include/SG_Containers/include)
install(DIRECTORY SG_Math/include/ DESTINATION include/SG_Math/include)
install(DIRECTORY SG_Core/include/ DESTINATION include/SG_Core/include)
install(DIRECTORY SG_FileSystem/include/ DESTINATION include/SG_FileSystem/include)
install(DIRECTORY SG_Widgets/include/ DESTINATION include/SG_Widgets/include)
install(DIRECTORY SG_RI/include/ DESTINATION include/SG_RI/include)
install(DIRECTORY EntryPoint_SG/ DESTINATION include/EntryPoint_SG)
install(EXPORT SG_ALL_Targets
    NAMESPACE SGEXTN::
    DESTINATION lib/cmake/SGEXTN
)
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/SGEXTNConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/SGEXTNConfig.cmake"
    INSTALL_DESTINATION lib/cmake/SGEXTN
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/SGEXTNConfig.cmake"
    DESTINATION lib/cmake/SGEXTN
)
install(FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/buildlah.cmake"
    DESTINATION lib/cmake/SGEXTN
)
# cmake --install build/Desktop_Qt_6_10_1-Release --config Release --prefix ../SGEXTN_install

