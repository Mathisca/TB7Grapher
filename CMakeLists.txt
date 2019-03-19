cmake_minimum_required(VERSION 3.12)
project(TB7Grapher C)

set(CMAKE_C_STANDARD 11)

add_executable(TB7Grapher main.c lib/codeInterpreter/codeInterpreter.c lib/codeInterpreter/codeInterpreter.h lib/grapher/grapher.c lib/grapher/grapher.h lib/lexicalAnalyser/lexicalAnalyser.c lib/lexicalAnalyser/lexicalAnalyser.h lib/syntaxAnalyser/syntaxAnalyser.c lib/syntaxAnalyser/syntaxAnalyser.h lib/logger/log.c lib/logger/log.c lib/logger/log.h main.h lib/tokens.h test/test.c test/test.h lib/lib.h)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})