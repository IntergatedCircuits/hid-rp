cmake_minimum_required(VERSION 3.21)

project(hid-rp
    LANGUAGES CXX
    VERSION 1.0.0
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)

set(INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}")

# add HID usage tables
include(ExternalProject)

set(HID_USAGE_TABLES_URL "https://github.com/IntergatedCircuits/hid-usage-tables.git" CACHE STRING "HID Usage Tables repository")
set(HID_USAGE_TABLES_REV "bbfc07ca2078c57c2848b5b7ce09e0b9e8d76689" CACHE STRING "HID Usage Tables commit hash")

set(USAGE_TABLES_OUTPUT_DIR ${INCLUDES}/hid/page)

find_package(Python 3 REQUIRED)
if(Python_VERSION_MAJOR LESS 3)
    message(FATAL_ERROR "Python 3 is required for usage tables code generation.")
endif()

ExternalProject_Add(hid-usage-tables
    PREFIX ${CMAKE_BINARY_DIR}/hid-usage-tables
    GIT_REPOSITORY ${HID_USAGE_TABLES_URL}
    GIT_TAG ${HID_USAGE_TABLES_REV}
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E chdir <SOURCE_DIR> ${Python_EXECUTABLE} <SOURCE_DIR>/src/hid/codegen/cpp.py ${USAGE_TABLES_OUTPUT_DIR}
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    UPDATE_DISCONNECTED TRUE
)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(get_cpm)
CPMAddPackage("gh:IntergatedCircuits/bitfilled#e108749cfd6d21946c4ff4aa5139229658d7a025")

# the library itself
add_library(${PROJECT_NAME} INTERFACE)
add_dependencies(${PROJECT_NAME} hid-usage-tables)

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDES}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${PROJECT_NAME}
    INTERFACE
        bitfilled
)

add_subdirectory(hid-rd-reader)

option(HID_RP_TESTS "hid-rp: enable unit testing" ${PROJECT_IS_TOP_LEVEL})
if(HID_RP_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
