SET SRC_DIR=..
SET LIB=libwriter.a
SET OBJS=pot_writer.o writer.o xpm_writer.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c pot_writer.cpp -o pot_writer.o
%CXX% %CXXFLAGS% %INCLUDES% -c writer.cpp -o writer.o
%CXX% %CXXFLAGS% %INCLUDES% -c xpm_writer.cpp -o xpm_writer.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
