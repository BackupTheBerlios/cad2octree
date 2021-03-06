############################################################################
# Usage:
#  SIM_AC_CHECK_QT([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the Qt development system. If it is found, these
#  shell variables are set:
#
#    $sim_ac_qt_cppflags (extra flags the compiler needs for Qt lib)
#    $sim_ac_qt_ldflags  (extra flags the linker needs for Qt lib)
#    $sim_ac_qt_libs     (link libraries the linker needs for Qt lib)
#
#  The CPPFLAGS, LDFLAGS and LIBS flags will also be modified accordingly.
#  In addition, the variable $sim_ac_qt_avail is set to "yes" if
#  the Qt development system is found.
#
# Authors:
#   Morten Eriksen <mortene@sim.no>.
#   Lars J. Aas <larsa@sim.no>.

AC_DEFUN([SIM_AC_CHECK_QT], [

AC_ARG_WITH(
  [qt],
  AC_HELP_STRING([--with-qt=DIR],
                 [specify location of Qt library [default=yes]]),
  [],
  [with_qt=yes])

AC_ARG_ENABLE(
  [qt-debug],
  AC_HELP_STRING([--enable-qt-debug], [win32: link with debug versions of Qt libraries]),
  [case $enableval in
  yes | true ) sim_ac_qt_debug=true ;;
  *) sim_ac_qt_debug=false ;;
  esac],
  [sim_ac_qt_debug=false])

sim_ac_qt_avail=no

if test x"$with_qt" != xno; then
  sim_ac_path=$PATH

  # Remember over config.status re-runs of configure.
  # FIXME: this doesn't work unless QTDIR is part of the configure
  # argument line. We should be able to grab it from the
  # environment settings. 20011018 mortene. 
  AC_SUBST([QTDIR], [$QTDIR])

  # The Cygwin environment needs to invoke moc with a POSIX-style path.
  AC_PATH_PROG(sim_ac_qt_cygpath, cygpath, false)
  if test $sim_ac_qt_cygpath = "false"; then
    sim_ac_qt_dir=$QTDIR
  else
    # Quote $QTDIR in case it's empty.
    sim_ac_qt_dir=`$sim_ac_qt_cygpath -u "$QTDIR"`
  fi

  if test x"$with_qt" != xyes; then
    sim_ac_qt_incflags="-I${with_qt}/include"
    sim_ac_qt_ldflags="-L${with_qt}/lib"
    sim_ac_path=${with_qt}/bin:$PATH
  else
    AC_MSG_CHECKING([value of the QTDIR environment variable])
    if test x"$sim_ac_qt_dir" = x""; then
      AC_MSG_RESULT([empty])
      AC_MSG_WARN([QTDIR environment variable not set -- this might be an indication of a problem])
    else
      AC_MSG_RESULT([$sim_ac_qt_dir])

      # list contents of what's in the qt dev environment into config.log...
      for i in "" bin lib; do
        echo "Listing contents of $sim_ac_qt_dir/$i:" >&5
        ls -l $sim_ac_qt_dir/$i >&5 2>&1
      done

      sim_ac_qt_incflags="-I$sim_ac_qt_dir/include"
      sim_ac_qt_ldflags="-L$sim_ac_qt_dir/lib"
      sim_ac_path=$sim_ac_qt_dir/bin:$PATH
    fi
  fi

  sim_ac_save_cppflags=$CPPFLAGS
  sim_ac_save_ldflags=$LDFLAGS
  sim_ac_save_libs=$LIBS

  CPPFLAGS="$sim_ac_qt_incflags $CPPFLAGS"
  LDFLAGS="$LDFLAGS $sim_ac_qt_ldflags"

  sim_ac_qt_libs=UNRESOLVED

  AC_PATH_PROG(MOC, moc, false, $sim_ac_path)

  if test x"$MOC" = x"false"; then
    AC_MSG_WARN([the ``moc'' Qt pre-processor tool not found])
  else

  sim_ac_qglobal=false
  SIM_AC_CHECK_HEADER_SILENT([qglobal.h],
    [sim_ac_qglobal=true],
    # Debian Linux has the Qt-dev installation headers in a separate subdir.
    [sim_ac_debian_qtheaders=/usr/include/qt
     if test -d $sim_ac_debian_qtheaders; then
       sim_ac_qt_incflags="-I$sim_ac_debian_qtheaders $sim_ac_qt_incflags"
       CPPFLAGS="-I$sim_ac_debian_qtheaders $CPPFLAGS"
       SIM_AC_CHECK_HEADER_SILENT([qglobal.h], [sim_ac_qglobal=true])
     fi])

  if $sim_ac_qglobal; then

  # Find version of the Qt library (MSWindows .dll is named with the
  # version number.)
  AC_MSG_CHECKING([version of Qt library])
  cat > conftest.c << EOF
