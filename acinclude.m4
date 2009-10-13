AC_DEFUN([ACX_SETUP_CUSTOM_BUILD_FLAGS],[

# Setup compilers for different architechtures
case $host in 
	*i*86*-linux*)
		acx_extra_build_flags="linux-i386"
		;;
	*ia*64*-linux*)
		acx_extra_build_flags="linux-ia64"
		;;
	*x86*64*-linux*)
		acx_extra_build_flags="linux-x86_64"
		;;
	*i*86*-darwin*)
		acx_extra_build_flags="darwin-x86"
		;;
	*) 	
		acx_extra_build_flags="none"
		;;
esac

# get the appropriate build flags 
if test -f ${ac_aux_dir}/compilers.conf; then
	. ${ac_aux_dir}/compilers.conf
else
	AC_MSG_ERROR([Missing config file: ${ac_aux_dir}/compilers.conf])
fi
if test -f ${ac_aux_dir}/${extra_build_flags}.conf; then
	. ${ac_aux_dir}/${extra_build_flags}.conf
fi
])

AC_DEFUN([ACX_CHECK_DIR],[
AC_MSG_CHECKING([for $1 directory])
if test -d $1; then
	AC_MSG_RESULT([yes])
else
	AC_MSG_RESULT([no])
	AC_MSG_NOTICE([creating $1])
	mkdir $1
fi
]) #ACX_CHECK_DIR
