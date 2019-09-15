noinst_LIBRARIES = librtclient.a
librtclient_a_SOURCES = \
			rtclient/request.h \
			rtclient/user.h \
			rtclient/ticket.h \
			rtclient/client.h \
			request.c \
			user.c \
			ticket.c \
			client.c
librtclient_a_CFLAGS = -fPIC

bin_PROGRAMS = rtclienttest
rtclienttest_SOURCES = main.c
rtclienttest_LDADD = librtclient.a
rtclienttest_LDFLAGS = -lcurl
