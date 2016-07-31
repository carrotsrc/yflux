cmake_minimum_required(VERSION 2.8)
set( CLD ${CMAKE_CURRENT_LIST_DIR} )

set( SRC ${SRC}
         ${CLD}/MemSourceContainer.cpp
         ${CLD}/YfxToken.cpp
         ${CLD}/YfxSyntax.cpp
         ${CLD}/YfxFrontend.cpp
     PARENT_SCOPE)

