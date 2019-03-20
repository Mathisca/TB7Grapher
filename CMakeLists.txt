 cmake_minimum_required(VERSION 3.12)
 project(TB7Grapher C)

 set(CMAKE_C_STANDARD 11)

 add_executable(TB7Grapher main.c lib/codeInterpreter/codeInterpreter.c lib/codeInterpreter/codeInterpreter.h lib/lexicalAnalyser/lexicalAnalyser.c lib/lexicalAnalyser/lexicalAnalyser.h lib/syntaxAnalyser/syntaxAnalyser.c lib/syntaxAnalyser/syntaxAnalyser.h lib/logger/log.c lib/logger/log.c lib/logger/log.h main.h lib/tokens.h test/test.c test/test.h lib/lib.h lib/grapher/guiManager.c lib/grapher/guiManager.h lib/grapher/guiRenderer.c lib/grapher/guiRenderer.h lib/grapher/inputHandler.c lib/grapher/inputHandler.h lib/grapher/grapher.c lib/grapher/grapher.h)

 if (UNIX)
     INCLUDE(FindPkgConfig)

     PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
     PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
     PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

     set(THREADS_PREFER_PTHREAD_FLAG ON)
     find_package(Threads REQUIRED)

     INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
     TARGET_LINK_LIBRARIES(TB7Grapher ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES} Threads::Threads m)

     TARGET_LINK_LIBRARIES(TB7Grapher ${SDL2_LIBRARIES})
 else ()
     target_link_libraries(TB7Grapher m)
 endif ()

