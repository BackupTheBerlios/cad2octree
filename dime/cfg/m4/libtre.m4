dnl @synopsis VL_CHECK_SIGN (TYPE, [ACTION-IF-SIGNED], [ACTION-IF-UNSIGNED], [INCLUDES])
dnl
dnl Checks whether TYPE is signed or not.  If no INCLUDES are specified,
dnl the default includes are used.  If ACTION-IF-SIGNED is given, it is
dnl additional shell code to execute when the type is signed.  If
dnl ACTION-IF-UNSIGNED is given, it is executed when the type is unsigned.
dnl
dnl This macro assumes that the type exists.  Therefore the existence of
dnl the type should be checked before calling this macro.  For example:
dnl
dnl   AC_CHECK_HEADERS([wchar.h])
dnl   AC_CHECK_TYPE([wchar_t],,[ AC_MSG_ERROR([Type wchar_t not found.]) ])
dnl   VL_CHECK_SIGN([wchar_t],
dnl     [ AC_DEFINE(WCHAR_T_SIGNED, 1, [Define if wchar_t is signed]) ],
dnl     [ AC_DEFINE(WCHAR_T_UNSIGNED, 1, [Define if wchar_t is unsigned]) ], [
dnl   #ifdef HAVE_WCHAR_H
dnl   #include <wchar.h>
dnl   #endif
dnl   ])
dnl
dnl @version 1.1
dnl @author Ville Laurikari <vl@iki.fi>
AC_DEFUN([VL_CHECK_SIGN], [
 typename=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g"`
 AC_CACHE_CHECK([whether $1 is signed], vl_cv_decl_${typename}_signed, [
   AC_TRY_COMPILE([$4],
     [ int foo @<:@ 1 - 2 * !((($1) -1) < 0) @:>@ ],
     [ eval "vl_cv_decl_${typename}_signed=\"yes\"" ],
     [ eval "vl_cv_decl_${typename}_signed=\"no\"" ])])
 symbolname=`echo $1 | sed "s/@<:@^a-zA-Z0-9_@:>@/_/g" | tr "a-z" "A-Z"`
 if eval "test \"\${vl_cv_decl_${typename}_signed}\" = \"yes\""; then
   $2
 elif eval "test \"\${vl_cv_decl_${typename}_signed}\" = \"no\""; then
   $3
 fi
])dnl
dnl @synopsis VL_DECL_WCHAR_MAX
dnl
dnl Checks whether the system headers define WCHAR_MAX or not.  If it is
dnl already defined, does nothing.  Otherwise checks the size and signedness
dnl of `wchar_t', and defines WCHAR_MAX to the maximum value that can be
dnl stored in a variable of type `wchar_t'.
dnl
dnl @version 1.1
dnl @author Ville Laurikari <vl@iki.fi>
dnl
AC_DEFUN([VL_DECL_WCHAR_MAX], [
  AC_CACHE_CHECK([whether WCHAR_MAX is defined], vl_cv_decl_wchar_max, [
    AC_TRY_COMPILE([
#ifdef HAVE_WCHAR_H
#include <wchar.h>
#endif
],[WCHAR_MAX],[vl_cv_decl_wchar_max="yes"],[vl_cv_decl_wchar_max="no"])])
  if test $vl_cv_decl_wchar_max = "no"; then
    VL_CHECK_SIGN([wchar_t],
      [ wc_signed="yes"
        AC_DEFINE(WCHAR_T_SIGNED, 1, [Define if wchar_t is signed]) ],
      [ wc_signed="no"
        AC_DEFINE(WCHAR_T_UNSIGNED, 1, [Define if wchar_t is unsigned])], [
#ifdef HAVE_WCHAR_H
#include <wchar.h>
#endif
])
    if test "$wc_signed" = "yes"; then
      AC_DEFINE(WCHAR_MAX, [(1L << (sizeof(wchar_t) * 8 - 1) - 1)], [
Define to the maximum value of wchar_t if not already defined elsewhere])
    elif test "$wc_signed" = "no"; then
      AC_DEFINE(WCHAR_MAX, [(1L << (sizeof(wchar_t) * 8) - 1)])
    fi
  fi
])dnl
dnl @synopsis VL_PROG_CC_WARNINGS([ANSI])
dnl
dnl Enables a reasonable set of warnings for the C compiler.  Optionally,
dnl if the first argument is nonempty, turns on flags which enforce and/or
dnl enable proper ANSI C if such are known with the compiler used.
dnl
dnl Currently this macro knows about GCC, Solaris C compiler,
dnl Digital Unix C compiler, C for AIX Compiler, HP-UX C compiler,
dnl IRIX C compiler, NEC SX-5 (Super-UX 10) C compiler, and Cray J90
dnl (Unicos 10.0.0.8) C compiler.
dnl
dnl @version 1.1
dnl @author Ville Laurikari <vl@iki.fi>
dnl
AC_DEFUN([VL_PROG_CC_WARNINGS], [
  ansi=$1
  if test -z "$ansi"; then
    msg="for C compiler warning flags"
  else
    msg="for C compiler warning and ANSI conformance flags"
  fi
  AC_CACHE_CHECK($msg, vl_cv_prog_cc_warnings, [
    if test -n "$CC"; then
      cat > conftest.c <<EOF
int main(int argc, char **argv) { return 0; }
EOF

      dnl GCC
      if test "$GCC" = "yes"; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-Wall"
        else
          vl_cv_prog_cc_warnings="-Wall -ansi -pedantic"
        fi

      dnl Most compilers print some kind of a version string with some command
      dnl line options (often "-V").  The version string should be checked
      dnl before doing a test compilation run with compiler-specific flags.
      dnl This is because some compilers (like the Cray compiler) only
      dnl produce a warning message for unknown flags instead of returning
      dnl an error, resulting in a false positive.  Also, compilers may do
      dnl erratic things when invoked with flags meant for a different
      dnl compiler.

      dnl Solaris C compiler
      elif $CC -V 2>&1 | grep -i "WorkShop" > /dev/null 2>&1 &&
           $CC -c -v -Xc conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-v"
        else
          vl_cv_prog_cc_warnings="-v -Xc"
        fi

      dnl Digital Unix C compiler
      elif $CC -V 2>&1 | grep -i "Digital UNIX Compiler" > /dev/null 2>&1 &&
           $CC -c -verbose -w0 -warnprotos -std1 conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-verbose -w0 -warnprotos"
        else
          vl_cv_prog_cc_warnings="-verbose -w0 -warnprotos -std1"
        fi

      dnl C for AIX Compiler
      elif $CC 2>&1 | grep -i "C for AIX Compiler" > /dev/null 2>&1 &&
           $CC -c -qlanglvl=ansi -qinfo=all conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-qsrcmsg -qinfo=all:noppt:noppc:noobs:nocnd"
        else
          vl_cv_prog_cc_warnings="-qsrcmsg -qinfo=all:noppt:noppc:noobs:nocnd -qlanglvl=ansi"
        fi

      dnl IRIX C compiler
      elif $CC -version 2>&1 | grep -i "MIPSpro Compilers" > /dev/null 2>&1 &&
           $CC -c -fullwarn -ansi -ansiE conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-fullwarn"
        else
          vl_cv_prog_cc_warnings="-fullwarn -ansi -ansiE"
        fi

      dnl HP-UX C compiler
      elif what $CC 2>&1 | grep -i "HP C Compiler" > /dev/null 2>&1 &&
           $CC -c -Aa +w1 conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="+w1"
        else
          vl_cv_prog_cc_warnings="+w1 -Aa"
        fi

      dnl The NEC SX-5 (Super-UX 10) C compiler
      elif $CC -V 2>&1 | grep "/SX" > /dev/null 2>&1 &&
           $CC -c -pvctl[,]fullmsg -Xc conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-pvctl[,]fullmsg"
        else
          vl_cv_prog_cc_warnings="-pvctl[,]fullmsg -Xc"
        fi

      dnl The Cray C compiler (Unicos)
      elif $CC -V 2>&1 | grep -i "Cray" > /dev/null 2>&1 &&
           $CC -c -h msglevel 2 conftest.c > /dev/null 2>&1 &&
           test -f conftest.o; then
        if test -z "$ansi"; then
          vl_cv_prog_cc_warnings="-h msglevel 2"
        else
          vl_cv_prog_cc_warnings="-h msglevel 2 -h conform"
        fi

      fi
      rm -f conftest.*
    fi
    if test -n "$vl_cv_prog_cc_warnings"; then
      CFLAGS="$CFLAGS $vl_cv_prog_cc_warnings"
    else
      vl_cv_prog_cc_warnings="unknown"
    fi
  ])
])dnl
