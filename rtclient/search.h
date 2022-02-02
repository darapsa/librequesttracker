#ifndef RTCLIENT_SEARCH_H
#define RTCLIENT_SEARCH_H

#ifdef __cplusplus
extern "C" {
#endif

void rtclient_search_ticket(const char *query,
		void (*callback)(struct rtclient_ticket **));

#ifdef __cplusplus
}
#endif

#endif
