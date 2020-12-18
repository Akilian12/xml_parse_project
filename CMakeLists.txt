cmake_minimum_required(VERSION 3.17)
project(xml_parse_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(xml_parse_project main.cpp)
find_package(PkgConfig REQUIRED)
pkg_check_modules(libxml_pkg REQUIRED IMPORTED_TARGET libxml++-3.0)
pkg_check_modules(xerces_pkg REQUIRED IMPORTED_TARGET xerces-c)
pkg_check_modules(pugixml_pkg REQUIRED IMPORTED_TARGET pugixml)
find_package(Catch2 REQUIRED)
find_package(tinyxml2 REQUIRED)

target_link_libraries(xml_parse_project Catch2::Catch2)
target_link_libraries(xml_parse_project PkgConfig::libxml_pkg)
target_link_libraries(xml_parse_project tinyxml2::tinyxml2)
target_link_libraries(xml_parse_project PkgConfig::xerces_pkg)
target_link_libraries(xml_parse_project PkgConfig::pugixml_pkg)