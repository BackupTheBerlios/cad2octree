cd container
call make.bat
cd ..
cd objects
call make.bat
cd ..

SET SRC_DIR=..
SET LIB=libcad.a
SET OBJS=cad_model.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c cad_model.cpp -o cad_model.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs