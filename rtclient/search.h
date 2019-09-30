#ifndef RTCLIENT_SEARCH_H
#define RTCLIENT_SEARCH_H

struct rtclient_search_ticket_list {
	size_t length;
	struct rtclient_ticket *tickets[];
};

#ifdef __cplusplus
extern "C" {
#endif

	void rtclient_search_ticket(struct rtclient_search_ticket_list **listptr
			, const char *query);
	void rtclient_search_ticket_free(struct rtclient_search_ticket_list *list);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_SEARCH_H
