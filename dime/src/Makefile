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
pkgdatadir = $(datadir)/libdime
pkglibdir = $(libdir)/libdime
pkgincludedir = $(includedir)/libdime
top_builddir = ..

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

CLEANFILES = \
        dime0.dll \
        dime0.pdb \
        dime0.exp


DISTCLEANFILES = \
        ii_files/*.ii


SUBDIRS = classes entities objects records sections tables util convert .

INCLUDES = -I$(top_srcdir)/include

#lib_LIBRARIES = dime0.lib
lib_LTLIBRARIES = libdime.la

DimeSources = \
	Base.cpp Base.h \
	Basic.cpp Basic.h \
	Input.cpp Input.h \
	Layer.cpp Layer.h \
	Model.cpp Model.h \
	Output.cpp Output.h \
	RecordHolder.cpp RecordHolder.h \
	State.cpp State.h


libdime_la_LIBADD = \
	classes/libclasses.la entities/libentities.la objects/libobjects.la \
	records/librecords.la sections/libsections.la tables/libtables.la \
	util/libutil.la convert/libconvert.la


libdime_la_LDFLAGS = \
	-version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)


dime0_lib_LIBADD = \
	classes/classes.lst entities/entities.lst objects/objects.lst \
	records/records.lst sections/sections.lst tables/tables.lst \
	util/util.lst convert/convert.lst


libdime_la_SOURCES = \
	$(DimeSources)


dime0_lib_SOURCES = \
	$(DimeSources)


libdimeincdir = $(includedir)/dime
libdimeinc_HEADERS = \
	../include/dime/Base.h \
	../include/dime/Basic.h \
	../include/dime/Input.h \
	../include/dime/Layer.h \
	../include/dime/Model.h \
	../include/dime/Output.h \
	../include/dime/RecordHolder.h \
	../include/dime/State.h

subdir = src
mkinstalldirs = $(SHELL) $(top_srcdir)/cfg/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/include/config.h
CONFIG_CLEAN_FILES =
LIBRARIES = $(lib_LIBRARIES)

dime0_lib_AR = $(AR) cru
dime0_lib_DEPENDENCIES = classes/classes.lst \
	entities/entities.lst objects/objects.lst records/records.lst \
	sections/sections.lst tables/tables.lst util/util.lst \
	convert/convert.lst
am_dime0_lib_OBJECTS = Base.$(OBJEXT) \
	Basic.$(OBJEXT) Input.$(OBJEXT) Layer.$(OBJEXT) Model.$(OBJEXT) \
	Output.$(OBJEXT) RecordHolder.$(OBJEXT) State.$(OBJEXT)
dime0_lib_OBJECTS = \
	$(am_dime0_lib_OBJECTS)
LTLIBRARIES = $(lib_LTLIBRARIES)

libdime_la_DEPENDENCIES = classes/libclasses.la \
	entities/libentities.la objects/libobjects.la \
	records/librecords.la sections/libsections.la \
	tables/libtables.la util/libutil.la convert/libconvert.la
am_libdime_la_OBJECTS = Base.lo Basic.lo Input.lo Layer.lo \
	Model.lo Output.lo RecordHolder.lo State.lo
libdime_la_OBJECTS = $(am_libdime_la_OBJECTS)

DEFS = -DHAVE_CONFIG_H
DEFAULT_INCLUDES =  -I. -I$(srcdir) -I$(top_builddir)/include
CPPFLAGS = -DDIME_INTERNAL
LDFLAGS = 
LIBS = 
depcomp = $(SHELL) $(top_srcdir)/cfg/depcomp
DEP_FILES = $(DEPDIR)/Base.Plo $(DEPDIR)/Base.Po \
	$(DEPDIR)/Basic.Plo $(DEPDIR)/Basic.Po \
	$(DEPDIR)/Input.Plo $(DEPDIR)/Input.Po \
	$(DEPDIR)/Layer.Plo $(DEPDIR)/Layer.Po \
	$(DEPDIR)/Model.Plo $(DEPDIR)/Model.Po \
	$(DEPDIR)/Output.Plo $(DEPDIR)/Output.Po \
	$(DEPDIR)/RecordHolder.Plo \
	$(DEPDIR)/RecordHolder.Po $(DEPDIR)/State.Plo \
	$(DEPDIR)/State.Po
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
DIST_SOURCES = $(dime0_lib_SOURCES) \
	$(libdime_la_SOURCES)
HEADERS = $(libdimeinc_HEADERS)


RECURSIVE_TARGETS = info-recursive dvi-recursive install-info-recursive \
	uninstall-info-recursive all-recursive install-data-recursive \
	install-exec-recursive installdirs-recursive install-recursive \
	uninstall-recursive check-recursive installcheck-recursive
DIST_COMMON = $(libdimeinc_HEADERS) Makefile.am Makefile.in
DIST_SUBDIRS = $(SUBDIRS)
SOURCES = $(dime0_lib_SOURCES) $(libdime_la_SOURCES)

all: all-recursive

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
	  $(AUTOMAKE) --gnu  src/Makefile
Makefile: # $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status

AR = ar
install-libLIBRARIES: $(lib_LIBRARIES)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libdir)
	@list='$(lib_LIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(libdir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(libdir)/$$p; \
	  else :; fi; \
	done
	@$(POST_INSTALL)
	@list='$(lib_LIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(RANLIB) $(DESTDIR)$(libdir)/$$p"; \
	    $(RANLIB) $(DESTDIR)$(libdir)/$$p; \
	  else :; fi; \
	done

uninstall-libLIBRARIES:
	@$(NORMAL_UNINSTALL)
	@list='$(lib_LIBRARIES)'; for p in $$list; do \
	  echo " rm -f $(DESTDIR)$(libdir)/$$p"; \
	  rm -f $(DESTDIR)$(libdir)/$$p; \
	done

clean-libLIBRARIES:
	-test -z "$(lib_LIBRARIES)" || rm -f $(lib_LIBRARIES)
install-libLTLIBRARIES: $(lib_LTLIBRARIES)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libdir)
	@list='$(lib_LTLIBRARIES)'; for p in $$list; do \
	  if test -f $$p; then \
	    echo " $(LIBTOOL) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$p $(DESTDIR)$(libdir)/$$p"; \
	    $(LIBTOOL) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$p $(DESTDIR)$(libdir)/$$p; \
	  else :; fi; \
	done

uninstall-libLTLIBRARIES:
	@$(NORMAL_UNINSTALL)
	@list='$(lib_LTLIBRARIES)'; for p in $$list; do \
	  echo " $(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(libdir)/$$p"; \
	  $(LIBTOOL) --mode=uninstall rm -f $(DESTDIR)$(libdir)/$$p; \
	done

clean-libLTLIBRARIES:
	-test -z "$(lib_LTLIBRARIES)" || rm -f $(lib_LTLIBRARIES)
libdime.la: $(libdime_la_OBJECTS) $(libdime_la_DEPENDENCIES) 
	$(CXXLINK) -rpath $(libdir) $(libdime_la_LDFLAGS) $(libdime_la_OBJECTS) $(libdime_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT) core *.core

distclean-compile:
	-rm -f *.tab.c

include $(DEPDIR)/Base.Plo
include $(DEPDIR)/Base.Po
include $(DEPDIR)/Basic.Plo
include $(DEPDIR)/Basic.Po
include $(DEPDIR)/Input.Plo
include $(DEPDIR)/Input.Po
include $(DEPDIR)/Layer.Plo
include $(DEPDIR)/Layer.Po
include $(DEPDIR)/Model.Plo
include $(DEPDIR)/Model.Po
include $(DEPDIR)/Output.Plo
include $(DEPDIR)/Output.Po
include $(DEPDIR)/RecordHolder.Plo
include $(DEPDIR)/RecordHolder.Po
include $(DEPDIR)/State.Plo
include $(DEPDIR)/State.Po

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

# This directory's subdirectories are mostly independent; you can cd
# into them and run `make' without going through this Makefile.
# To change the values of `make' variables: instead of editing Makefiles,
# (1) if the variable is set in `config.status', edit `config.status'
#     (which will cause the Makefiles to be regenerated when you run `make');
# (2) otherwise, pass the desired values on the `make' command line.
$(RECURSIVE_TARGETS):
	@set fnord $(MAKEFLAGS); amf=$$2; \
	dot_seen=no; \
	target=`echo $@ | sed s/-recursive//`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    dot_seen=yes; \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done; \
	if test "$$dot_seen" = "no"; then \
	  $(MAKE) $(AM_MAKEFLAGS) "$$target-am" || exit 1; \
	fi; test -z "$$fail"

mostlyclean-recursive clean-recursive distclean-recursive \
maintainer-clean-recursive:
	@set fnord $(MAKEFLAGS); amf=$$2; \
	dot_seen=no; \
	case "$@" in \
	  distclean-* | maintainer-clean-*) list='$(DIST_SUBDIRS)' ;; \
	  *) list='$(SUBDIRS)' ;; \
	esac; \
	rev=''; for subdir in $$list; do \
	  if test "$$subdir" = "."; then :; else \
	    rev="$$subdir $$rev"; \
	  fi; \
	done; \
	rev="$$rev ."; \
	target=`echo $@ | sed s/-recursive//`; \
	for subdir in $$rev; do \
	  echo "Making $$target in $$subdir"; \
	  if test "$$subdir" = "."; then \
	    local_target="$$target-am"; \
	  else \
	    local_target="$$target"; \
	  fi; \
	  (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) $$local_target) \
	   || case "$$amf" in *=*) exit 1;; *k*) fail=yes;; *) exit 1;; esac; \
	done && test -z "$$fail"
tags-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) tags); \
	done

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP) $(TAGS_FILES)
	list='$(SOURCES) $(HEADERS) $(TAGS_FILES)'; \
	unique=`for i in $$list; do \
	    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
	  done | \
	  $(AWK) '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	mkid -fID $$unique $(LISP)

TAGS: tags-recursive $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) \
		$(TAGS_FILES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  if test "$$subdir" = .; then :; else \
	    test -f $$subdir/TAGS && tags="$$tags -i $$here/$$subdir/TAGS"; \
	  fi; \
	done; \
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

top_distdir = ..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	$(mkinstalldirs) $(distdir)/../include/dime
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
	for subdir in $(SUBDIRS); do \
	  if test "$$subdir" = .; then :; else \
	    test -d $(distdir)/$$subdir \
	    || mkdir $(distdir)/$$subdir \
	    || exit 1; \
	    (cd $$subdir && \
	      $(MAKE) $(AM_MAKEFLAGS) \
	        top_distdir="$(top_distdir)" \
	        distdir=../$(distdir)/$$subdir \
	        distdir) \
	      || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-recursive
all-am: Makefile $(LIBRARIES) $(LTLIBRARIES) $(HEADERS)
installdirs: installdirs-recursive
installdirs-am:
	$(mkinstalldirs) $(DESTDIR)$(libdir) $(DESTDIR)$(libdir) $(DESTDIR)$(libdimeincdir)

install: install-recursive
install-exec: install-exec-recursive
install-data: install-data-recursive
uninstall: uninstall-recursive

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-recursive
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:
	-test -z "$(CLEANFILES)" || rm -f $(CLEANFILES)

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*
	-test -z "$(DISTCLEANFILES)" || rm -f $(DISTCLEANFILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-recursive

clean-am: clean-generic clean-libLIBRARIES clean-libLTLIBRARIES \
	clean-libtool mostlyclean-am

distclean: distclean-recursive

distclean-am: clean-am distclean-compile distclean-depend \
	distclean-generic distclean-libtool distclean-tags

dvi: dvi-recursive

dvi-am:

info: info-recursive

info-am:

install-data-am: install-data-local install-libdimeincHEADERS

install-exec-am: install-exec-local install-libLIBRARIES \
	install-libLTLIBRARIES

install-info: install-info-recursive

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-recursive

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-recursive

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

uninstall-am: uninstall-info-am uninstall-libLIBRARIES \
	uninstall-libLTLIBRARIES uninstall-libdimeincHEADERS \
	uninstall-local

uninstall-info: uninstall-info-recursive

.PHONY: $(RECURSIVE_TARGETS) GTAGS all all-am check check-am clean \
	clean-generic clean-libLIBRARIES clean-libLTLIBRARIES \
	clean-libtool clean-recursive distclean distclean-compile \
	distclean-depend distclean-generic distclean-libtool \
	distclean-recursive distclean-tags distdir dvi dvi-am \
	dvi-recursive info info-am info-recursive install install-am \
	install-data install-data-am install-data-local \
	install-data-recursive install-exec install-exec-am \
	install-exec-local install-exec-recursive install-info \
	install-info-am install-info-recursive install-libLIBRARIES \
	install-libLTLIBRARIES install-libdimeincHEADERS install-man \
	install-recursive install-strip installcheck installcheck-am \
	installdirs installdirs-am installdirs-recursive \
	maintainer-clean maintainer-clean-generic \
	maintainer-clean-recursive mostlyclean mostlyclean-compile \
	mostlyclean-generic mostlyclean-libtool mostlyclean-recursive \
	tags tags-recursive uninstall uninstall-am uninstall-info-am \
	uninstall-info-recursive uninstall-libLIBRARIES \
	uninstall-libLTLIBRARIES uninstall-libdimeincHEADERS \
	uninstall-local uninstall-recursive


# Custom rule for linking a Visual C++ (MS Windows) library.

dime0.lib: Makefile \
  $(dime0_lib_OBJECTS) \
  $(dime0_lib_DEPENDENCIES)
	@basename="dime0"; \
	rm -f "$$basename.dll" "$$basename.lib"; \
	echo "Linking $$basename.lib..."; \
	echo $(CC) $(LDFLAGS) $(LIBFLAGS) \
	  $(dime0_lib_OBJECTS) \
	  $(dime0_lib_LIBADD) $(LIBS); \
	$(CC) $(LDFLAGS) $(LIBFLAGS) \
	  $(dime0_lib_OBJECTS) \
	  $(dime0_lib_LIBADD) $(LIBS);

install-data-local:
	@$(NORMAL_INSTALL)
	@basename="dime0"; \
	for ext in lib; do \
	  file="$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(libdir)"; \
	    echo " $(INSTALL_DATA)" "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	    $(INSTALL_DATA) "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	  fi \
	done;

install-exec-local:
	@basename="dime0"; \
	for ext in dll pdb; do \
	  file="$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	    echo " $(INSTALL_PROGRAM)" "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	    $(INSTALL_PROGRAM) "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	  fi \
	done

install-libdimeincHEADERS: $(libdimeinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libdimeincdir)
	@list='$(libdimeinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libdimeincdir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libdimeincdir)/$$f; \
	done

uninstall-libdimeincHEADERS:
	@$(NORMAL_UNINSTALL)
	@list='$(libdimeinc_HEADERS)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(libdimeincdir)/$$f"; \
	  rm -f $(DESTDIR)$(libdimeincdir)/$$f; \
	done

uninstall-local:
	@basename="dime0"; \
	for file in \
	  "$(DESTDIR)$(bindir)/$$basename.dll" \
	  "$(DESTDIR)$(bindir)/$$basename.pdb" \
	  "$(DESTDIR)$(libdir)/$$basename.lib"; do \
	  if test -f "$$file"; then \
	    echo " rm -f" "$$file"; \
	    rm -f "$$file"; \
	  fi \
	done; \
	baseincdir="$(DESTDIR)$(libdimeincdir)"; \
	for dir in \
	  "$$baseincdir/VRMLnodes" \
	  "$$baseincdir/actions" \
	  "$$baseincdir/classes" \
	  "$$baseincdir/convert" \
	  "$$baseincdir/entities" \
	  "$$baseincdir/objects" \
	  "$$baseincdir/records" \
	  "$$baseincdir/sections" \
	  "$$baseincdir/tables" \
	  "$$baseincdir/util" \
	  "$$baseincdir"; do \
	  if test -d "$$dir"; then \
	    echo " rmdir $$dir"; \
	    rmdir "$$dir" || exit 1; \
	  fi \
	done; \
	:
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
