rem goto done

mkdir .libs

cd cad
call make.bat
cd ..
cd generator
call make.bat
cd ..
cd geom
call make.bat
cd ..
cd octree
call make.bat
cd ..
cd reader
call make.bat
cd ..
cd utils
call make.bat
cd ..
cd writer
call make.bat
cd ..

:done
SET SRC_DIR=.
SET LIB_DIR=%SRC_DIR%\.libs
SET INCLUDES=-I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils
SET INCLUDES=%INCLUDES% -I%SRC_DIR%\cad\objects
SET LIBS=-lreader %DIME_LIB% -lcad -lcadcont -lgen -loctree -lgeom
SET LIBS=%LIBS% -lcadobjs -lwriter -lutils
SET LDFLAGS=-lm -L%LIB_DIR% %LIBS%
%CXX% %CXXFLAGS% %INCLUDES% cad2octree.cpp %LDFLAGS% -o cad2octree.exe