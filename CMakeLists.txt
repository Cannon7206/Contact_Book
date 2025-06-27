cmake_minimum_required(VERSION 3.31)
project(Contact_Book)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)


find_package(Qt6 COMPONENTS
        Core
        Widgets
        REQUIRED)

add_executable(Contact_Book main.cpp
        Contact.h
        "Main WIndow.cpp"
        "Main WIndow.h")

target_link_libraries(Contact_Book
        Qt::Core
        Qt::Widgets
)