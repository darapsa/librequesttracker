#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

struct rtclient_ticketlist {
	unsigned int length;
	char *tickets[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void rtclient_ticket_search(struct rtclient_ticketlist **listptr
			, const char *query);
	void rtclient_ticket_freelist(struct rtclient_ticketlist *list);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_TICKET_H
