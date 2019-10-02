#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

struct rtclient_ticket {
	unsigned int id;
	char *subject;
};

enum rtclient_ticket_result_format {
	RTCLIENT_TICKET_RESULT_FORMAT_S = 0
	, RTCLIENT_TICKET_RESULT_FORMAT_I
	, RTCLIENT_TICKET_RESULT_FORMAT_L
};

enum rtclient_ticket_history_type {
	RTCLIENT_TICKET_HISTORY_TYPE_UNKNOWN = 0
	, RTCLIENT_TICKET_HISTORY_TYPE_CREATE
	, RTCLIENT_TICKET_HISTORY_TYPE_EMAIL_RECORD
	, RTCLIENT_TICKET_HISTORY_TYPE_SET
	, RTCLIENT_TICKET_HISTORY_TYPE_SET_WATCHER
	, RTCLIENT_TICKET_HISTORY_TYPE_STATUS
};

enum rtclient_ticket_history_field {
	RTCLIENT_TICKET_HISTORY_FIELD_NONE = 0
	, RTCLIENT_TICKET_HISTORY_FIELD_PRIORITY
	, RTCLIENT_TICKET_HISTORY_FIELD_STATUS
	, RTCLIENT_TICKET_HISTORY_FIELD_OWNER
};

struct rtclient_ticket_history_attachment {
	unsigned int id;
	char *file_name;
	size_t size;
};

struct rtclient_ticket_history {
	unsigned int id;
	unsigned int ticket;
	unsigned int time_taken;
	enum rtclient_ticket_history_type type;
	enum rtclient_ticket_history_field field;
	char *old_value;
	char *new_value;
	char *data;
	char *description;
	char *content;
	char *creator;
	struct tm *created;
	struct {
		size_t length;
		struct rtclient_ticket_history_attachment *attachments[];
	} *attachments;
};

struct rtclient_ticket_history_list {
	size_t length;
	struct rtclient_ticket_history *histories[];
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
	void rtclient_ticket_history(struct rtclient_ticket_history_list **listptr
			, unsigned int id
			, enum rtclient_ticket_result_format result_format);
	void rtclient_ticket_history_free
		(struct rtclient_ticket_history *history);
	void rtclient_ticket_history_list_free
		(struct rtclient_ticket_history_list *list);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_TICKET_H
