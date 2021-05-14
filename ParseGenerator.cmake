set(LEX_INPUT "Lexer.lex")
set(LEX_CPP "Lexer.ll.cpp")
set(YACC_INPUT "Grammar.yacc")
set(YACC_CPP "Grammar.yy.cpp")
set(YACC_HPP "Grammar.yy.hpp")
set(INCLUDE_FOR_YACC_HEADER "#include \"ExpertSystemData.hpp\"")
set(PARSE_DIR "${CMAKE_SOURCE_DIR}/src/ExpertSystemLib/Parse")
set(YACC_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# generate lex/yacc parse when build
add_custom_target(parser_generator ALL
        COMMAND rm ${YACC_INCLUDE_DIR}/${YACC_HPP} ${LEX_CPP} ${YACC_CPP}
        COMMAND lex -o ${LEX_CPP} ${LEX_INPUT}
        COMMAND sed -i "" -- "s/register//g" ${LEX_CPP} #for compatibility with c++17
        COMMAND yacc -d -o ${YACC_CPP} ${YACC_INPUT}
        COMMAND echo ${INCLUDE_FOR_YACC_HEADER} | cat - ${YACC_HPP} > tmp && mv tmp ${YACC_HPP} #copy needed include into yacc header
        COMMAND mv ${YACC_HPP} ${YACC_INCLUDE_DIR}/Grammar.yy.hpp
        COMMENT "generate lex/yacc parser"
        WORKING_DIRECTORY ${PARSE_DIR}
        VERBATIM
        )
add_dependencies(${EXPERT_SYSTEM_LIB} parser_generator)

# generate lex/yacc parse when reload cmake
execute_process(COMMAND rm ${YACC_INCLUDE_DIR}/${YACC_HPP} ${LEX_CPP} ${YACC_CPP}
        WORKING_DIRECTORY ${PARSE_DIR}
        )
execute_process(COMMAND lex -o ${LEX_CPP} ${LEX_INPUT}
        WORKING_DIRECTORY ${PARSE_DIR}
        )
execute_process(COMMAND sed -i "" -- "s/register//g" ${LEX_CPP} #for compatibility with c++17
        WORKING_DIRECTORY ${PARSE_DIR}
        )
execute_process(COMMAND yacc -d -o ${YACC_CPP} ${YACC_INPUT}
        WORKING_DIRECTORY ${PARSE_DIR}
        )
file(WRITE ${YACC_INCLUDE_DIR}/${YACC_HPP} "${INCLUDE_FOR_YACC_HEADER}\n")
file(READ ${PARSE_DIR}/${YACC_HPP} YACC_HEADER)
file(APPEND ${YACC_INCLUDE_DIR}/${YACC_HPP} ${YACC_HEADER})
execute_process(COMMAND rm ${PARSE_DIR}/${YACC_HPP})
