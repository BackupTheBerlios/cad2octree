SET SRC_DIR=..
SET OBJS=sections\BlocksSection.o sections\ClassesSection.o sections\EntitiesSection.o
SET OBJS=%OBJS% sections\HeaderSection.o sections\ObjectsSection.o
SET OBJS=%OBJS% sections\Section.o sections\TablesSection.o sections\UnknownSection.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c BlocksSection.cpp -o BlocksSection.o
%CXX% %CXXFLAGS% %INCLUDES% -c ClassesSection.cpp -o ClassesSection.o
%CXX% %CXXFLAGS% %INCLUDES% -c EntitiesSection.cpp -o EntitiesSection.o
%CXX% %CXXFLAGS% %INCLUDES% -c HeaderSection.cpp -o HeaderSection.o
%CXX% %CXXFLAGS% %INCLUDES% -c ObjectsSection.cpp -o ObjectsSection.o
%CXX% %CXXFLAGS% %INCLUDES% -c Section.cpp -o Section.o
%CXX% %CXXFLAGS% %INCLUDES% -c TablesSection.cpp -o TablesSection.o
%CXX% %CXXFLAGS% %INCLUDES% -c UnknownSection.cpp -o UnknownSection.o
