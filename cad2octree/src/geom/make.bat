SET SRC_DIR=..
SET LIB=libgeom.a
SET OBJS=geom_point.o geom_vec.o line.o node_index.o node_vec.o polygon.o spline.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c geom_point.cpp -o geom_point.o
%CXX% %CXXFLAGS% %INCLUDES% -c geom_vec.cpp -o geom_vec.o
%CXX% %CXXFLAGS% %INCLUDES% -c line.cpp -o line.o
%CXX% %CXXFLAGS% %INCLUDES% -c node_index.cpp -o node_index.o
%CXX% %CXXFLAGS% %INCLUDES% -c node_vec.cpp -o node_vec.o
%CXX% %CXXFLAGS% %INCLUDES% -c polygon.cpp -o polygon.o
%CXX% %CXXFLAGS% %INCLUDES% -c spline.cpp -o spline.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
