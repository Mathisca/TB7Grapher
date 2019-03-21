 cmake_minimum_required(VERSION 3.12)
 project(TB7Grapher C)

 set(CMAKE_C_STANDARD 11)

 add_executable(TB7Grapher main.c lib/codeInterpreter/codeInterpreter.c lib/codeInterpreter/codeInterpreter.h lib/tokens.h)


     target_link_libraries(TB7Grapher m )
