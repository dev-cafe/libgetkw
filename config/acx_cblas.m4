dnl @synopsis ACX_CBLAS([ACTION-IF-FOUND[, ACTION-IF-NOT-FOUND]])
dnl
dnl This macro looks for a library that implements the CBLAS
dnl linear-algebra interface (see http://www.netlib.org/blas/).
dnl On success, it sets the CBLAS_LIBS output variable to
dnl hold the requisite library linkages.
dnl
dnl To link with CBLAS, you should link with:
dnl
dnl 	$CBLAS_LIBS $LIBS 
dnl
dnl in that order.  
dnl 
dnl The user may also use --with-cblas=<lib> in order to use some
dnl specific BLAS library <lib>.  In order to link successfully,
dnl however, be aware that you will probably need to use the same
dnl Fortran compiler (which can be set via the FC env. var.) as
dnl was used to compile the CBLAS library.
dnl
dnl ACTION-IF-FOUND is a list of shell commands to run if a CBLAS
dnl library is found, and ACTION-IF-NOT-FOUND is a list of commands
dnl to run it if it is not found.  If ACTION-IF-FOUND is not specified,
dnl the default action will define HAVE_CBLAS.
dnl
dnl This macro requires autoconf 2.50 or later.
dnl
dnl @version $Id: acx_f77blas.m4,v 1.2 2005/06/10 12:08:55 juselius Exp $
dnl @author Steven G. Johnson <stevenj@alum.mit.edu>
dnl
dnl Written by Jonas Juselius <jonas@iki.fi>, using Steven G. Johnson's
dnl acx_blas.m4 as a template
dnl
AC_DEFUN([ACX_CBLAS], [
AC_PREREQ(2.59)

acx_cblas_ok=no
acx_cblas_save_LIBS="$LIBS"
acx_cblas_save_LDFLAGS="$LDFLAGS"
acx_cblas_save_CFLAGS="$CFLAGS"
acx_cblas_save_CXXFLAGS="$CXXFLAGS"
acx_cblas_save_CPPFLAGS="$CPPFLAGS"
acx_cblas_libs=""
acx_cblas_libdir=""
acx_cblas_incdir=""
acx_cblas_header="cblas.h"

AC_ARG_WITH(cblas,
	[AC_HELP_STRING([--with-cblas=LIB], [use CBLAS library LIB])])

AC_ARG_WITH(cblas_dir,
	[AC_HELP_STRING([--with-cblas-dir=DIR], 
	[look for CBLAS in DIR])])

AC_ARG_WITH(cblas_libdir,
	[AC_HELP_STRING([--with-cblas-libdir=DIR], 
	[look for CBLAS library file in DIR])])

AC_ARG_WITH(cblas_incdir,
	[AC_HELP_STRING([--with-cblas-incdir=DIR], 
	[look for CBLAS headers in DIR])])

AC_ARG_WITH(cblas_header,
	[AC_HELP_STRING([--with-cblas-header=NAME], 
	[name of CBLAS header file (cblas.h)])])

case $with_cblas in
	yes | "") ;;
	no) acx_cblas_ok=disable ;;
	-l* | -L* | */* | *.a | *.so | *.so.* | *.o) 
		acx_cblas_libs="$with_cblas" ;;
	*) acx_cblas_libs="-l$with_cblas" ;;
esac

if test "x$with_cblas_dir" != "x"; then
	acx_cblas_libdir="-L$with_cblas_dir/lib"
	acx_cblas_incdir="-I$with_cblas_dir/include" 
	LDFLAGS="$LDFLAGS $acx_cblas_libdir"
	CFLAGS="$CFLAGS $acx_cblas_incdir"
	CXXFLAGS="$CXXFLAGS $acx_cblas_incdir"
	CPPFLAGS="$CPPFLAGS $acx_cblas_incdir"
fi

if test "x$with_cblas_libdir" != "x"; then
    acx_cblas_libdir="-L$with_cblas_libdir"
	LDFLAGS="$LDFLAGS $acx_cblas_libdir"
fi

if test "x$with_cblas_incdir" != "x"; then
    acx_cblas_incdir="-I$with_cblas_incdir" 
	CFLAGS="$CFLAGS $acx_cblas_incdir"
	CXXFLAGS="$CXXFLAGS $acx_cblas_incdir"
	CPPFLAGS="$CPPFLAGS $acx_cblas_incdir"
fi

sgemm="cblas_sgemm"

# If --with-cblas is defined, then look for THIS AND ONLY THIS cblas lib
if test $acx_cblas_ok = no; then
case $with_cblas in
    ""|yes) ;;
	*) save_LIBS="$LIBS"; LIBS="$acx_cblas_libs $LIBS"
	AC_MSG_CHECKING([for $sgemm in $acx_cblas_libs])
	AC_TRY_LINK_FUNC($sgemm, [acx_cblas_ok=yes])
	AC_MSG_RESULT($acx_cblas_ok)
	LIBS="$save_LIBS"
	acx_cblas_ok=specific
	;;
esac
fi

test "x$with_cblas_header" != "x" && acx_cblas_header="$with_cblas_header"

# First, check CBLAS_LIBS environment variable
if test $acx_cblas_ok = no; then
if test "x$CBLAS_LIBS" != x; then
	save_LIBS="$LIBS"; LIBS="$CBLAS_LIBS $LIBS"
	AC_MSG_CHECKING([for $sgemm in $CBLAS_LIBS])
	AC_TRY_LINK_FUNC($sgemm, [acx_cblas_ok=yes; acx_cblas_libs=$CBLAS_LIBS])
	AC_MSG_RESULT($acx_cblas_ok)
	LIBS="$save_LIBS"
fi
fi

dnl # CBLAS linked to by default?  (happens on some supercomputers)
dnl if test $acx_cblas_ok = no; then
dnl     AC_MSG_CHECKING([for builtin $sgemm])
dnl     AC_TRY_LINK_FUNC($sgemm, [acx_cblas_ok=yes])
dnl     AC_MSG_RESULT($acx_cblas_ok)
dnl fi

# CBLAS in ATLAS library? (http://math-atlas.sourceforge.net/)
if test $acx_cblas_ok = no; then
	AC_MSG_NOTICE([trying ATLAS library:])
    AC_CHECK_HEADER(cblas.h, [acx_cblas_header=cblas.h])
		AC_CHECK_LIB(cblas, $sgemm,
			[acx_cblas_ok=yes; acx_cblas_libs="-lcblas -lf77blas -latlas"],
			[], [-lf77blas -latlas])
	AC_MSG_NOTICE([ATLAS library... $acx_cblas_ok])
fi

# Intel mkl CBLAS. Currently only for emt64a. 
if test $acx_cblas_ok = no; then
	AC_MSG_NOTICE([trying Intel MKL library:])
    AC_CHECK_HEADER(mkl_cblas.h, [acx_cblas_header=mkl_cblas.h])
	AC_CHECK_LIB(mkl_intel_lp64, $sgemm, 
	[acx_cblas_ok=yes; 
    acx_cblas_libs="-Wl,--start-group -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -Wl,--end-group -lguide -lpthread -lm"],
	[],[-lmkl_intel_thread -lmkl_core -lguide -lpthread -lm])
	AC_MSG_NOTICE([Intel MKL library... $acx_cblas_ok])
fi


# Generic CBLAS library?
if test $acx_cblas_ok = no; then
    unset ac_cv_lib_cblas_sgemm
	AC_CHECK_LIB(cblas, $sgemm, [acx_cblas_ok=yes; acx_cblas_libs="-lcblas"])
fi

CBLAS_LIBS="$acx_cblas_libdir $acx_cblas_libs"
CBLAS_INCLUDES="$acx_cblas_incdir"
AC_SUBST(CBLAS_LIBS)
AC_SUBST(CBLAS_INCLUDES)

LIBS="$acx_cblas_save_LIBS"
LDFLAGS="$acx_cblas_save_LDFLAGS"
CFLAGS="$acx_cblas_save_CFLAGS" 
CXXFLAGS="$acx_cblas_save_CXXFLAGS" 
CPPFLAGS="$acx_cblas_save_CPPFLAGS"

if test x"$acx_cblas_ok" = xspecific ; then
   acx_cblas_ok=yes
fi
# Finally, execute ACTION-IF-FOUND/ACTION-IF-NOT-FOUND:
if test x"$acx_cblas_ok" = xyes; then
        ifelse([$1],,
			AC_DEFINE(HAVE_CBLAS,1,[Define if you have a CBLAS library.])
			AC_DEFINE_UNQUOTED([INCLUDE_CBLAS_H], 
			[#include <$acx_cblas_header>],
			[Macro for including the appropriate CBLAS headers]),
		[$1])
        :
else
		AC_DEFINE([INCLUDE_CBLAS_H], 
			[],
			[Macro for including the appropriate CBLAS headers]),
        acx_cblas_ok=no
        $2
fi
])dnl ACX_CBLAS

