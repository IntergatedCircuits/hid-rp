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

# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# https://embeddedartistry.com/blog/2023/09/20/leveraging-your-toolchain-to-improve-security/
target_link_options(${PROJECT_NAME}-test
    PRIVATE
        #-fsanitize=address
        -fsanitize=signed-integer-overflow
        -fsanitize=bounds
)
target_compile_options(${PROJECT_NAME}-test
    PRIVATE
        -ftrivial-auto-var-init=pattern
        -fstack-protector-all
        #-fsanitize=address
        -fno-omit-frame-pointer
        #-fsanitize=undefined
        -fsanitize=signed-integer-overflow
        -fsanitize=bounds
        -Wall
        -Wextra
        -Werror
        -Wformat=2
        -Wsign-conversion
        -Wuninitialized
        -Wcast-qual
        #-Wshadow
        -Wimplicit-fallthrough
        -Wfloat-equal
        -Wstack-protector
        $<$<CXX_COMPILER_ID:GNU>:
            -fconcepts-diagnostics-depth=20
            #-fanalyzer
            -Wshift-overflow=2
            -Warray-bounds=2
            -Wstringop-overflow=4
            -Wuse-after-free=3
            -Wformat-overflow=2
            -Wformat-truncation=2
            -Wformat-signedness
            -Wlogical-op
            -Wduplicated-cond
            -Wduplicated-branches
            #-Wswitch-default
            -Wcast-align=strict
        >
        $<$<CXX_COMPILER_ID:Clang>:
            -Wshift-sign-overflow
            -Warray-bounds-pointer-arithmetic
            -Wformat-type-confusion
            -Wcast-align
            -Wconditional-uninitialized
            -Wloop-analysis
            -Wtautological-constant-in-range-compare
            -Wcomma
            -Wassign-enum
            -Wunreachable-code-aggressive
        >
)
