#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

struct rt_ticketlist {
	unsigned int length;
	char *tickets[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void rtclient_ticket_search(struct rt_ticketlist **listptr, const char *query);
	void rtclient_ticket_freelist(struct rt_ticketlist *list);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_TICKET_H
