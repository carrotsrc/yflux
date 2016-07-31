cmake_minimum_required(VERSION 2.8)
set( CLD ${CMAKE_CURRENT_LIST_DIR} )

set( SRC ${SRC})
add_subdirectory(ast)
add_subdirectory(front)


set( SRC ${SRC}
         ${CLD}/YfxContext.cpp
         ${CLD}/entry.cpp 
    PARENT_SCOPE)


