SET SRC_DIR=..
SET LIB=libgen.a
SET OBJS=gen_help.o oct_gen.o scan_line.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c gen_help.cpp -o gen_help.o
%CXX% %CXXFLAGS% %INCLUDES% -c oct_gen.cpp -o oct_gen.o
%CXX% %CXXFLAGS% %INCLUDES% -c scan_line.cpp -o scan_line.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
