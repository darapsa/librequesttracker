#ifndef RTCLIENT_CLIENT_H
#define RTCLIENT_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

	bool rtclient_init(const char *url);
	void rtclient_login(const char *name, const char *password);
	void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_CLIENT_H
