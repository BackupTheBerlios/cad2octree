SET SRC_DIR=..
SET OBJS=records\DoubleRecord.o records\FloatRecord.o records\HexRecord.o
SET OBJS=%OBJS% records\Int8Record.o records\Int16Record.o records\Int32Record.o
SET OBJS=%OBJS% records\StringRecord.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c DoubleRecord.cpp -o DoubleRecord.o
%CXX% %CXXFLAGS% %INCLUDES% -c FloatRecord.cpp -o FloatRecord.o
%CXX% %CXXFLAGS% %INCLUDES% -c Int8Record.cpp -o Int8Record.o
%CXX% %CXXFLAGS% %INCLUDES% -c Int16Record.cpp -o Int16Record.o
%CXX% %CXXFLAGS% %INCLUDES% -c Int32Record.cpp -o Int32Record.o
%CXX% %CXXFLAGS% %INCLUDES% -c HexRecord.cpp -o HexRecord.o
%CXX% %CXXFLAGS% %INCLUDES% -c Record.cpp -o Record.o
%CXX% %CXXFLAGS% %INCLUDES% -c StringRecord.cpp -o StringRecord.o
