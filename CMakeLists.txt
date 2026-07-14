cmake_minimum_required(VERSION 3.24)
project(cavansite VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.*
    include/*.*

    test/*.*
)
if (PROJECT_IS_TOP_LEVEL)
    find_package(QT NAMES Qt6 Qt5)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg)

    qt_standard_project_setup()
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOMOC ON)

    qt_add_executable(${PROJECT_NAME} ${SOURCES})

    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Svg
    )

    set(CAVANSITE_ADD_BREEZE all)
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
)

# defines
if (DEFINED CAVANSITE_USE_NAMESPACE)
    message(STATUS "CAVANSITE_USE_NAMESPACE set. Adding to PCH.")

    target_precompile_headers(${PROJECT_NAME}
        PUBLIC
            pch/namespace.hpp
    )
else()
    message(STATUS "CAVANSITE_USE_NAMESPACE not set. Not using the namespace.")
endif()

if (DEFINED CAVANSITE_ADD_BREEZE)
    message(STATUS "CAVANSITE_ADD_BREEZE set. Adding the Breeze theme.")

    include("cmake/breeze.cmake")
else()
    message(STATUS "CAVANSITE_ADD_BREEZE not set. Not adding Breeze.")
endif()

# libs
include(cmake/CPM.cmake)
CPMAddPackage("gh:Fryy55/aurora@1.1.3")
target_link_libraries(${PROJECT_NAME} PUBLIC Aurora)