SET SRC_DIR=..
SET OBJS=entities\3DFace.o entities\Arc.o entities\Block.o entities\Circle.o
SET OBJS=%OBJS% entities\Ellipse.o entities\Entity.o entities\ExtrusionEntity.o
SET OBJS=%OBJS% entities\FaceEntity.o entities\Insert.o entities\Line.o
SET OBJS=%OBJS% entities\LWPolyline.o entities\Point.o entities\Polyline.o
SET OBJS=%OBJS% entities\Solid.o entities\Spline.o entities\Trace.o 
SET OBJS=%OBJS% entities\UnknownEntity.o entities\Vertex.o
SET INCLUDES= -I%SRC_DIR%\..\include
%CXX% %CXXFLAGS% %INCLUDES% -c 3DFace.cpp -o 3DFace.o
%CXX% %CXXFLAGS% %INCLUDES% -c Arc.cpp -o Arc.o
%CXX% %CXXFLAGS% %INCLUDES% -c Block.cpp -o Block.o
%CXX% %CXXFLAGS% %INCLUDES% -c Circle.cpp -o Circle.o
%CXX% %CXXFLAGS% %INCLUDES% -c Ellipse.cpp -o Ellipse.o
%CXX% %CXXFLAGS% %INCLUDES% -c Entity.cpp -o Entity.o
%CXX% %CXXFLAGS% %INCLUDES% -c ExtrusionEntity.cpp -o ExtrusionEntity.o
%CXX% %CXXFLAGS% %INCLUDES% -c FaceEntity.cpp -o FaceEntity.o
%CXX% %CXXFLAGS% %INCLUDES% -c Insert.cpp -o Insert.o
%CXX% %CXXFLAGS% %INCLUDES% -c Line.cpp -o Line.o
%CXX% %CXXFLAGS% %INCLUDES% -c LWPolyline.cpp -o LWPolyline.o
%CXX% %CXXFLAGS% %INCLUDES% -c Point.cpp -o Point.o
%CXX% %CXXFLAGS% %INCLUDES% -c Polyline.cpp -o Polyline.o
%CXX% %CXXFLAGS% %INCLUDES% -c Solid.cpp -o Solid.o
%CXX% %CXXFLAGS% %INCLUDES% -c Spline.cpp -o Spline.o
%CXX% %CXXFLAGS% %INCLUDES% -c Trace.cpp -o Trace.o
%CXX% %CXXFLAGS% %INCLUDES% -c UnknownEntity.cpp -o UnknownEntity.o
%CXX% %CXXFLAGS% %INCLUDES% -c Vertex.cpp -o Vertex.o
