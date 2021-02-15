cmake_minimum_required(VERSION 3.17)

target_sources(expert_system PUBLIC
        Grammar.yy.cpp
        Lexer.ll.cpp
        )


set(LEX_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/Lexer.lex")
set(LEX_CPP_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/Lexer.ll.cpp")
set(YACC_INPUT "${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yacc")
set(YACC_CPP_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yy.cpp")
set(YACC_HPP_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/Grammar.yy.hpp")

set(INCLUDE_FOR_YACC_HEADER "#include \"MainExpressionsList.hpp\"")

# generate lex/yacc parse when build
add_custom_target(parser_generator ALL
        COMMAND lex -o ${LEX_CPP_OUTPUT} ${LEX_INPUT}
        COMMAND sed -i "" -- "s/register//g" ${LEX_CPP_OUTPUT} #for compatibility with c++17
        COMMAND yacc -o ${YACC_CPP_OUTPUT} -d ${YACC_INPUT}
        COMMAND echo ${INCLUDE_FOR_YACC_HEADER} | cat - ${YACC_HPP_OUTPUT} > tmp && mv tmp ${YACC_HPP_OUTPUT} #copy needed include into yacc header
        COMMAND mv ${YACC_HPP_OUTPUT} ${YACC_INCLUDE_DIR}/Grammar.yy.hpp
        COMMENT "generate lex/yacc parser"
        VERBATIM
        )
add_dependencies(${PROJECT_NAME} parser_generator)

# generate lex/yacc parse when reload cmake
execute_process(COMMAND lex -o ${LEX_CPP_OUTPUT} ${LEX_INPUT})
execute_process(COMMAND sed -i "" -- "s/register//g" ${LEX_CPP_OUTPUT}) #for compatibility with c++17
execute_process(COMMAND yacc -o ${YACC_CPP_OUTPUT} -d ${YACC_INPUT})
execute_process(COMMAND mv ${YACC_HPP_OUTPUT} ${YACC_INCLUDE_DIR}/Grammar.yy.hpp)
