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
top_srcdir = ../..

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
pkgdatadir = $(datadir)/libdime
pkglibdir = $(libdir)/libdime
pkgincludedir = $(includedir)/libdime
top_builddir = ../..

ACLOCAL = ${SHELL} /home/mahlersn/projs/dime/cfg/missing --run aclocal
AUTOCONF = ${SHELL} /home/mahlersn/projs/dime/cfg/missing --run autoconf
AUTOMAKE = ${SHELL} /home/mahlersn/projs/dime/cfg/missing --run automake
AUTOHEADER = ${SHELL} /home/mahlersn/projs/dime/cfg/missing --run autoheader

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
build_alias = 
build_triplet = i686-pc-linux-gnu
host_alias = 
host_triplet = i686-pc-linux-gnu
target_alias = 
target_triplet = i686-pc-linux-gnu
AMTAR = ${SHELL} /home/mahlersn/projs/dime/cfg/missing --run tar
AS = @AS@
AWK = gawk
BUILD_WITH_MSVC = false
CC = gcc
CPP = gcc -E
CXX = g++
CXXCPP = g++ -E
DEPDIR = .deps
DIME_BETA_VERSION = 1
DIME_BINARY_AGE = 0
DIME_COMPILER = g++
DIME_EXTRA_CFLAGS = -g -O2
DIME_EXTRA_CPPFLAGS = -I${prefix}/include
DIME_EXTRA_CXXFLAGS = -g -O2
DIME_EXTRA_LDFLAGS = -L${exec_prefix}/lib
DIME_EXTRA_LIBS = -ldime
DIME_INTERFACE_AGE = 0
DIME_MAJOR_VERSION = 0
DIME_MICRO_VERSION = 1
DIME_MINOR_VERSION = 9
DIME_MSVC_LIBC = 
DIME_VERSION = 0.9.1
DLLTOOL = @DLLTOOL@
ECHO = echo
EXEEXT = 
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
LIBFLAGS = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LT_AGE = 0
LT_CURRENT = 1
LT_RELEASE = 0.9
LT_REVISION = 0
MAINT = #
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = libdime
RANLIB = ranlib
STRIP = strip
SUFFIX = 
VERSION = 0.9.1
am__include = include
am__quote = 
install_sh = /home/mahlersn/projs/dime/cfg/install-sh

LIBS = 
INCLUDES = -I$(top_srcdir)/include

#noinst_LIBRARIES = util.lst
noinst_LTLIBRARIES = libutil.la

UtilSources = \
	Array.cpp Array.h \
	BSPTree.cpp BSPTree.h \
	Box.cpp Box.h \
	Dict.cpp Dict.h \
	Linear.cpp Linear.h \
	MemHandler.cpp MemHandler.h


libutil_la_SOURCES = \
	$(UtilSources)


util_lst_SOURCES = \
	$(UtilSources)


libutilincdir = $(includedir)/dime/util
libutilinc_HEADERS = \
	../../include/dime/util/Array.h \
	../../include/dime/util/BSPTree.h \
	../../include/dime/util/Box.h \
	../../include/dime/util/Dict.h \
	../../include/dime/util/Linear.h \
	../../include/dime/util/MemHandler.h

subdir = src/util
mkinstalldirs = $(SHELL) $(top_srcdir)/cfg/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/include/config.h
CONFIG_CLEAN_FILES =
LIBRARIES = $(noinst_LIBRARIES)

util_lst_AR = $(AR) cru
util_lst_LIBADD =
am_util_lst_OBJECTS = Array.$(OBJEXT) BSPTree.$(OBJEXT) Box.$(OBJEXT) \
	Dict.$(OBJEXT) Linear.$(OBJEXT) MemHandler.$(OBJEXT)
util_lst_OBJECTS = $(am_util_lst_OBJECTS)
LTLIBRARIES = $(noinst_LTLIBRARIES)

libutil_la_LDFLAGS =
libutil_la_LIBADD =
am_libutil_la_OBJECTS = Array.lo BSPTree.lo Box.lo Dict.lo Linear.lo \
	MemHandler.lo
libutil_la_OBJECTS = $(am_libutil_la_OBJECTS)

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)/include
CPPFLAGS = -DDIME_INTERNAL
LDFLAGS = 
depcomp = $(SHELL) $(top_srcdir)/cfg/depcomp
DEP_FILES = $(DEPDIR)/Array.Plo $(DEPDIR)/Array.Po \
	$(DEPDIR)/BSPTree.Plo $(DEPDIR)/BSPTree.Po \
	$(DEPDIR)/Box.Plo $(DEPDIR)/Box.Po \
	$(DEPDIR)/Dict.Plo $(DEPDIR)/Dict.Po \
	$(DEPDIR)/Linear.Plo $(DEPDIR)/Linear.Po \
	$(DEPDIR)/MemHandler.Plo $(DEPDIR)/MemHandler.Po
CXXCOMPILE = $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) \
	$(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS)
