cmake_minimum_required(VERSION 3.17)

target_sources(expert_system PUBLIC
        Grammar.yy.cpp
        Lexer.ll.cpp
        )

# generate lex/yacc parse when build
add_custom_target(parser_generator ALL
        COMMAND lex -o ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.ll.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.lex
        COMMAND sed -i "" -- "s/register//g" ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.ll.cpp
        COMMAND yacc -o ${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yy.cpp -d ${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yacc
        COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yy.hpp ${INCLUDE_DIR}/Grammar.yy.hpp
        COMMENT "generate lex/yacc parser"
        VERBATIM
        )
add_dependencies(${PROJECT_NAME} parser_generator)

# generate lex/yacc parse when reload cmake
execute_process(COMMAND lex -o ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.ll.cpp ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.lex)
execute_process(COMMAND sed -i "" -- "s/register//g" ${CMAKE_CURRENT_SOURCE_DIR}/Lexer.ll.cpp) #for compatibility with c++17
execute_process(COMMAND yacc -o ${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yy.cpp -d ${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yacc)
execute_process(COMMAND mv ${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yy.hpp ${INCLUDE_DIR}/Grammar.yy.hpp)

