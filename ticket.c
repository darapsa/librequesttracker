#include <stdlib.h>
#include "post.h"
#include "rtclient/ticket.h"

typedef struct rtclient_ticket rtclient_ticket;
typedef struct rtclient_ticket_list rtclient_ticket_list;

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
			, const char *text)
{
	post("REST/1.0/ticket/new", (const char *[]){
			"ticket/new", "id"
			, queue, "Queue"
			, requestor, "Requestor"
			, subject, "Subject"
			, cc, "Cc"
			, admin_cc, "AdminCc"
			, owner, "Owner"
			, status, "Status"
			, priority, "Priority"
			, initial_priority, "InitialPriority"
			, final_priority, "FinalPriority"
			, time_estimated, "TimeEstimated"
			, starts, "Starts"
			, due, "Due"
			, text, "Text"
			}, 28);
}

static size_t search_handler(void *contents, size_t size, size_t nmemb
		, void *writedata)
{
	size_t realsize = size * nmemb;
	char response[realsize + 1];
	memcpy(response, contents, realsize);
	response[realsize] = '\0';
	char lines[strlen(response) + 1];
	strcpy(lines, response);
	rtclient_ticket_list **listptr = (rtclient_ticket_list **)writedata;

	char *line = strtok(response, "\n");
	if (strstr(line, "200 Ok")) {
		line = strtok(NULL, "\n");
		do {
			(*listptr)->length++;
			if (!strcmp(line, "No matching results.")) {
				free(*listptr);
				*listptr = NULL;
				return realsize;
			}
		} while ((line = strtok(NULL, "\n")));

		rtclient_ticket_list *ptr = realloc(*listptr, sizeof(*listptr)
				+ (*listptr)->length * sizeof(rtclient_ticket));
		*listptr = ptr;
		rtclient_ticket_list *list = *listptr;

		char *linesaveptr = NULL;
		line = strtok_r(lines, "\n", &linesaveptr);
		line = strtok_r(NULL, "\n", &linesaveptr);
		char *tokensaveptr = NULL, *token = NULL;
		for (size_t i = 0; i < list->length; i++) {
			list->tickets[i] = malloc(sizeof(rtclient_ticket));
			rtclient_ticket *ticket = list->tickets[i]; 
			token = strtok_r(line, ":", &tokensaveptr);
			ticket->id = atoi(token);
			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket->subject = malloc(strlen(token));
			strcpy(ticket->subject, ++token);
			line = strtok_r(NULL, "\n", &linesaveptr);
		}
	} else {
		free(*listptr);
		*listptr = NULL;
#ifdef DEBUG
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_INFO, "librtclient"
				, "%s response status:\n%s", __func__, line);
#else
		printf("%s response status:\n%s\n", __func__, line);
#endif // ANDROID
#endif // DEBUG
	}

	return realsize;
}

void rtclient_ticket_search(rtclient_ticket_list **listptr, const char *query)
{
	*listptr = malloc(sizeof(rtclient_ticket_list));
	(*listptr)->length = 0;
	request(search_handler, (void *)listptr, NULL, "%s%s"
			, "REST/1.0/search/ticket?query=", query);
}

void rtclient_ticket_history(unsigned int id)
{
	request(NULL, NULL, NULL, "%s%u%s", "REST/1.0/ticket/", id
			, "/history?format=l");
}

void rtclient_ticket_freelist(rtclient_ticket_list *list)
{
	for (size_t i = 0; i < list->length; i++) {
		rtclient_ticket *ticket = list->tickets[i];
		free(ticket->subject);
		free(ticket);
	}
	free(list);
	list = NULL;
}
