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
	-I/usr/include/teonet \
	-Iteocli/libteol0

AM_LDFLAGS = \
	-I/usr/include/teonet
	-L/usr/local/lib

#	-LAngelSdk/angelscript/sdk/angelscript/lib

AM_CXX = clang++
AM_CXXFLAGS = \
	 -g -Wall \
	-I/opt/localionclude \
	-I/usr/include/teonet \
	 -I$(HOME)/Projects/teonet/src/ \
	 -I../AngelSdk/angelscript/sdk/angelscript/include \
	 -I../teocli/libteol0 \
	 -std=c++11
	
# -pedantic

LIBS =	-langelscript -pthread
# -lteonet -lcrypto
#teocli_as_LDADD = $(HOME)/Projects/teonet/src/libteonet.la

bin_PROGRAMS = teocli_as

teocli_as_SOURCES = \
	main.cpp \
	modules/as_connect.cpp \
	modules/as_teocli.cpp \
	\
	../teocli/libteol0/teonet_l0_client.c \
	\
	modules/as/scriptstdstring.cpp \
	modules/as/scriptbuilder.cpp


teocli_as_LDFLAGS = $(AM_LDFLAGS)

teocli_as_LDADD = $(TEOCLI_AS_LIBS)
