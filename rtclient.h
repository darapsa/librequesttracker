#ifndef RTCLIENT_H
#define RTCLIENT_H

#include "rtuser.h"
#include "rtticket.h"

#ifdef __cplusplus
extern "C" {
#endif

	bool rtclient_init(const char *server_url);
	void rtclient_login(const char *name, const char *password);
	void rtclient_userget(struct rt_user **userptr, const char *name);
	void rtclient_search(struct rt_ticketlist **listptr, const char *query);
	void rtclient_userfree(struct rt_user *user);
	void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_H
