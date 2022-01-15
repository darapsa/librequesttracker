#ifndef RTCLIENT_H
#define RTCLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

	bool rtclient_init(const char *url, const char *certificate);
	void rtclient_login(const char *name, const char *password);
	void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif
