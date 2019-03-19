cmake_minimum_required(VERSION 3.12)
project(TB7Grapher C)

set(CMAKE_C_STANDARD 11)

add_executable(TB7Grapher main.c lib/codeInterpreter/codeInterpreter.c lib/codeInterpreter/codeInterpreter.h lib/grapher/grapher.c lib/grapher/grapher.h lib/lexicalAnalyser/lexicalAnalyser.c lib/lexicalAnalyser/lexicalAnalyser.h lib/syntaxAnalyser/syntaxAnalyser.c lib/syntaxAnalyser/syntaxAnalyser.h lib/logger/log.c lib/logger/log.c lib/logger/log.h main.h lib/tokens.h test/test.c test/test.h lib/lib.h)

if (UNIX)
    find_package(SDL2 REQUIRED SDL2)
    target_link_libraries(TB7Grapher PRIVATE SDL2 m)
else()
    target_link_libraries(TB7Grapher m)
endif()

