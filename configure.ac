dnl AC_INIT(src/gui/gbhed.c, src/abtranslate.c, src/albhed.c, src/albhed.h,  \
dnl	src/vector_string.h, src/vector_string.c, cipher_tables.h)
AC_INIT([gBhed], [0.18], [liquidchile@liquidchile.net])
AM_CONFIG_HEADER(config.h)

PACKAGE=gBhed
VERSION=0.18

AM_INIT_AUTOMAKE($PACKAGE, $VERSION)

AC_PROG_CC
AC_PROG_INSTALL
AC_STDC_HEADERS
AC_CHECK_HEADERS(string.h)

AC_MSG_CHECKING(for bnacahla uv Yevon)
AC_MSG_RESULT([No])

dnl check to see if we are compiling everything or not
AC_MSG_CHECKING(whether to compile gBhed)
AC_ARG_ENABLE(gbhed,
	      [  --enable-gbhed		enable compliation of gBhed
  --disable-gbhed		disable compilation of gBhed],
	      [ if test "x$enableval" = "xno" ;then
	       		compile_gbhed="no"
		else
			compile_gbhed="yes"
		fi])

if test "x${compile_gbhed}" = "xno"; then
	AC_MSG_RESULT([No])
else
	AC_MSG_RESULT([Yes])
	PKG_CHECK_MODULES(DEPS, gtk+-2.0 >= 2.2 glib-2.0 >= 2.2)
	[compile_gbhed="yes"]
fi

AC_MSG_CHECKING(whether to compile abtranslate)
AC_ARG_ENABLE(abtranslate,
	      [  --enable-abtranslate		enable compliation of abtranslate
  --disable-abtranslate		disable compilation of abtranslate],
	      [ if test "x$enableval" = "xno" ;then
	       		compile_ab="no"
		else
	       		compile_ab="yes"
		fi])

if test "x${compile_ab}" = "xno"; then
	AC_MSG_RESULT([No])
else
	AC_MSG_RESULT([Yes])
	[compile_ab="yes"]
fi

AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

AM_CONDITIONAL(COMPILE_GBHED, test "x$compile_gbhed" = "xyes")
AM_CONDITIONAL(COMPILE_AB, test "x$compile_ab" = "xyes")

AC_OUTPUT([
	   Makefile
	   src/Makefile
	   src/gui/Makefile
	   pixmaps/Makefile
	   doc/Makefile
	   doc/abtranslate.1
	   doc/gbhed.1
])

echo
echo Use gBhed.... $compile_gbhed
echo Use abtranslate.... $compile_ab
echo
echo configure completed, now type \'make\'
