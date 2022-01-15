lib_LTLIBRARIES = librtclient.la
librtclient_la_SOURCES = \
			request.h \
			request.c \
			post.h \
			post.c \
			user.c \
			ticket.c \
			search.c \
			client.c
librtclient_la_CPPFLAGS = -I${prefix}/include
librtclient_la_LDFLAGS = -L${prefix}/lib -lcurl
pkginclude_HEADERS = \
		     rtclient/user.h \
		     rtclient/ticket.h \
		     rtclient/search.h \
		     rtclient/client.h
#bin_PROGRAMS = rtclienttest
#rtclienttest_SOURCES = main.c
#rtclienttest_LDADD = librtclient.la
#rtclienttest_LDFLAGS = -lcurl