#include <qglobal.h>
int VerQt = QT_VERSION;
EOF
  # The " *"-parts of the last sed-expression on the next line are necessary
  # because at least the Solaris/CC preprocessor adds extra spaces before and
  # after the trailing semicolon.
  sim_ac_qt_version=`$CXXCPP $CPPFLAGS conftest.c 2>/dev/null | grep '^int VerQt' | sed 's%^int VerQt = %%' | sed 's% *; *$%%'`

  case $sim_ac_qt_version in
  0x* )
    sim_ac_qt_version=`echo $sim_ac_qt_version | sed -e 's/^0x.\(.\).\(.\).\(.\)/\1\2\3/;'`
    ;;
  * )
    # nada
    ;;
  esac

  rm -f conftest.c
  AC_MSG_RESULT($sim_ac_qt_version)

  if test $sim_ac_qt_version -lt 200; then
    SIM_AC_ERROR([too-old-qt])
  fi

  # Too hard to feature-check for the Qt-on-Mac problems, as they involve
  # obscure behavior of the QGLWidget -- so we just resort to do platform
  # and version checking instead.
  case $host_os in
  darwin*)
    if test $sim_ac_qt_version -lt 302; then
      SIM_AC_CONFIGURATION_WARNING([The version of Qt you are using is
known to contain some serious bugs on MacOS X. We strongly recommend you to
upgrade. (See $srcdir/README.MAC for details.)])
    fi

  # Qt/X11 is currently not supported on Mac OS X.
    AC_TRY_LINK([#include <qapplication.h>],
                [#if defined(__APPLE__) && defined(Q_WS_X11)
                 #error blah!
                 #endif],[],
                [SIM_AC_ERROR([x11-qt-on-mac])])
    ;;
  esac

  # Known problems:
  #
  #   * Qt v3.0.1 has a bug where SHIFT-PRESS + CTRL-PRESS + CTRL-RELEASE
  #     results in the last key-event coming out completely wrong under X11.
  #     Known to be fixed in 3.0.3, unknown status in 3.0.2.  <mortene@sim.no>.
  #
  if test $sim_ac_qt_version -lt 303; then
    SIM_AC_CONFIGURATION_WARNING([The version of Qt you are compiling against
is known to contain bugs which influences functionality in SoQt. We strongly
recommend you to upgrade.])
  fi

  sim_ac_qt_cppflags=
  if test x"$MOC" != xfalse; then
    # Do not cache the result, as we might need to play tricks with
    # CPPFLAGS under MSWin.

    # It should be helpful to be able to override the libs-checking with
    # environment variables. Then people won't get completely stuck
    # when the check fails -- we can just take a look at the
    # config.log and give them advice on how to proceed with no updates
    # necessary.
    #
    # (Note also that this makes it possible to select whether to use the
    # mt-safe or the "standard" Qt library if both are installed on the
    # user's system.)
    #
    # mortene.
  
    if test x"$CONFIG_QTLIBS" != x""; then
      AC_MSG_CHECKING([for Qt linking with $CONFIG_QTLIBS])

      for sim_ac_qt_cppflags_loop in "" "-DQT_DLL"; do
        CPPFLAGS="$sim_ac_qt_incflags $sim_ac_qt_cppflags_loop $sim_ac_save_cppflags"
        LIBS="$CONFIG_QTLIBS $sim_ac_save_libs"
        AC_TRY_LINK([#include <qapplication.h>],
                    [qApp = NULL; /* QT_DLL must be defined for assignment to global variables to work */
                     qApp->exit(0);],
                    [sim_ac_qt_libs="$CONFIG_QTLIBS"
                     sim_ac_qt_cppflags="$sim_ac_qt_incflags $sim_ac_qt_cppflags_loop"])
      done

      if test "x$sim_ac_qt_libs" = "xUNRESOLVED"; then
        AC_MSG_RESULT([failed!])
      else
        AC_MSG_RESULT([ok])
      fi

    else
      AC_MSG_CHECKING([for Qt library devkit])

      ## Test all known possible combinations of linking against the
      ## Troll Tech Qt library:
      ##
      ## * "-lqt-gl": links against the standard Debian version of the
      ##   Qt library with embedded QGL
      ##
      ## * "-lqt": should work for most UNIX(-derived) platforms on
      ##   dynamic and static linking with the non-mtsafe library
      ##
      ## * "-lqt-mt": should work for most UNIX(-derived) platforms on
      ##   dynamic and static linking with the mtsafe library
      ##
      ## * "-lqt{version} -lqtmain -lgdi32": w/QT_DLL defined should
      ##   cover dynamic Enterprise Edition linking on Win32 platforms
      ##
      ## * "-lqt -lqtmain -lgdi32": ...unless the {version} suffix is missing,
      ##   which we've had reports about
      ##
      ## * "-lqt-mt{version} -lqtmain -lgdi32": w/QT_DLL defined should
      ##   cover dynamic multi-thread Enterprise Edition linking on Win32
      ##   platforms
      ##
      ## * "-lqt-mt{version}nc -lqtmain -lgdi32": w/QT_DLL defined should
      ##   cover dynamic Non-Commercial Edition linking on Win32 platforms
      ##
      ## * "-lqt -luser32 -lole32 -limm32 -lcomdlg32 -lgdi32": should cover
      ##   static linking on Win32 platforms
      ##
      ## * "-lqt-mt -luser32 -lole32 -limm32 -lcomdlg32 -lgdi32 -lwinspool -lwinmm -ladvapi32":
      ##   added for the benefit of the Qt 3.0.0 Evaluation Version
      ##   (update: "advapi32.lib" seems to be a new dependency for Qt 3.1.0)

      sim_ac_qt_suffix=
      if $sim_ac_qt_debug; then
        sim_ac_qt_suffix=d
      fi

      # Note that we need to always check for -lqt-mt before -lqt, because
      # at least the most recent Debian platforms (as of 2003-02-20) comes
      # with a -lqt which is missing QGL support, while it also has a
      # -lqt-mt *with* QGL support. The reason for this is because the
      # default GL (Mesa) library on Debian is built in mt-safe mode,
      # so a non-mt-safe Qt can't use it.

      for sim_ac_qt_cppflags_loop in "" "-DQT_DLL"; do
        for sim_ac_qt_libcheck in \
            "-lqt-gl" \
            "-lqt-mt" \
            "-lqt" \
            "-lqt-mt -luser32 -lole32 -limm32 -lcomdlg32 -lgdi32 -lwinspool -lwinmm -ladvapi32" \
            "-lqt-mt${sim_ac_qt_version}${sim_ac_qt_suffix} -lqtmain -lgdi32" \
            "-lqt-mt${sim_ac_qt_version}nc${sim_ac_qt_suffix} -lqtmain -lgdi32" \
            "-lqt -lqtmain -lgdi32" \
            "-lqt${sim_ac_qt_version}${sim_ac_qt_suffix} -lqtmain -lgdi32" \
            "-lqt -luser32 -lole32 -limm32 -lcomdlg32 -lgdi32"
        do
          if test "x$sim_ac_qt_libs" = "xUNRESOLVED"; then
            CPPFLAGS="$sim_ac_qt_incflags $sim_ac_qt_cppflags_loop $sim_ac_save_cppflags"
            LIBS="$sim_ac_qt_libcheck $sim_ac_save_libs"
            AC_TRY_LINK([#include <qapplication.h>],
                        [qApp = NULL; /* QT_DLL must be defined for assignment to global variables to work */
                         qApp->exit(0);],
                        [sim_ac_qt_libs="$sim_ac_qt_libcheck"
                         sim_ac_qt_cppflags="$sim_ac_qt_incflags $sim_ac_qt_cppflags_loop"])
          fi
        done
      done

      AC_MSG_RESULT($sim_ac_qt_cppflags $sim_ac_qt_libs)
    fi
  fi

  else # sim_ac_qglobal = false
   AC_MSG_WARN([header file qglobal.h not found, can not compile Qt code])
  fi
  fi # MOC = false

  if test ! x"$sim_ac_qt_libs" = xUNRESOLVED; then
    sim_ac_qt_avail=yes
    CPPFLAGS="$sim_ac_qt_cppflags $sim_ac_save_cppflags"
    LIBS="$sim_ac_qt_libs $sim_ac_save_libs"
    $1
  else
    CPPFLAGS=$sim_ac_save_cppflags
    LDFLAGS=$sim_ac_save_ldflags
    LIBS=$sim_ac_save_libs
    $2
  fi
fi
])

############################################################################
# Usage:
#  SIM_AC_CHECK_QGL([ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]])
#
#  Try to find the QGL widget for interfacing Qt with OpenGL. If it
#  is found, these shell variables are set:
#
#    $sim_ac_qgl_cppflags (extra flags the compiler needs for QGL lib)
#    $sim_ac_qgl_ldflags  (extra flags the linker needs for QGL lib)
#    $sim_ac_qgl_libs     (link libraries the linker needs for QGL lib)
#
#  The LIBS flag will also be modified accordingly. In addition, the
#  variable $sim_ac_qgl_avail is set to "yes" if the QGL extension
#  library is found.
#
# Note that all "modern" variants of Qt should come with QGL embedded.
# There's one important deviation: Debian comes with a -lqt which is
# missing QGL support, while it also has a -lqt-mt *with* QGL support.
# The reason for this is because the default GL (Mesa) library on Debian
# is built in mt-safe mode.
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_CHECK_QGL], [
sim_ac_qgl_avail=no
sim_ac_qgl_cppflags=
sim_ac_qgl_ldflags=
sim_ac_qgl_libs=

if test x"$with_qt" != xno; then
  # first check if we can link with the QGL widget already
  AC_CACHE_CHECK(
    [whether the QGL widget is part of main Qt library],
    sim_cv_lib_qgl_integrated,
    [AC_TRY_LINK([#include <qgl.h>],
                 [QGLFormat * f = new QGLFormat; f->setDepth(true); ],
                 [sim_cv_lib_qgl_integrated=yes],
                 [sim_cv_lib_qgl_integrated=no])])

  if test x"$sim_cv_lib_qgl_integrated" = xyes; then
    sim_ac_qgl_avail=yes
    $1
  else
    sim_ac_save_LIBS=$LIBS
    LIBS="$sim_ac_qgl_libs $LIBS"

    AC_MSG_CHECKING([for the QGL extension library])

    sim_ac_qgl_libs=UNRESOLVED
    for sim_ac_qgl_libcheck in "-lqgl" "-lqgl -luser32"; do
      if test "x$sim_ac_qgl_libs" = "xUNRESOLVED"; then
        LIBS="$sim_ac_qgl_libcheck $sim_ac_save_LIBS"
        AC_TRY_LINK([#include <qgl.h>],
                    [QGLFormat * f = new QGLFormat; f->setDepth(true); ],
                    [sim_ac_qgl_libs="$sim_ac_qgl_libcheck"])
      fi
    done

    if test x"$sim_ac_qgl_libs" != xUNRESOLVED; then
      AC_MSG_RESULT($sim_ac_qgl_libs)
      sim_ac_qgl_avail=yes
      $1
    else
      AC_MSG_RESULT([unavailable])
      LIBS=$sim_ac_save_LIBS
      $2
    fi
  fi
fi
])

# SIM_AC_QGLWIDGET_SETAUTOBUFFERSWAP
# ----------------------------------
#
# Use the macro for its side-effect: it defines
#
#       HAVE_QGLWIDGET_SETAUTOBUFFERSWAP
#
# to 1 in config.h if QGLWidget::setAutoBufferSwap() is available.
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_QGLWIDGET_SETAUTOBUFFERSWAP], [
AC_CACHE_CHECK(
  [whether the QGLWidget::setAutoBufferSwap() is available],
  sim_cv_func_qglwidget_setautobufferswap,
  [AC_TRY_LINK([#include <qgl.h>
class MyGLWidget : public QGLWidget {
public: MyGLWidget() {setAutoBufferSwap(FALSE);} };],
               [MyGLWidget * w = new MyGLWidget;],
               [sim_cv_func_qglwidget_setautobufferswap=yes],
               [sim_cv_func_qglwidget_setautobufferswap=no])])

if test x"$sim_cv_func_qglwidget_setautobufferswap" = xyes; then
  AC_DEFINE([HAVE_QGLWIDGET_SETAUTOBUFFERSWAP], 1,
    [Define this to 1 if QGLWidget::setAutoBufferSwap() is available])
fi
])


