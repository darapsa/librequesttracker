noinst_LIBRARIES = librtclient.a
librtclient_a_SOURCES = \
			rtclient/common.h \
			rtclient/user.h \
			rtclient/ticket.h \
			rtclient/rtclient.h \
			common.c \
			user.c \
			ticket.c \
			client.c

bin_PROGRAMS = rtclienttest
rtclienttest_SOURCES = main.c
rtclienttest_LDADD = librtclient.a
rtclienttest_LDFLAGS = -lcurl
