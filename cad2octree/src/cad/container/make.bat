SET SRC_DIR=..\..
SET LIB=libcadcont.a
SET OBJS=faces.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c faces.cpp -o faces.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
