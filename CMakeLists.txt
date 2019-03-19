cmake_minimum_required(VERSION 3.12)
project(TB7Grapher C)

set(CMAKE_C_STANDARD 11)

add_executable(TB7Grapher main.c lib/codeInterpreter/codeInterpreter.c lib/codeInterpreter/codeInterpreter.h lib/grapher/grapher.c lib/grapher/grapher.h lib/lexicalAnalyser/lexicalAnalyser.c lib/lexicalAnalyser/lexicalAnalyser.h lib/syntaxAnalyser/syntaxAnalyser.c lib/syntaxAnalyser/syntaxAnalyser.h lib/logger/log.c lib/logger/log.c lib/logger/log.h main.h lib/tokens.h test/test.c test/test.h lib/lib.h)

target_link_libraries(TB7Grapher m)
#if (UNIX)
 #   INCLUDE(FindPkgConfig)
#else()
 #   set(SDL2_IMAGE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/SDL2/include")
  #  set(SDL2_IMAGE_LIBRARY "${PROJECT_SOURCE_DIR}/SDL2/lib/SDL2_image.lib")
#endif()