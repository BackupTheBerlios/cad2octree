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



# This has to be a separate subdir so bin/ won't be created in the
# Mac OS X framework and coin-config won't be installed when you are not
# building the library at all.

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

dist_bin_SCRIPTS = coin-config
subdir = bin
mkinstalldirs = $(SHELL) $(top_srcdir)/cfg/mkinstalldirs
CONFIG_HEADER = $(top_builddir)/include/config.h
CONFIG_CLEAN_FILES =
SCRIPTS = $(dist_bin_SCRIPTS)

DIST_SOURCES =
DIST_COMMON = $(dist_bin_SCRIPTS) Makefile.am Makefile.in
all: all-am

.SUFFIXES:

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
$(srcdir)/Makefile.in: # Makefile.am  $(top_srcdir)/configure.ac $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --gnu  bin/Makefile
Makefile: # $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status
install-dist_binSCRIPTS: $(dist_bin_SCRIPTS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(bindir)
	@list='$(dist_bin_SCRIPTS)'; for p in $$list; do \
	  f="`echo $$p|sed '$(transform)'`"; \
	  if test -f $$p; then \
	    echo " $(INSTALL_SCRIPT) $$p $(DESTDIR)$(bindir)/$$f"; \
	    $(INSTALL_SCRIPT) $$p $(DESTDIR)$(bindir)/$$f; \
	  elif test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_SCRIPT) $(srcdir)/$$p $(DESTDIR)$(bindir)/$$f"; \
	    $(INSTALL_SCRIPT) $(srcdir)/$$p $(DESTDIR)$(bindir)/$$f; \
	  else :; fi; \
	done

uninstall-dist_binSCRIPTS:
	@$(NORMAL_UNINSTALL)
	@list='$(dist_bin_SCRIPTS)'; for p in $$list; do \
	  f="`echo $$p|sed '$(transform)'`"; \
	  echo " rm -f $(DESTDIR)$(bindir)/$$f"; \
	  rm -f $(DESTDIR)$(bindir)/$$f; \
	done
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
all-am: Makefile $(SCRIPTS)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(bindir)

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

install-data-am: install-dist_binSCRIPTS

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic mostlyclean-libtool

uninstall-am: uninstall-dist_binSCRIPTS uninstall-info-am

.PHONY: all all-am check check-am clean clean-generic clean-libtool \
	distclean distclean-generic distclean-libtool distdir dvi \
	dvi-am info info-am install install-am install-data \
	install-data-am install-dist_binSCRIPTS install-exec \
	install-exec-am install-info install-info-am install-man \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic mostlyclean \
	mostlyclean-generic mostlyclean-libtool uninstall uninstall-am \
	uninstall-dist_binSCRIPTS uninstall-info-am

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
