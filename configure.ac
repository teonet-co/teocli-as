dnl Process this file with autoconf to produce a configure script.


AC_INIT(teonet-tmpl, 0.0.1)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_PROG_CC
AC_PROG_CXX
AC_PROG_LIBTOOL


dnl ***************************************************************************
dnl Internatinalization
dnl ***************************************************************************
GETTEXT_PACKAGE=ksnet_ksf
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.35.0])


AM_PROG_LIBTOOL


# PKG_CHECK_MODULES(TEONET_TMPL, [glib-2.0 ])


AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
