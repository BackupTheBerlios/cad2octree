SET SRC_DIR=..\..
SET LIB=libcadobjs.a
SET OBJS=cad_object.o b_spline.o face.o plane.o point.o quadrilateral.o triangle.o
SET INCLUDES= -I%SRC_DIR% -I%SRC_DIR%\geom -I%SRC_DIR%\utils -I%SRC_DIR%\cad\objects
%CXX% %CXXFLAGS% %INCLUDES% -c cad_object.cpp -o cad_object.o
%CXX% %CXXFLAGS% %INCLUDES% -c b_spline.cpp -o b_spline.o
%CXX% %CXXFLAGS% %INCLUDES% -c face.cpp -o face.o
%CXX% %CXXFLAGS% %INCLUDES% -c plane.cpp -o plane.o
%CXX% %CXXFLAGS% %INCLUDES% -c point.cpp -o point.o
%CXX% %CXXFLAGS% %INCLUDES% -c quadrilateral.cpp -o quadrilateral.o
%CXX% %CXXFLAGS% %INCLUDES% -c triangle.cpp -o triangle.o
ar rc %LIB% %OBJS%
move %LIB% %SRC_DIR%\.libs\
