#ifndef RTCLIENT_H
#define RTCLIENT_H

#include "rtuser.h"

#ifdef __cplusplus
extern "C" {
#endif

	bool rtclient_init(const char *server_url);
	void rtclient_login(const char *name, const char *password);
	bool rtclient_get_user(struct rt_user **userptr, const char *name);
	void rtclient_search(const char *query);
	void rtclient_user_free(struct rt_user *user);
	void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_H
