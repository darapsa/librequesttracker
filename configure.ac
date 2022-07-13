AC_INIT([rtclient], [0.0], [pt@darapsa.co.id])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT
AC_CANONICAL_HOST
case $host_cpu in
	*wasm* ) wasm=true;;
	*) wasm=false;;
esac
AM_CONDITIONAL([WASM], [test x$wasm = xtrue])
if test "x$wasm" = "xfalse"; then
	PKG_CHECK_MODULES([CURL], [libcurl])
fi
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_CHECK_FUNCS([memset strstr])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
