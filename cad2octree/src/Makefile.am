SUBDIRS = cad geom octree generator reader utils writer .

LDADD = reader/libreader.a cad/libcad.a \
	cad/container/libcadcont.a generator/libgen.a octree/liboctree.a \
	geom/libgeom.a writer/libwriter.a cad/objects/libcadobjs.a \
	utils/libutils.a

bin_PROGRAMS = cad2octree # model_viewer geom_test fulltree std_lines stack_test
cad2octree_SOURCES = cad2octree.cpp
#model_viewer_SOURCES = model_viewer.cpp
#geom_test_SOURCES = geom_test.cpp
#fulltree_SOURCES = fulltree.cpp
#std_lines_SOURCES = std_lines.cpp
#stack_test_SOURCES = stack_test.cpp

all:	cad2octree
