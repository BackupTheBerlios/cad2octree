DOCUMENT = ausarbeitung

all:	pdf

pdf:	clean-pdf $(DOCUMENT).pdf 

clean:
	$(RM) *.aux *.log *~ *.blg *.toc *.lof *.lot *.bbl *.out

clean-pdf:
	$(RM) $(DOCUMENT).pdf

clean-all: clean clean-pdf
	$(RM) 

%.pdf : %.tex
	@PDFLATEX@ $*
	bibtex $*
	while egrep -q '^LaTeX Warning: There were undefined references' \
		$*.log\
		 >/dev/null 2>&1 ; do \
		@PDFLATEX@ $* ; \
	done
	@PDFLATEX@ $*

%.eps : %.png
	convert $< $@
