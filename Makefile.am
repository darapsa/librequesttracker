noinst_LIBRARIES = librtclient.a
librtclient_a_SOURCES = \
			rtclient/user.h \
			rtclient/ticket.h \
			rtclient/rtclient.h \
			rtclient.c

bin_PROGRAMS = test
test_SOURCES = test.c
test_LDADD = librtclient.a
test_LDFLAGS = -lcurl
