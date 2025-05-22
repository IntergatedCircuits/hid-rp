include(CPM)
CPMAddPackage("gh:catchorg/Catch2@3.5.4")
list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

include(CTest)
include(Catch)

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

add_executable(${PROJECT_NAME}-test)
target_sources(${PROJECT_NAME}-test
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/compilation_test.cpp
        descriptor_view.cpp
        formatter.cpp
        imported_descriptor.cpp
        keyboard.cpp
        mouse.cpp
        opaque.cpp
)
target_link_libraries(${PROJECT_NAME}-test
    PRIVATE
        Catch2::Catch2WithMain
        ${PROJECT_NAME}
)
catch_discover_tests(${PROJECT_NAME}-test)
