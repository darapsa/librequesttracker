AC_INIT([rtclient], [0.0], [pt@darapsa.co.id])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_CHECK_FUNCS([memset strstr])
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_CANONICAL_HOST
case $host_os in
	*emscripten* ) emscripten=true;;
	*) emscripten=false;;
esac
if test "x$emscripten" = "xfalse"; then
	PKG_CHECK_MODULES([CURL], [libcurl])
fi
AM_CONDITIONAL([EMSCRIPTEN], [test x$emscripten = xtrue])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
