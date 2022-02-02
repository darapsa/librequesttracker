#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

#include <stdbool.h>

struct rtclient_ticket {
	unsigned int id;
	char *subject;
};

enum rtclient_ticket_history_type {
	RTCLIENT_TICKET_HISTORY_TYPE_NONE = 0,
	RTCLIENT_TICKET_HISTORY_TYPE_ADD_LINK,
	RTCLIENT_TICKET_HISTORY_TYPE_ADD_MEMBER,
	RTCLIENT_TICKET_HISTORY_TYPE_ADD_MEMBERSHIP,
	RTCLIENT_TICKET_HISTORY_TYPE_ADD_REMINDER,
	RTCLIENT_TICKET_HISTORY_TYPE_ADD_WATCHER,
	RTCLIENT_TICKET_HISTORY_TYPE_COMMENT,
	RTCLIENT_TICKET_HISTORY_TYPE_COMMENT_EMAIL_RECORD,
	RTCLIENT_TICKET_HISTORY_TYPE_CORRESPOND,
	RTCLIENT_TICKET_HISTORY_TYPE_CREATE,
	RTCLIENT_TICKET_HISTORY_TYPE_DEL_WATCHER,
	RTCLIENT_TICKET_HISTORY_TYPE_DISABLED,
	RTCLIENT_TICKET_HISTORY_TYPE_EMAIL_RECORD,
	RTCLIENT_TICKET_HISTORY_TYPE_RESOLVE_REMINDER,
	RTCLIENT_TICKET_HISTORY_TYPE_SET,
	RTCLIENT_TICKET_HISTORY_TYPE_SET_WATCHER,
	RTCLIENT_TICKET_HISTORY_TYPE_STATUS,
	RTCLIENT_TICKET_HISTORY_TYPE_SYSTEM_ERROR
};

struct rtclient_ticket_history_attachment {
	unsigned int id;
	char *file_name;
	size_t size;
};

struct rtclient_ticket_history_attachment_list {
	size_t length;
	struct rtclient_ticket_history_attachment *attachments[];
};

struct rtclient_ticket_history {
	unsigned int id;
	unsigned int ticket;
	unsigned int time_taken;
	enum rtclient_ticket_history_type type;
	char *field;
	char *old_value;
	char *new_value;
	char *data;
	char *description;
	char *content;
	char *creator;
	struct tm *created;
	struct rtclient_ticket_history_attachment_list *attachments;
};

struct rtclient_ticket_history_list {
	size_t length;
	struct rtclient_ticket_history *histories[];
};

#ifdef __cplusplus
extern "C" {
#endif

void rtclient_ticket_new(const char *queue,
		const char *requestor,
		const char *subject,
		const char *cc,
		const char *admin_cc,
		const char *owner,
		const char *status,
		const char *priority,
		const char *initial_priority,
		const char *final_priority,
		const char *time_estimated,
		const char *starts,
		const char *due,
		const char *text);
	void rtclient_ticket_history(struct rtclient_ticket_history_list **listptr
			, unsigned int id, bool long_format);
	void rtclient_ticket_history_free
		(struct rtclient_ticket_history *history);
	void rtclient_ticket_history_list_free
		(struct rtclient_ticket_history_list *list);

#ifdef __cplusplus
}
#endif

#endif