LTCXXCOMPILE = $(LIBTOOL) --mode=compile $(CXX) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CXXFLAGS) $(CXXFLAGS)
CXXLD = $(CXX)
CXXLINK = $(LIBTOOL) --mode=link $(CXXLD) $(AM_CXXFLAGS) $(CXXFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
CXXFLAGS = -g -O2
CFLAGS = -g -O2
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) --mode=compile $(CC) $(DEFS) $(DEFAULT_INCLUDES) \
	$(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(LIBTOOL) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
DIST_SOURCES = $(util_lst_SOURCES) $(libutil_la_SOURCES)
HEADERS = $(libutilinc_HEADERS)

DIST_COMMON = $(libutilinc_HEADERS) Makefile.am Makefile.in
SOURCES = $(util_lst_SOURCES) $(libutil_la_SOURCES)

all: all-am

.SUFFIXES:
.SUFFIXES: .cpp .lo .o .obj

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
$(srcdir)/Makefile.in: # Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  src/util/Makefile
Makefile: # $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status

AR = ar

clean-noinstLIBRARIES:
	-test -z "$(noinst_LIBRARIES)" || rm -f $(noinst_LIBRARIES)

clean-noinstLTLIBRARIES:
	-test -z "$(noinst_LTLIBRARIES)" || rm -f $(noinst_LTLIBRARIES)
libutil.la: $(libutil_la_OBJECTS) $(libutil_la_DEPENDENCIES) 
	$(CXXLINK)  $(libutil_la_LDFLAGS) $(libutil_la_OBJECTS) $(libutil_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

include $(DEPDIR)/Array.Plo
include $(DEPDIR)/Array.Po
include $(DEPDIR)/BSPTree.Plo
include $(DEPDIR)/BSPTree.Po
include $(DEPDIR)/Box.Plo
include $(DEPDIR)/Box.Po
include $(DEPDIR)/Dict.Plo
include $(DEPDIR)/Dict.Po
include $(DEPDIR)/Linear.Plo
include $(DEPDIR)/Linear.Po
include $(DEPDIR)/MemHandler.Plo
include $(DEPDIR)/MemHandler.Po

distclean-depend:
	-rm -rf $(DEPDIR)

.cpp.o:
	source='$<' object='$@' libtool=no \
	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
	$(CXXDEPMODE) $(depcomp) \
	$(CXXCOMPILE) -c -o $@ `test -f $< || echo '$(srcdir)/'`$<

.cpp.obj:
	source='$<' object='$@' libtool=no \
	depfile='$(DEPDIR)/$*.Po' tmpdepfile='$(DEPDIR)/$*.TPo' \
	$(CXXDEPMODE) $(depcomp) \
	$(CXXCOMPILE) -c -o $@ `cygpath -w $<`

.cpp.lo:
	source='$<' object='$@' libtool=yes \
	depfile='$(DEPDIR)/$*.Plo' tmpdepfile='$(DEPDIR)/$*.TPlo' \
	$(CXXDEPMODE) $(depcomp) \
	$(LTCXXCOMPILE) -c -o $@ `test -f $< || echo '$(srcdir)/'`$<
CXXDEPMODE = depmode=gcc
uninstall-info-am:

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || etags $(ETAGS_ARGS) $$tags  $$unique $(LISP)

GTAGS:
	here=`CDPATH=: && cd $(top_builddir) && pwd` \
	  && cd $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) $$here

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH

DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ../..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	$(mkinstalldirs) $(distdir)/../../include/dime/util
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
all-am: Makefile $(LIBRARIES) $(LTLIBRARIES) $(HEADERS)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(libutilincdir)

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

clean-am: clean-generic clean-libtool clean-noinstLIBRARIES \
	clean-noinstLTLIBRARIES mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-compile distclean-depend \
	distclean-generic distclean-libtool distclean-tags

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am: install-libutilincHEADERS

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

uninstall-am: uninstall-info-am uninstall-libutilincHEADERS

.PHONY: GTAGS all all-am check check-am clean clean-generic \
	clean-libtool clean-noinstLIBRARIES clean-noinstLTLIBRARIES \
	distclean distclean-compile distclean-depend distclean-generic \
	distclean-libtool distclean-tags distdir dvi dvi-am info \
	info-am install install-am install-data install-data-am \
	install-exec install-exec-am install-info install-info-am \
	install-libutilincHEADERS install-man install-strip \
	installcheck installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool tags uninstall \
	uninstall-am uninstall-info-am uninstall-libutilincHEADERS


util.lst: Makefile $(util_lst_OBJECTS)
	@echo "Linking util.lst..."; \
	rm -f $@; \
	for i in $(util_lst_OBJECTS); do echo $$i >>$@; done

install-libutilincHEADERS: $(libutilinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libutilincdir)
	@list='$(libutilinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libutilincdir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libutilincdir)/$$f; \
	done

uninstall-libutilincHEADERS:
	@$(NORMAL_UNINSTALL)
	@list='$(libutilinc_HEADERS)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(libutilincdir)/$$f"; \
	  rm -f $(DESTDIR)$(libutilincdir)/$$f; \
	done
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
