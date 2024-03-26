cmake_minimum_required(VERSION 3.5)

project(demo1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 静态库位置
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 动态库位置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin) # 可执行文件位置

add_definitions(-DSOFT_VERSION="v0.01")

execute_process(
  COMMAND git log -1 --format=%h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_HASH
  OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(-DGIT_HASH=\"${GIT_HASH}\")

execute_process(
  COMMAND git log --pretty=format:%cs -1
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_DATE
  OUTPUT_STRIP_TRAILING_WHITESPACE)
add_definitions(-DGIT_DATE=\"${GIT_DATE}\")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_AUTOUIC_SEARCH_PATHS ../ui)
set(CMAKE_AUTOUIC ON) # 如果ui文件和cpp文件不在同一个目录下，不能使用此项
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(
  Qt5
  COMPONENTS Core
  REQUIRED)
find_package(
  Qt5
  COMPONENTS Gui
  REQUIRED)
find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED)
find_package(
  Qt5
  COMPONENTS Network
  REQUIRED)
find_package(
  Qt5
  COMPONENTS PrintSupport
  REQUIRED)

# set (Project_UI  ${PROJECT_SOURCE_DIR}/mainwindow.ui)
set(Project_UI ../ui/mainwindow.ui)
qt5_wrap_ui(Project_UI_MOC ${Project_UI})

set(SOURCES main_window/main.cpp main_window/mainwindow.cpp ${Project_UI_MOC})
qt5_add_resources(SOURCES ../res/res.qrc)

if(WIN32)
  add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ../res/app_icon.rc)
else()
  add_executable(${PROJECT_NAME} ${SOURCES} )
endif()

target_link_libraries(
  ${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui
                          Qt5::PrintSupport)

string(TIMESTAMP COMPILE_TIME %Y%m%d_%H%M%S)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX
                                                 "_${GIT_DATE}_${GIT_HASH}_d")
set_target_properties(${PROJECT_NAME} PROPERTIES RELEASE_POSTFIX
                                                 "_${GIT_DATE}_${GIT_HASH}_r")
