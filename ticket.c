#if defined __ANDROID__ && defined DEBUG
#include <android/log.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "request.h"
#include "rtclient.h"
#include "rtclient/ticket.h"

typedef struct rtclient_ticket rtclient_ticket;
typedef struct rtclient_ticket_history_attachment history_attachment;
typedef struct rtclient_ticket_history_attachment_list attachment_list;

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
		const char *text)
{
	request(NULL, NULL, &(struct body){ 15, {
			{ "id", "ticket/new" },
			{ "Queue", queue },
			{ "Requestor", requestor },
			{ "Subject", subject },
			{ "Cc", cc },
			{ "AdminCc", admin_cc },
			{ "Owner", owner },
			{ "Status", status },
			{ "Priority", priority },
			{ "InitialPriority", initial_priority },
			{ "FinalPriority", final_priority },
			{ "TimeEstimated", time_estimated },
			{ "Starts", starts },
			{ "Due", due },
			{ "Text", text }
		}}, "%s", "REST/1.0/ticket/new");
}

static void handle_history(rtclient_response *response)
{
	char data[response->numBytes];
	strcpy(data, response->data);

	char *linesaveptr = NULL;
	char *line = strtok_r(data, "\n", &linesaveptr);
	if (strstr(line, "200 Ok")) {

		line = strtok_r(NULL, "\n", &linesaveptr);
		char *lengthstr = strtok(line, "/");
		size_t length = atoi(&lengthstr[2]);
		struct rtclient_ticket_history **list
			= malloc(sizeof(struct rtclient_ticket_history *)
					* (length + 1));

		for (size_t i = 0; i < length; i++) {
			line = strtok_r(NULL, "\n", &linesaveptr);
			list[i] = malloc(sizeof(struct rtclient_ticket_history));
			struct rtclient_ticket_history *ticket_history = list[i];

			char *tokensaveptr = NULL;
			char *token = strtok_r(line, ":", &tokensaveptr);
			ticket_history->id = atoi(token);

			ticket_history->ticket = 0;
			ticket_history->time_taken = 0;
			ticket_history->type = RTCLIENT_TICKET_HISTORY_TYPE_NONE;
			ticket_history->field = NULL;
			ticket_history->old_value = NULL;
			ticket_history->new_value = NULL;
			ticket_history->data = NULL;

			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket_history->description = malloc(strlen(token));
			strcpy(ticket_history->description, ++token);

			ticket_history->content = NULL;
			ticket_history->creator = NULL;
			ticket_history->created = NULL;
			ticket_history->attachments
				= malloc(sizeof(attachment_list));
			ticket_history->attachments->length = 0;
		}
		list[length] = NULL;
		((void (*)(struct rtclient_ticket_history **))response->userData)(list);
	} else {
#ifdef DEBUG
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "librtclient",
				"%s response status:\n%s", __func__, line);
#else
		printf("%s response status:\n%s\n", __func__, line);
#endif
#endif
	}
	rtclient_free_response(response);
}

