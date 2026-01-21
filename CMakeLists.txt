include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/buildlah.cmake")
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)
BuildLah_use_default_settings()
project(SGEXTN VERSION 6.4.0 LANGUAGES CXX)
BuildLah_find_dependencies()
BuildLah_add_component(Containers DLL "Containers")

target_sources(Containers
  PRIVATE
    Containers/include/private_api/SGEXTN_Containers_PriorityQueue_impl.h
)
BuildLah_add_component(Math DLL "Math")
BuildLah_add_component(Core DLL "Core" Containers Math Qt6::Core Qt6::Gui)
BuildLah_add_component(FileSystem DLL "FileSystem" Containers Core Qt6::Core)
BuildLah_add_component(SGWidget DLL "SGWidget" Containers Math Core FileSystem Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::QuickDialogs2)
BuildLah_add_component(RendererInterface DLL "RendererInterface" Containers Math Core FileSystem SGWidget Qt6::Core Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 Qt6::QuickDialogs2 Qt6::GuiPrivate)
BuildLah_add_component(InternalTest GUI "InternalTest" Containers Math Core FileSystem SGWidget RendererInterface)
BuildLah_finalise_project()
# cmake --install build/Desktop_Qt_6_10_1-Release --config Release --prefix ../SGEXTN_install
