SET SRC_DIR=..
SET LIB=libutils.a
SET OBJS=filename.o global.o timer.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c filename.cpp -o filename.o
%CXX% %CXXFLAGS% %INCLUDES% -c global.cpp -o global.o
%CXX% %CXXFLAGS% %INCLUDES% -c timer.cpp -o timer.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
