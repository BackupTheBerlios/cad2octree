SET SRC_DIR=..
SET OBJS=classes\Class.o classes\UnknownClass.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c Class.cpp -o Class.o
%CXX% %CXXFLAGS% %INCLUDES% -c UnknownClass.cpp -o UnknownClass.o
