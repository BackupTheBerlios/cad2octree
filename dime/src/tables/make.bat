SET SRC_DIR=..
SET OBJS=tables\LayerTable.o tables\Table.o tables\TableEntry.o
SET OBJS=%OBJS% tables\UCSTable.o tables\UnknownTable.o 
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c LayerTable.cpp -o LayerTable.o
%CXX% %CXXFLAGS% %INCLUDES% -c Table.cpp -o Table.o
%CXX% %CXXFLAGS% %INCLUDES% -c TableEntry.cpp -o TableEntry.o
%CXX% %CXXFLAGS% %INCLUDES% -c UCSTable.cpp -o UCSTable.o
%CXX% %CXXFLAGS% %INCLUDES% -c UnknownTable.cpp -o UnknownTable.o
