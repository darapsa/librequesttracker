#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

struct rtclient_ticket {
	unsigned int id;
	char *subject;
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
			, const char *admin_cc
			, const char *owner
			, const char *status
			, const char *priority
			, const char *initial_priority
			, const char *final_priority
			, const char *time_estimated
			, const char *starts
			, const char *due
			, const char *text);
	void rtclient_ticket_history(unsigned int id);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_TICKET_H
