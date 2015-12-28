## Process this file with automake to produce Makefile.in
#
# Rename teonet-tmpl or teonet_tmpl to your application name
#

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(TEONET_KSF_CFLAGS)

AM_CFLAGS = \
	 -Wall \
	 -g \
	 -I$(HOME)/Projects/teonet/src/ \
	 -I$(HOME)/Projects/teonet/embedded/libpbl/src \
	 -I$(HOME)/Projects/teonet/embedded/teocli/libteol0

AM_LDFLAGS = \
 	 -L$(HOME)/Projects/teonet/src/

AM_CXX = clang++
AM_CXXFLAGS = \
         -g -Wall -pedantic \
	 -I/opt/localionclude \
	 -I$(HOME)/Projects/teonet/src/
#-std=c++11

#LIBS = $YODGE_NODE_LIBS
LIBS =	-lteonet -lcrypto
teonet_tmpl_LDADD = $(HOME)/Projects/teonet/src/libteonet.la

bin_PROGRAMS = teonet_tmpl

teonet_tmpl_SOURCES = \
	main.c

teonet_tmpl_LDFLAGS =

teonet_tmpl_LDADD += $(TEONET_TMPL_LIBS)
