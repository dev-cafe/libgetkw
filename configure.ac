#
# Process this file with autoconf to produce a configure script.
#
# Written by Jonas Juselius <jonas@iki.fi> 2007
#

AC_INIT([MRChem2],[dev],[jonas.juselius@uit.no])
AC_CONFIG_AUX_DIR(config)
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR(Python/getkw.py)
AC_CONFIG_HEADER(config.h)
AC_PREFIX_DEFAULT([/usr/local])
AC_PROG_MAKE_SET
AC_CANONICAL_HOST

AC_ARG_ENABLE([optimization],
    AC_HELP_STRING([--enable-optimization],[Turn on optimizations]),
     [case "${enableval}" in
       yes) optimize=true ;;
       no)  optimize=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-optimization]) ;;
     esac],[optimize=false])
AM_CONDITIONAL([OPTIMIZE], [test x$optimize = xtrue])

AC_ARG_ENABLE([profiling],
     AC_HELP_STRING([--enable-profiling],[Turn on profiling]),
     [case "${enableval}" in
       yes) profiling=true ;;
       no)  profiling=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-profiling]) ;;
     esac],[profiling=false])
AM_CONDITIONAL([PROFILING], [test x$profiling = xtrue])

AC_ARG_ENABLE([fortran],
    AC_HELP_STRING([--enable-fortran],[Build the Fortran 90/95 interface]),
     [case "${enableval}" in
       yes) enable_fortran=true ;;
       no)  enable_fortran=false ;;
       *) AC_MSG_ERROR([bad value ${enableval} for --enable-fortran]) ;;
     esac],[optimize=false])
AM_CONDITIONAL([HAVE_FORTRAN], [test x$enable_fortran = xtrue])

AC_PROG_RANLIB
# find compilers
AC_PROG_CC
AC_PROG_CXX
if test "x$enable_fortran" = "xtrue"; then 
	AC_PROG_FC
	AC_FC_WRAPPERS
fi
# Get sensible compile flags (see acinclude.m4)
# Definitions in ./config/compilers.conf & ./config/{arch}.conf
ACX_SETUP_CUSTOM_BUILD_FLAGS

AX_PYTHON
AC_CACHE_SAVE

CXXFLAGS="${cxx_debug}"
if test "$optimize" = "true"; then
	CXXFLAGS="${cxx_flags}"
fi
if test "$profiling" = "true"; then
	CXXFLAGS="$CXXFLAGS ${cxx_prof}"
fi

LDFLAGS=${cxx_ldflags}

AC_SUBST(AM_CXXFLAGS)
AC_SUBST(EXTMOD, [$extmod])

AC_CONFIG_FILES([Makefile 
				 cpp/Makefile
				 c/Makefile
				 f95/Makefile
				 Python/Makefile
				 ])
dnl AC_CONFIG_SUBDIRS([libgetkw])
AC_OUTPUT
