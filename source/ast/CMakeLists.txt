cmake_minimum_required(VERSION 2.8)
set( CLD ${CMAKE_CURRENT_LIST_DIR} )

set( SRC ${SRC}
         ${CLD}/ExprAst.cpp
         ${CLD}/VariableAst.cpp
         ${CLD}/FunctionAst.cpp
         ${CLD}/visitors/PrinterVisitor.cpp
     PARENT_SCOPE)

