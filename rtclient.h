#ifndef RTCLIENT_H
#define RTCLIENT_H

#include "rtuser.h"

#ifdef __cplusplus
extern "C" {
#endif

	bool rtclient_init(const char *server_url);
	void rtclient_login(const char *name, const char *password);
	struct rt_user *rtclient_user(const char *name);
	void rtclient_search(const char *query);
	void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_H
