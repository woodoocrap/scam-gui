cmake_minimum_required(VERSION 3.10)


project(scam_gui)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_BUILD_TYPE Debug)

find_package(Qt5 COMPONENTS Widgets)


SET(
      SOURCE_FILES 
      
      main.cpp   
      canvas.cpp
      gitrepo.cpp
      mainwindow.cpp
      gitrepopicker.cpp
      canvasarea.cpp
      colorpicker.cpp
      signaturedialog.cpp
)

add_executable(scam_gui ${SOURCE_FILES})
target_link_libraries(scam_gui Qt5::Widgets git2)

