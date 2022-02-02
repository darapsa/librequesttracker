#ifndef RTCLIENT_H
#define RTCLIENT_H

#include "rtclient/typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

void rtclient_init(const char *url, const char *cookies,
		const char *certificate);
void rtclient_login(const char *name, const char *password,
		void (*handler)(rtclient_response *));
void rtclient_free_response(rtclient_response *response);
void rtclient_cleanup();

#ifdef __cplusplus
}
#endif

#endif
