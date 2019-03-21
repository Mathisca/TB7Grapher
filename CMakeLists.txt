 cmake_minimum_required(VERSION 3.12)
 project(TB7Grapher C)

 set(CMAKE_C_STANDARD 11)

 add_executable(TB7Grapher main.c lib/lexicalAnalyser/lexicalAnalyser.c lib/lexicalAnalyser/lexicalAnalyser.h lib/lib.h lib/tokens.h test/test.c test/test.h main.c main.h)

     target_link_libraries(TB7Grapher m )

