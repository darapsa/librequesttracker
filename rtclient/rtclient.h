#ifndef RTCLIENT_H
#define RTCLIENT_H

#include "user.h"
#include "ticket.h"

#ifdef __cplusplus
extern "C" {
#endif

	bool rtclient_init(const char *server_url);
	void rtclient_login(const char *name, const char *password);
	void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_H