# SIM_AC_QGLFORMAT_SETOVERLAY
# ---------------------------
#
# Use the macro for its side-effect: it defines
#
#       HAVE_QGLFORMAT_SETOVERLAY
#
# to 1 in config.h if QGLFormat::setOverlay() is available.
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_QGLFORMAT_SETOVERLAY], [
AC_CACHE_CHECK(
  [whether QGLFormat::setOverlay() is available],
  sim_cv_func_qglformat_setoverlay,
  [AC_TRY_LINK([#include <qgl.h>],
               [QGLFormat f; f.setOverlay(TRUE);],
               [sim_cv_func_qglformat_setoverlay=yes],
               [sim_cv_func_qglformat_setoverlay=no])])

if test x"$sim_cv_func_qglformat_setoverlay" = xyes; then
  AC_DEFINE([HAVE_QGLFORMAT_SETOVERLAY], 1,
    [Define this to 1 if QGLFormat::setOverlay() is available])
fi
])


# SIM_AC_QGLFORMAT_EQ_OP
# ----------------------
#
# Use the macro for its side-effect: it defines
#
#       HAVE_QGLFORMAT_EQ_OP
#
# to 1 in config.h if operator==(QGLFormat&, QGLFormat&) is available.
# (For Qt v2.2.2 at least, Troll Tech forgot to include this method
# in the publicly exported API for MSWindows DLLs.)
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_QGLFORMAT_EQ_OP], [
AC_CACHE_CHECK(
  [whether operator==(QGLFormat&,QGLFormat&) is available],
  sim_cv_func_qglformat_eq_op,
  [AC_TRY_LINK([#include <qgl.h>],
               [QGLFormat f; if (f == f) f.setDepth(true);],
               [sim_cv_func_qglformat_eq_op=true],
               [sim_cv_func_qglformat_eq_op=false])])

if $sim_cv_func_qglformat_eq_op; then
  AC_DEFINE([HAVE_QGLFORMAT_EQ_OP], 1,
    [Define this to 1 if operator==(QGLFormat&, QGLFormat&) is available])
fi
])


