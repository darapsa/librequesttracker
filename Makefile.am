noinst_LIBRARIES = librtclient.a
librtclient_a_SOURCES = \
			rtclient/user.h \
			rtclient/ticket.h \
			rtclient/client.h \
			request.h \
			request.c \
			post.h \
			post.c \
			user.c \
			ticket.c \
			client.c
librtclient_a_CFLAGS = -fPIC

bin_PROGRAMS = rtclienttest
rtclienttest_SOURCES = main.c
rtclienttest_LDADD = librtclient.a
rtclienttest_LDFLAGS = -lcurl
