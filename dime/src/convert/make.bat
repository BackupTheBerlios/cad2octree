SET SRC_DIR=..
SET OBJS=convert\3dface.o convert\arc.o convert\circle.o convert\convert.o 
SET OBJS=%OBJ% convert\ellipse.o convert\layerdata.o convert\line.o
SET OBJS=%OBJ% convert\linesegment.o convert\lwpolyline.o convert\point.o
SET OBJS=%OBJ% convert\polyline.o convert\solid.o convert\trace.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c 3dface.cpp -o 3dface.o
%CXX% %CXXFLAGS% %INCLUDES% -c arc.cpp -o arc.o
%CXX% %CXXFLAGS% %INCLUDES% -c convert.cpp -o convert.o
%CXX% %CXXFLAGS% %INCLUDES% -c ellipse.cpp -o ellipse.o
%CXX% %CXXFLAGS% %INCLUDES% -c layerdata.cpp -o layerdata.o
%CXX% %CXXFLAGS% %INCLUDES% -c line.cpp -o line.o
%CXX% %CXXFLAGS% %INCLUDES% -c linesegment.cpp -o linesegment.o
%CXX% %CXXFLAGS% %INCLUDES% -c lwpolyline.cpp -o lwpolyline.o
%CXX% %CXXFLAGS% %INCLUDES% -c point.cpp -o point.o
%CXX% %CXXFLAGS% %INCLUDES% -c polyline.cpp -o polyline.o
%CXX% %CXXFLAGS% %INCLUDES% -c solid.cpp -o solid.o
%CXX% %CXXFLAGS% %INCLUDES% -c trace.cpp -o trace.o