# SIM_AC_QWIDGET_SHOWFULLSCREEN
# -----------------------------
#
# Use the macro for its side-effect: it defines HAVE_QWIDGET_SHOWFULLSCREEN
# to 1 in config.h if QWidget::showFullScreen() is available (that
# function wasn't introduced in Qt until version 2.1.0).
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_QWIDGET_SHOWFULLSCREEN], [
AC_CACHE_CHECK(
  [whether QWidget::showFullScreen() is available],
  sim_cv_def_qwidget_showfullscreen,
  [AC_TRY_LINK([#include <qwidget.h>],
               [QWidget * w = new QWidget(); w->showFullScreen();],
               [sim_cv_def_qwidget_showfullscreen=true],
               [sim_cv_def_qwidget_showfullscreen=false])])

if $sim_cv_def_qwidget_showfullscreen; then
  AC_DEFINE([HAVE_QWIDGET_SHOWFULLSCREEN], 1,
            [Define this if QWidget::showFullScreen() is available])
fi
]) # SIM_AC_QWIDGET_SHOWFULLSCREEN


# SIM_AC_QT_KEYPAD_DEFINE
# -----------------------
#
# Use the macro for its side-effect: it defines HAVE_QT_KEYPAD_DEFINE
# to 1 in config.h if Qt::Keypad is available.
#
# Author: Morten Eriksen, <mortene@sim.no>.

AC_DEFUN([SIM_AC_QT_KEYPAD_DEFINE], [
AC_CACHE_CHECK(
  [whether Qt::Keypad is defined],
  sim_cv_def_qt_keypad,
  [AC_TRY_LINK([#include <qkeycode.h>],
               [Qt::ButtonState s = Qt::Keypad;],
               [sim_cv_def_qt_keypad=true],
               [sim_cv_def_qt_keypad=false])])

if $sim_cv_def_qt_keypad; then
  AC_DEFINE([HAVE_QT_KEYPAD_DEFINE], 1,
            [Define this if Qt::Keypad is available])
fi
]) # SIM_AC_QT_KEYPAD_DEFINE