static void handle_history_l(rtclient_response *response)
{
	char data[response->numBytes];
	strcpy(data, response->data);

	char *linesaveptr = NULL;
	char *line = strtok_r(data, "\n", &linesaveptr);
	if (strstr(line, "200 Ok")) {

		line = strtok_r(NULL, "\n", &linesaveptr);
		char *tokensaveptr = NULL;
		strtok_r(line, "/", &tokensaveptr);
		size_t length = atoi(strtok_r(NULL, "(", &tokensaveptr));
		struct rtclient_ticket_history **list
			= malloc(sizeof(struct rtclient_ticket_history *)
					* (length + 1));

		for (size_t i = 0; i < length; i++) {
			line = strtok_r(NULL, "\n", &linesaveptr);
			if (i)
				line = strtok_r(NULL, "\n", &linesaveptr);
			list[i] = malloc(sizeof(struct rtclient_ticket_history));
			struct rtclient_ticket_history *ticket_history = list[i];

			strtok_r(line, ":", &tokensaveptr);
			char *token = strtok_r(NULL, ":", &tokensaveptr);
			ticket_history->id = atoi(++token);
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket_history->ticket = atoi(++token);
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket_history->time_taken = atoi(++token);
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			if (!strcmp(++token, "AddLink"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_ADD_LINK;
			else if (!strcmp(token, "AddMember"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_ADD_MEMBER;
			else if (!strcmp(token, "AddMembership"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_ADD_MEMBERSHIP;
			else if (!strcmp(token, "AddReminder"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_ADD_REMINDER;
			else if (!strcmp(token, "AddWatcher"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_ADD_WATCHER;
			else if (!strcmp(token, "Comment"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_COMMENT;
			else if (!strcmp(token, "CommentEmailRecord"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_COMMENT_EMAIL_RECORD;
			else if (!strcmp(token, "Correspond"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_CORRESPOND;
			else if (!strcmp(token, "Create"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_CREATE;
			else if (!strcmp(token, "DelWatcher"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_DEL_WATCHER;
			else if (!strcmp(token, "Disabled"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_DISABLED;
			else if (!strcmp(token, "EmailRecord"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_EMAIL_RECORD;
			else if (!strcmp(token, "ResolveReminder"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_RESOLVE_REMINDER;
			else if (!strcmp(token, "Set"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_SET;
			else if (!strcmp(token, "SetWatcher"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_SET_WATCHER;
			else if (!strcmp(token, "Status"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_STATUS;
			else if (!strcmp(token, "SystemError"))
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_SYSTEM_ERROR;
			else
				ticket_history->type
					= RTCLIENT_TICKET_HISTORY_TYPE_NONE;
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			if (token && strcmp(token, "")) {
				ticket_history->field = malloc(strlen(token));
				strcpy(ticket_history->field, ++token);
			} else
				ticket_history->field = NULL;
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			if (token && strcmp(token, "")) {
				ticket_history->old_value
					= malloc(strlen(token));
				strcpy(ticket_history->old_value, ++token);
			} else
				ticket_history->old_value = NULL;
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			if (token && strcmp(token, "")) {
				ticket_history->new_value
					= malloc(strlen(token));
				strcpy(ticket_history->new_value, ++token);
			} else
				ticket_history->new_value = NULL;
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			if (token && strcmp(token, "")) {
				ticket_history->data = malloc(strlen(token));
				strcpy(ticket_history->data, ++token);
			} else
				ticket_history->data = NULL;
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			if (token && strcmp(token, "")) {
				ticket_history->description
					= malloc(strlen(token));
				strcpy(ticket_history->description, ++token);
			} else
				ticket_history->description = NULL;
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket_history->content = malloc(strlen(token));
			char *content = ticket_history->content;
			strcpy(content, ++token);
			line = strtok_r(NULL, "\n", &linesaveptr);
			while (strncmp(line, "Creator", 7)) {
				ticket_history->content = realloc(content,
						strlen(content) + strlen(line)
						+ 2);
				content = ticket_history->content;
				sprintf(content, "%s\n%s", content, line);
				line = strtok_r(NULL, "\n", &linesaveptr);
			}

			strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket_history->creator = malloc(strlen(token));
			strcpy(ticket_history->creator, ++token);
			line = strtok_r(NULL, "\n", &linesaveptr);

			strtok_r(line, ": -", &tokensaveptr);
			ticket_history->created = malloc(sizeof(struct tm));
			struct tm *created = ticket_history->created;
			created->tm_wday = 0;
			created->tm_yday = 0;
			created->tm_isdst = -1;
			token = strtok_r(NULL, ": -", &tokensaveptr);
			created->tm_year = atoi(token) - 1900;
			token = strtok_r(NULL, ": -", &tokensaveptr);
			created->tm_mon = atoi(token) - 1;
			token = strtok_r(NULL, ": -", &tokensaveptr);
			created->tm_mday = atoi(token);
			token = strtok_r(NULL, ": -", &tokensaveptr);
			created->tm_hour = atoi(token);
			token = strtok_r(NULL, ": -", &tokensaveptr);
			created->tm_min = atoi(token);
			token = strtok_r(NULL, ": -", &tokensaveptr);
			created->tm_sec = atoi(token);
			line = strtok_r(NULL, "\n", &linesaveptr);

			line = strtok_r(NULL, "\n", &linesaveptr);
			token = strtok_r(line, ": ()", &tokensaveptr);
			if (!token)
				break;

			ticket_history->attachments
				= malloc(sizeof(attachment_list));
			ticket_history->attachments->length = 0;
			size_t i = 0;
			while (strcmp(line, "--")) {
				ticket_history->attachments
					= realloc(ticket_history->attachments,
							sizeof(attachment_list)
							+ (i + 1)
							* sizeof
							(history_attachment));
				attachment_list *list
					= ticket_history->attachments;
				list->length++;
				list->attachments[i]
					= malloc(sizeof(history_attachment));
				history_attachment *attachment
					= list->attachments[i++];

				attachment->id = atoi(token);
				token = strtok_r(NULL, ": ()", &tokensaveptr);

				if (!strcmp(token, "untitled"))
					attachment->file_name = NULL;
				else {
					attachment->file_name
						= malloc(strlen(token) + 1);
					strcpy(attachment->file_name, token);
				}
				token = strtok_r(NULL, ": ()", &tokensaveptr);

				size_t length = strlen(token);
				char size[length];
				strncpy(size, token, length - 1);
				attachment->size = atoi(size);

				line = strtok_r(NULL, "\n", &linesaveptr);
				token = strtok_r(line, ": ()", &tokensaveptr);
			}
		}
		list[length] = NULL;
		((void (*)(struct rtclient_ticket_history **))
		 response->userData)(list);
	} else {
#ifdef DEBUG
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_INFO, "librtclient",
				"%s response status:\n%s", __func__, line);
#else
		printf("%s response status:\n%s\n", __func__, line);
#endif
#endif
	}
	rtclient_free_response(response);
}

void rtclient_ticket_history_list(unsigned int id, bool long_format,
		void (*callback)(struct rtclient_ticket_history **))
{
	if (long_format)
		request(handle_history_l, (void (*)(void *))callback, NULL,
				"%s%u%s", "REST/1.0/ticket/", id,
				"/history?format=l");
	else
		request(handle_history, (void (*)(void *))callback, NULL,
				"%s%u%s", "REST/1.0/ticket/", id, "/history");
}

void rtclient_ticket_history_free(struct rtclient_ticket_history *history)
{
	attachment_list *list = history->attachments;
	for (size_t i = 0; i < list->length; i++) {
		history_attachment *attachment = list->attachments[i];
		if (attachment->file_name)
			free(attachment->file_name);
		free(attachment);
	}
	free(list);
	free(history->created);
	free(history->creator);
	free(history->content);
	free(history->description);
	if (history->data)
		free(history->data);
	if (history->new_value)
		free(history->new_value);
	if (history->old_value)
		free(history->old_value);
	if (history->field)
		free(history->field);
	free(history);
	history = NULL;
}
