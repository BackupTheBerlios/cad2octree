# doc/graf/gen/Makefile
#

SUBDIRS = 
DEVEL_HOME = ../../..

TEX_FILE= castel.tex 
PRG= castel 

include $(DEVEL_HOME)/Makefile.incl

alltargets: 

$(TEX_FILE): $(PRG) 
	./$< 

$(PRG):
	$(CC) $@.cpp -o $@ 

clean:
	$(RM) $(PRG) *.bak *~

clean-all: clean 
	$(RM) $(TEX_FILE)
