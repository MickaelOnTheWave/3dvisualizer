cmake_minimum_required(VERSION 3.5)

project(3dVisualizer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS KITGL_SUPPORT_GLFW=0)
add_subdirectory(libs)

set(PROJECT_SOURCES
        src/main.cpp
        src/MainWindow.cpp
        src/MainWindow.h
        src/MainWindow.ui
        src/RendererGlWindow.h src/RendererGlWindow.cpp
)

qt_add_executable(3dVisualizer
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_compile_definitions(3dVisualizer PRIVATE QT_NO_OPENGL_FUNCTIONS)

target_link_libraries(3dVisualizer PRIVATE Qt6::Widgets Qt6::OpenGLWidgets glad RenderLib)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.3dVisualizer)
endif()
set_target_properties(3dVisualizer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 3dVisualizer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3dVisualizer)
endif()
