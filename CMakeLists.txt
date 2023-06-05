cmake_minimum_required(VERSION 3.14)

project(hid-rp LANGUAGES CXX)

include(GNUInstallDirs)

find_package(Python 3 REQUIRED)
if(Python_VERSION_MAJOR LESS 3)
    message(FATAL_ERROR "Python 3 is required for usage tables code generation.")
endif()

set(INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}")

set(USAGE_TABLES_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/hid-usage-tables)
set(USAGE_TABLES_OUTPUT_DIR ${INCLUDES}/hid/page)

execute_process(
    COMMAND python ${USAGE_TABLES_SRC_DIR}/src/hid/codegen/cpp.py ${USAGE_TABLES_OUTPUT_DIR}
    WORKING_DIRECTORY ${USAGE_TABLES_SRC_DIR}
)

set(EXPORT_NAMESPACE "${PROJECT_NAME}::")

add_library(${PROJECT_NAME} INTERFACE)
add_library(${EXPORT_NAMESPACE}${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${INCLUDES}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
