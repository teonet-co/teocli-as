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
	 -Iembedded/teocli/libteol0

AM_LDFLAGS = \
 	 -L$(HOME)/Projects/teonet/src/ \
 	 -L../../angelscript/sdk/angelscript/lib \
	 -L$(HOME)/Projects/angelscript/sdk/angelscript/lib

AM_CXX = clang++
AM_CXXFLAGS = \
         -g -Wall -pedantic \
	 -I/opt/localionclude \
	 -I$(HOME)/Projects/teonet/src/ \
	 -I../../angelscript/sdk/angelscript/include \
	 -Iembedded/teocli/libteol0
	 -std=c++11

LIBS =	-langelscript -pthread
# -lteonet -lcrypto
#teocli_as_LDADD = $(HOME)/Projects/teonet/src/libteonet.la

bin_PROGRAMS = teocli_as

teocli_as_SOURCES = \
	main.cpp \
	modules/as_connect.cpp \
	\
	../../angelscript/sdk/add_on/scriptstdstring/scriptstdstring.cpp \
	../../angelscript/sdk/add_on/scriptbuilder/scriptbuilder.cpp

#	embedded/teocli/libteol0/teonet_l0_client.c 


teocli_as_LDFLAGS = $(AM_LDFLAGS)

teocli_as_LDADD = $(TEOCLI_AS_LIBS)
