SET SRC_DIR=..
SET LIB=liboctree.a
SET OBJS=fill_oct.o idx_holder.o index_oct.o oct_struct.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c fill_oct.cpp -o fill_oct.o
%CXX% %CXXFLAGS% %INCLUDES% -c idx_holder.cpp -o idx_holder.o
%CXX% %CXXFLAGS% %INCLUDES% -c index_oct.cpp -o index_oct.o
%CXX% %CXXFLAGS% %INCLUDES% -c oct_struct.cpp -o oct_struct.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
