cmake_minimum_required(VERSION 3.5)

project(activitykeeper LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

include_directories (${CMAKE_CURRENT_SOURCE_DIR}/if)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/rsc)

set(PROJECT_SOURCES
            inc/binfilehandler.h
            inc/confighandler.h
            inc/maindialog.h
            inc/mousemover.h
            inc/systemtrayicon.h
            inc/configwriter.h
            inc/mousehandler.h
            inc/config.h
            inc/point.h
            inc/appguimanager.h

            if/iconfigwriter.h
            if/imousehandler.h
            if/iconfighandler.h
            if/imousemover.h

            src/main.cpp
            src/confighandler.cpp
            src/maindialog.cpp
            src/mousemover.cpp
            src/systemtrayicon.cpp
            src/configwriter.cpp
            src/mousehandler.cpp
            src/appguimanager.cpp

            rsc/icon.qrc
)

set(APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/rsc/app_icon.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(activitykeeper
        WIN32
        ${PROJECT_SOURCES}
        ${APP_ICON}
    )
else()
    add_executable(activitykeeper
        WIN32
        ${PROJECT_SOURCES}
        ${APP_ICON}
    )
endif()

target_link_libraries(activitykeeper PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
