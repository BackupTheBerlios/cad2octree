SUBDIRS =

all:	doxy 

doxy:	
	@DOXYGEN@ *.dox 2>doxy.log

doxy-latex:
	$(MAKE) -C latex

clean:
	$(RM) *~ *.log

clean-all: clean
	$(RM) -r html/ latex/
