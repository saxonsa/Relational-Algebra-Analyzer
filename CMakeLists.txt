cmake_minimum_required(VERSION 3.20)
project(RelationalAlgebraAnalyzer C)

set(CMAKE_C_STANDARD 11)

add_executable(RelationalAlgebraAnalyzer analyzer.c lexer.c lexer.h SLR.h rule.h rule.c)
