# Makefile.in generated automatically by automake 1.5 from Makefile.am.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



SHELL = /bin/sh

srcdir = .
top_srcdir = ..

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/cad2octree
pkglibdir = $(libdir)/cad2octree
pkgincludedir = $(includedir)/cad2octree
top_builddir = ..

ACLOCAL = ${SHELL} /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/missing --run aclocal
AUTOCONF = ${SHELL} /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/missing --run autoconf
AUTOMAKE = ${SHELL} /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/missing --run automake
AUTOHEADER = ${SHELL} /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/missing --run autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = i686-suse-linux
host_triplet = i686-suse-linux
AMTAR = ${SHELL} /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/missing --run tar
AS = @AS@
AWK = gawk
CC = gcc
CXX = g++
CXXCPP = g++ -E
CXXFLAGS = -I/home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/src -I/home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/src/utils -I/home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/src/geom -I/home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/src/cad/objects -g -O2 -I/usr/local/include
DEPDIR = .deps
DIME_INCLNAME = dime/entities/Polyline.h
DIME_LIBNAME = libdime.la
DLLTOOL = @DLLTOOL@
DOXYGEN = /usr/local/bin/doxygen
ECHO = echo
EXEEXT = 
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LIBS =  -L/usr/local/lib -ldime
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = cad2octree
PDFLATEX = /usr/bin/pdflatex
RANLIB = ranlib
SRC_DIR = /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/src
STRIP = strip
TOP_DIR = /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1
VERSION = 0.2.1
am__include = include
am__quote = 
install_sh = /home/mahlersn/projs/cad2octree-0.2.1/cad2octree-0.2.1/install-sh

DOCUMENT = ausarbeitung
subdir = doc
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES =
DIST_SOURCES =
DIST_COMMON = Makefile.am Makefile.in
all: all-am

.SUFFIXES:

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  doc/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status
uninstall-info-am:
tags: TAGS
TAGS:


DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    $(mkinstalldirs) "$(distdir)/$$dir"; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir) \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile

installdirs:

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libtool mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-generic distclean-libtool

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am:

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic mostlyclean-libtool

uninstall-am: uninstall-info-am

.PHONY: all all-am check check-am clean clean-generic clean-libtool \
	distclean distclean-generic distclean-libtool distdir dvi \
	dvi-am info info-am install install-am install-data \
	install-data-am install-exec install-exec-am install-info \
	install-info-am install-man install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-generic \
	mostlyclean-libtool uninstall uninstall-am uninstall-info-am


all:	pdf

pdf:	clean-pdf $(DOCUMENT).pdf 

clean:
	$(RM) *.aux *.log *~ *.blg *.toc *.lof *.lot *.bbl *.out

clean-pdf:
	$(RM) $(DOCUMENT).pdf

clean-all: clean clean-pdf
	$(RM) 

%.pdf : %.tex
	/usr/bin/pdflatex $*
	bibtex $*
	while egrep -q '^LaTeX Warning: There were undefined references' \
		$*.log\
		 >/dev/null 2>&1 ; do \
		/usr/bin/pdflatex $* ; \
	done
	/usr/bin/pdflatex $*

%.eps : %.png
	convert $< $@
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
