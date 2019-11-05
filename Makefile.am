noinst_LIBRARIES = librtclient.a
librtclient_a_SOURCES = \
			rtclient/user.h \
			rtclient/ticket.h \
			rtclient/search.h \
			rtclient/client.h \
			request.h \
			request.c \
			post.h \
			post.c \
			user.c \
			ticket.c \
			search.c \
			client.c

bin_PROGRAMS = rtclienttest
rtclienttest_SOURCES = main.c
rtclienttest_LDADD = librtclient.a
rtclienttest_LDFLAGS = -lcurl
