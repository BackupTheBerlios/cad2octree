SET SRC_DIR=..
SET OBJS=objects\Object.o objects\UnknownObject.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c Object.cpp -o Object.o
%CXX% %CXXFLAGS% %INCLUDES% -c UnknownObject.cpp -o UnknownObject.o
