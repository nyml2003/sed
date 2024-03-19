cmake_minimum_required(VERSION 3.0)
project(sed)

set(CMAKE_CXX_STANDARD 17)

# llvm config
set(LLVM_DIR "/usr/lib/llvm-14/cmake")
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
include_directories("/usr/lib/llvm-14/include")
separate_arguments(LLVM_DEFINITIONS NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS})

# flex and bison config
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
BISON_TARGET(parser src/Driver/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)
FLEX_TARGET(scanner src/Driver/scanner.l ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/AST)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Context)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/Driver)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/AST/Expression)
include_directories()
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable -Wno-unused-value -Wno-unused-label -Wno-unused-local-typedefs -Wno-unused-private-field")

add_executable(sed main.cpp
        ${llvm_libs}
        ${BISON_parser_OUTPUTS}
        ${FLEX_scanner_OUTPUTS}
        src/Driver/Driver.cpp
        src/Driver/Driver.hpp
        src/AST/Expression/ast_expression_base.cpp
        src/AST/Expression/ast_expression_base.hpp
        src/AST/ast_node_base.cpp
        src/AST/ast_node_base.hpp
        src/AST/Expression/ast_expression_int32.cpp
        src/AST/Expression/ast_expression_int32.hpp
        src/AST/Expression/ast_expression_float32.cpp
        src/AST/Expression/ast_expression_float32.hpp
        src/AST/Expression/ast_expression_identifier.cpp
        src/AST/Expression/ast_expression_identifier.hpp
        src/AST/Expression/ast_expression_unary_expression.cpp
        src/AST/Expression/ast_expression_unary_expression.hpp
        src/AST/Expression/ast_expression_operator.hpp
        src/AST/Expression/ast_expression_boolean.cpp
        src/AST/Expression/ast_expression_boolean.hpp
        src/AST/Expression/ast_expression_binary_expression.cpp
        src/AST/Expression/ast_expression_binary_expression.hpp
        src/AST/ast_node_compilation_unit.cpp
        src/AST/ast_node_compilation_unit.hpp
        src/AST/ast_node_declaration.cpp
        src/AST/ast_node_declaration.hpp
        src/AST/ast_node_inner_type.hpp
        src/AST/ast_node_decorator.hpp
        src/AST/ast_node_definition.cpp
        src/AST/ast_node_definition.hpp
        src/Context/context.hpp
        src/Context/message.hpp
        src/Context/message.cpp
        src/Context/llvm_assist_context.cpp
        src/Context/llvm_assist_context.hpp
        src/Context/analyze_context.cpp
        src/Context/analyze_context.hpp
        src/AST/Expression/ast_expression_left_value.cpp
        src/AST/Expression/ast_expression_left_value.hpp
        src/AST/Expression/ast_expression_initial_value.cpp
        src/AST/Expression/ast_expression_initial_value.hpp
        src/AST/ast_node_block.cpp
        src/AST/ast_node_block.hpp
        src/AST/ast_node_function_definition.cpp
        src/AST/ast_node_function_definition.hpp
        src/AST/ast_node_assignment_statement.cpp
        src/AST/ast_node_assignment_statement.hpp
        src/AST/ast_node_expression_statement.cpp
        src/AST/ast_node_expression_statement.hpp
        src/AST/ast_node_if_statement.cpp
        src/AST/ast_node_if_statement.hpp
        src/AST/ast_node_while_statement.cpp
        src/AST/ast_node_while_statement.hpp
        src/AST/ast_node_break_statement.cpp
        src/AST/ast_node_break_statement.hpp
        src/AST/ast_node_continue_statement.cpp
        src/AST/ast_node_continue_statement.hpp
        src/AST/ast_node_return_statement.cpp
        src/AST/ast_node_return_statement.hpp
        src/AST/Expression/ast_expression_undefined.cpp
        src/AST/Expression/ast_expression_undefined.hpp

)


add_custom_target(
        run
        COMMAND sed -
        DEPENDS sed
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
        clean-all
        COMMAND ${CMAKE_BUILD_TOOL} clean
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_clean.cmake
)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(sed
        LLVM
)

enable_testing()

file(GLOB TEST_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/tests ${CMAKE_CURRENT_SOURCE_DIR}/tests/*)

foreach (TEST_DIR ${TEST_DIRS})
    set(TEST_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/in.sy)

    set (TEST_MD ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.md)

    set (TEST_IR ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.ll)

    set(TEST_ERROR ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/error.txt)
    set (TEST_EXE ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.exe)
    set (TEST_ASM ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_DIR}/out.s)

    if (NOT EXISTS ${TEST_INPUT})
        file(WRITE ${TEST_INPUT} "")
    endif ()
    if (NOT EXISTS ${TEST_MD})
        file(WRITE ${TEST_MD} "")
    endif ()
    if (NOT EXISTS ${TEST_ERROR})
        file(WRITE ${TEST_ERROR} "")
    endif ()
    if (NOT EXISTS ${TEST_IR})
        file(WRITE ${TEST_IR} "")
    endif ()
    if (NOT EXISTS ${TEST_ASM})
        file(WRITE ${TEST_ASM} "")
    endif ()
    if (NOT EXISTS ${TEST_EXE})
        file(WRITE ${TEST_EXE} "")
    endif ()
    
    add_test(
            NAME ${TEST_DIR}
            COMMAND sed ${TEST_INPUT} ${TEST_MD} ${TEST_ERROR}  ${TEST_IR}
            )

    add_test(
            NAME ${TEST_DIR}_toAssembly
            COMMAND llc ${TEST_IR} -o ${TEST_ASM}
    )

    add_test(
            NAME ${TEST_DIR}_toExe
            COMMAND clang ${TEST_ASM} -o ${TEST_EXE}
    )

    set_tests_properties(${TEST_DIR} PROPERTIES
            TIMEOUT 10
    )
endforeach ()