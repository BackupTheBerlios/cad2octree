SET SRC_DIR=.
SET LIB=libdime.a
SET LIB_DIR=..\lib
SET LIBS=%LIBS% libentities.a libutil.a
SET OBJS=Base.o Basic.o Input.o Layer.o Model.o Output.o RecordHolder.o State.o

SET OBJECTS= %OBJS%
cd entities
call make
cd ..
SET OBJECTS= %OBJECTS% %OBJS%
cd records
call make
cd ..
SET OBJECTS= %OBJECTS% %OBJS%
cd sections
call make
cd ..
SET OBJECTS= %OBJECTS% %OBJS%
cd tables
call make
cd ..
SET OBJECTS= %OBJECTS% %OBJS%
cd util
call make
cd ..
SET OBJECTS= %OBJECTS% %OBJS%

SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c Base.cpp -o Base.o
%CXX% %CXXFLAGS% %INCLUDES% -c Basic.cpp -o Basic.o
%CXX% %CXXFLAGS% %INCLUDES% -c Input.cpp -o Input.o
%CXX% %CXXFLAGS% %INCLUDES% -c Layer.cpp -o Layer.o
%CXX% %CXXFLAGS% %INCLUDES% -c Model.cpp -o Model.o
%CXX% %CXXFLAGS% %INCLUDES% -c Output.cpp -o Output.o
%CXX% %CXXFLAGS% %INCLUDES% -c RecordHolder.cpp -o RecordHolder.o
%CXX% %CXXFLAGS% %INCLUDES% -c State.cpp -o State.o
ar rc %LIB_DIR%\%LIB% %OBJECTS%
