# Process this file with autoconf to produce a configure script.
AC_INIT(configure.in)
AM_INIT_AUTOMAKE(cad2octree, 0.2.1, http://sourceforge.net/projects/cad2octree)
AC_CONFIG_SRCDIR(src/cad2octree.cpp)
#AC_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXXCPP
AM_PROG_CC_STDC
AC_HEADER_STDC
AC_PROG_LIBTOOL
AC_PROG_INSTALL

AC_SUBST(TOP_DIR, $(cd .; pwd))
AC_SUBST(SRC_DIR, $TOP_DIR/src)
AC_SUBST(CXXFLAGS, "-I@SRC_DIR@ -I@SRC_DIR@/utils -I@SRC_DIR@/geom -I@SRC_DIR@/cad/objects $CXXFLAGS")

# Checks for dime-Library
AC_SUBST(DIME_LIBNAME, "libdime.la")
AC_CHECK_FILE(${prefix}/lib/$DIME_LIBNAME, AC_SUBST(LIBS, "$LIBS -L${prefix}/lib"), \
    AC_CHECK_FILE(/usr/local/lib/$DIME_LIBNAME, AC_SUBST(LIBS, "$LIBS -L/usr/local/lib"),\
	AC_CHECK_FILE(/usr/lib/$DIME_LIBNAME, AC_SUBST(LIBS, "$LIBS -L/usr/lib"), \
	    AC_CHECK_FILE($HOME/lib/$DIME_LIBNAME, AC_SUBST(LIBS, "$LIBS -L$HOME/lib"), \
		AC_MSG_ERROR($DIME_LIBNAME not found!)))))
AC_SUBST(LIBS, "$LIBS -ldime")
AC_SUBST(DIME_INCLNAME, "dime/entities/Polyline.h")
AC_CHECK_FILE(${prefix}/include/$DIME_INCLNAME, AC_SUBST(CXXFLAGS, "$CXXFLAGS -I${prefix}/include"), \
    AC_CHECK_FILE(/usr/local/include/$DIME_INCLNAME, AC_SUBST(CXXFLAGS, "$CXXFLAGS -I/usr/local/include"),\
	AC_CHECK_FILE(/usr/include/$DIME_INCLNAME, AC_SUBST(CXXFLAGS, "$CXXFLAGS -I/usr/include"), \
	    AC_CHECK_FILE($HOME/include/$DIME_INCLNAME, AC_SUBST(CXXFLAGS, "$CXXFLAGS -I$HOME/include"), \
		AC_MSG_ERROR($DIME_INCLNAME not found!)))))

#checks for doxygen and latex
AC_PATH_PROG(DOXYGEN, doxygen)
AC_SUBST(DOXYGEN)
AC_PATH_PROG(PDFLATEX, pdflatex)
AC_SUBST(PDFLATEX)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([limits.h stdint.h stdlib.h string.h sys/time.h values.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_STAT
AC_CHECK_FUNCS([pow sqrt strcasecmp strdup])

AC_CONFIG_FILES([Makefile
                 classref/Makefile
		 doc/Makefile
                 src/Makefile
                 src/cad/Makefile
                 src/cad/container/Makefile
                 src/cad/objects/Makefile
                 src/generator/Makefile
                 src/geom/Makefile
                 src/octree/Makefile
                 src/reader/Makefile
                 src/utils/Makefile
                 src/writer/Makefile])
AC_OUTPUT
