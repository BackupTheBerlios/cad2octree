SET SRC_DIR=..
SET LIB=libreader.a
SET OBJS=dime_help.o dime_reader.o dxf_reader.o reader.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
SET INCLUDES= %INCLUDES% %DIME_INCL%
%CXX% %CXXFLAGS% %INCLUDES% -c dime_help.cpp -o dime_help.o
%CXX% %CXXFLAGS% %INCLUDES% -c dime_reader.cpp -o dime_reader.o
%CXX% %CXXFLAGS% %INCLUDES% -c dxf_reader.cpp -o dxf_reader.o
%CXX% %CXXFLAGS% %INCLUDES% -c reader.cpp -o reader.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs
