# **************************************************************************
# SIM_AC_HAVE_SMALLCHANGE_IFELSE( IF-FOUND, IF-NOT-FOUND )
#
# Variables:
#   sim_ac_have_smallchange
#   sim_ac_smallchange_cppflags
#   sim_ac_smallchange_ldflags
#   sim_ac_smallchange_libs
#
# Authors:
#   Peder Blekken <pederb@coin3d.org>, based on check_zlib.m4

# Todo:
# - use AS_UNSET to unset internal variables to avoid polluting the environment
#

# **************************************************************************

AC_DEFUN([SIM_AC_HAVE_SMALLCHANGE_IFELSE],
[: ${sim_ac_have_smallchange=false}
AC_MSG_CHECKING([for SmallChange])
AC_ARG_WITH(
  [smallchange],
  [AC_HELP_STRING([--with-smallchange=PATH], [enable/disable SmallChange support])],
  [case $withval in
  yes | "") sim_ac_want_smallchange=true ;;
  no)       sim_ac_want_smallchange=false ;;
  *)        sim_ac_want_smallchange=true
            sim_ac_smallchange_path=$withval ;;
  esac],
  [sim_ac_want_smallchange=true])
case $sim_ac_want_smallchange in
true)
  $sim_ac_have_smallchange && break
  sim_ac_smallchange_save_CPPFLAGS=$CPPFLAGS
  sim_ac_smallchange_save_LDFLAGS=$LDFLAGS
  sim_ac_smallchange_save_LIBS=$LIBS
  sim_ac_smallchange_debug=false
  test -n "`echo -- $CPPFLAGS $CFLAGS $CXXFLAGS | grep -- '-g\\>'`" &&
    sim_ac_smallchange_debug=true
  # test -z "$sim_ac_smallchange_path" -a x"$prefix" != xNONE &&
  #   sim_ac_smallchange_path=$prefix
  sim_ac_smallchange_name=SmallChange
  if test -n "$sim_ac_smallchange_path"; then
    for sim_ac_smallchange_candidate in \
      `( ls $sim_ac_smallchange_path/lib/SmallChange*.lib;
         ls $sim_ac_smallchange_path/lib/SmallChange*d.lib ) 2>/dev/null`
    do
      case $sim_ac_smallchange_candidate in
      *d.lib)
        $sim_ac_smallchange_debug &&
          sim_ac_smallchange_name=`basename $sim_ac_smallchange_candidate .lib` ;;
      *.lib)
        sim_ac_smallchange_name=`basename $sim_ac_smallchange_candidate .lib` ;;
      esac
    done
    sim_ac_smallchange_cppflags="-I$sim_ac_smallchange_path/include"
    CPPFLAGS="$CPPFLAGS $sim_ac_smallchange_cppflags"
    sim_ac_smallchange_ldflags="-L$sim_ac_smallchange_path/lib"
    LDFLAGS="$LDFLAGS $sim_ac_smallchange_ldflags"
    # unset sim_ac_smallchange_candidate
    # unset sim_ac_smallchange_path
  fi
  sim_ac_smallchange_libs="-l$sim_ac_smallchange_name"
  LIBS="$sim_ac_smallchange_libs $LIBS"
  AC_TRY_LINK(
    [#include <SmallChange/misc/Init.h>],
    [smallchange_init();],
    [sim_ac_have_smallchange=true])
  CPPFLAGS=$sim_ac_smallchange_save_CPPFLAGS
  LDFLAGS=$sim_ac_smallchange_save_LDFLAGS
  LIBS=$sim_ac_smallchange_save_LIBS
  # unset sim_ac_smallchange_debug
  # unset sim_ac_smallchange_name
  # unset sim_ac_smallchange_save_CPPFLAGS
  # unset sim_ac_smallchange_save_LDFLAGS
  # unset sim_ac_smallchange_save_LIBS
  ;;
esac
if $sim_ac_want_smallchange; then
  if $sim_ac_have_smallchange; then
    AC_MSG_RESULT([success ($sim_ac_smallchange_libs)])
    $1
  else
    AC_MSG_RESULT([failure])
    $2
  fi
else
  AC_MSG_RESULT([disabled])
  $2
fi
# unset sim_ac_want_smallchange
])

# EOF **********************************************************************
