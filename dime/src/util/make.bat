SET SRC_DIR=..
SET OBJS=util\Array.o util\Box.o util\BSPTree.o util\Dict.o util\Linear.o
SET OBJS=%OBJS% util\MemHandler.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c Array.cpp -o Array.o
%CXX% %CXXFLAGS% %INCLUDES% -c Box.cpp -o Box.o
%CXX% %CXXFLAGS% %INCLUDES% -c BSPTree.cpp -o BSPTree.o
%CXX% %CXXFLAGS% %INCLUDES% -c Dict.cpp -o Dict.o
%CXX% %CXXFLAGS% %INCLUDES% -c Linear.cpp -o Linear.o
%CXX% %CXXFLAGS% %INCLUDES% -c MemHandler.cpp -o MemHandler.o
