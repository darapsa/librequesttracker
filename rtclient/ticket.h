#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

struct rtclient_ticket {
	unsigned int id;
	char *subject;
};

struct rtclient_ticket_list {
	size_t length;
	struct rtclient_ticket *tickets[];
};

enum rtclient_ticket_history_type {
	RTCLIENT_TICKET_HISTORY_TYPE_CREATE
	, RTCLIENT_TICKET_HISTORY_TYPE_EMAILRECORD
	, RTCLIENT_TICKET_HISTORY_TYPE_SET
	, RTCLIENT_TICKET_HISTORY_TYPE_SETWATCHER
	, RTCLIENT_TICKET_HISTORY_TYPE_STATUS
};

enum rtclient_ticket_history_field {
	RTCLIENT_TICKET_HISTORY_FIELD_NONE
	, RTCLIENT_TICKET_HISTORY_FIELD_PRIORITY
	, RTCLIENT_TICKET_HISTORY_FIELD_STATUS
	, RTCLIENT_TICKET_HISTORY_FIELD_OWNER
};

struct rtclient_ticket_history {
	unsigned int id;
	unsigned int ticket;
	unsigned int time_taken;
	enum rtclient_ticket_history_type type;
	enum rtclient_ticket_history_field field;
	const char *old_value;
	const char *new_value;
	const char *data;
	const char *description;
	const char *content;
	const char *creator;
	struct tm *created;
	const char *attachments;
};

#ifdef __cplusplus
extern "C" {
#endif

	void rtclient_ticket_new(const char *queue
			, const char *requestor
			, const char *subject
			, const char *cc
			, const char *admincc
			, const char *owner
			, const char *status
			, const char *priority
			, const char *initialpriority
			, const char *finalpriority
			, const char *timeestimated
			, const char *starts
			, const char *due
			, const char *text);
	void rtclient_ticket_search(struct rtclient_ticket_list **listptr
			, const char *query);
	void rtclient_ticket_history(unsigned int id);
	void rtclient_ticket_freelist(struct rtclient_ticket_list *list);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_TICKET_H
