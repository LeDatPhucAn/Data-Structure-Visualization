cmake_minimum_required(VERSION 4.0)

project(DATA_STRUCTURE_VISUALIZATION)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    "Data Structure Visualization/source/Animation.cpp"
    "Data Structure Visualization/source/Button.cpp"
    "Data Structure Visualization/source/Edge.cpp"
    "Data Structure Visualization/source/Graph.cpp"
    "Data Structure Visualization/source/HashTable.cpp"
    "Data Structure Visualization/source/Main.cpp"
    "Data Structure Visualization/source/Menu.cpp"
    "Data Structure Visualization/source/SceneHandler.cpp"
    "Data Structure Visualization/source/SinglyLinkedList.cpp"
    "Data Structure Visualization/source/SinglyLinkedListUI.cpp"
    "Data Structure Visualization/source/Treap.cpp"
    "Data Structure Visualization/source/TreapUI.cpp"
    "Data Structure Visualization/source/UI.cpp"
)

find_package(raylib CONFIG REQUIRED)

add_executable(output ${SOURCES})

target_include_directories(output PRIVATE "Data Structure Visualization/header")

target_link_libraries(output PRIVATE raylib)

set(ASSETS_DIR "Data Structure Visualization/assets")

file(COPY ${ASSETS_DIR} DESTINATION ${CMAKE_BINARY_DIR})


