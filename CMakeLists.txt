cmake_minimum_required(VERSION 3.14)

project(hid-rp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

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

# generate a source file and build it to verify syntax
file(GLOB_RECURSE HEADER_FILES "${INCLUDES}/*.hpp")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/compilation_test.cpp" "")
foreach(HEADER_FILE ${HEADER_FILES})
    file(RELATIVE_PATH FILE_RELATIVE_PATH
        ${INCLUDES} ${HEADER_FILE}
    )
    file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/compilation_test.cpp"
        "#include \"${FILE_RELATIVE_PATH}\"\n"
    )
endforeach()
file(APPEND "${CMAKE_CURRENT_BINARY_DIR}/compilation_test.cpp"
    "\nint main() { return 0; }\n"
)
add_executable(${PROJECT_NAME}-verify ${CMAKE_CURRENT_BINARY_DIR}/compilation_test.cpp)
target_link_libraries(${PROJECT_NAME}-verify ${PROJECT_NAME})
