lib_LTLIBRARIES = librtclient.la
librtclient_la_SOURCES = \
			 client.c \
			 request.c \
			 user.c \
			 ticket.c \
			 search.c
librtclient_la_CPPFLAGS = -I${prefix}/include
librtclient_la_LDFLAGS = -L${prefix}/lib
if WASM
librtclient_la_LDFLAGS += -static
else
librtclient_la_CPPFLAGS += $(CURL_CFLAGS)
librtclient_la_LDFLAGS += $(CURL_LIBS)
endif
include_HEADERS = rtclient.h
pkginclude_HEADERS = \
		     rtclient/typedefs.h \
		     rtclient/user.h \
		     rtclient/ticket.h \
		     rtclient/search.h
#bin_PROGRAMS = rtclienttest
#rtclienttest_SOURCES = main.c
#rtclienttest_LDADD = librtclient.la
#rtclienttest_LDFLAGS = -lcurl
