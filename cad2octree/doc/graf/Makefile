# doc/graf/Makefile
#

SUBDIRS = gen 
DEVEL_HOME = ../..

EPS= csg.eps fill_beg.eps fill_queue_1.eps fill_queue_2.eps fill_queue_3.eps \
	fill_queue_4.eps fill_queue_end.eps fill_stack_1.eps fill_stack_2.eps\
	fill_stack_3.eps fill_stack_4.eps fill_stack_end.eps naz.eps \
	pos_quad_alt.eps pos_quad_classic.eps primitivinst.eps quadtree.eps \
	quad_ref.eps scanline_alt.eps scanline_bresenham.eps \
	schnittstelle_oct.eps verschgeo.eps zellzerl.eps z_muster.eps 

include $(DEVEL_HOME)/Makefile.incl

all: $(EPS)

clean:
	$(RM) $(EPS) *~

clean-all: clean

