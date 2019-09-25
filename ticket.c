#include <stdlib.h>
#include "post.h"
#include "rtclient/ticket.h"

typedef struct rtclient_ticket rtclient_ticket;
typedef struct rtclient_ticketlist rtclient_ticketlist;

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
			, const char *text)
{
	post("REST/1.0/ticket/new", (const char *[]){
			"ticket/new", "id"
			, queue, "Queue"
			, requestor, "Requestor"
			, subject, "Subject"
			, cc, "Cc"
			, admincc, "AdminCc"
			, owner, "Owner"
			, status, "Status"
			, priority, "Priority"
			, initialpriority, "InitialPriority"
			, finalpriority, "FinalPriority"
			, timeestimated, "TimeEstimated"
			, starts, "Starts"
			, due, "Due"
			, text, "Text"
			}, 28);
}

static size_t search_callback(void *contents, size_t size, size_t nmemb
		, void *writedata)
{
	size_t realsize = size * nmemb;
	char response[realsize + 1];
	memcpy(response, contents, realsize);
	response[realsize] = '\0';
	char lines[strlen(response) + 1];
	strcpy(lines, response);
	rtclient_ticketlist **listptr = (rtclient_ticketlist **)writedata;

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
		rtclient_ticketlist *ptr = realloc(*listptr, sizeof(*listptr)
				+ (*listptr)->length * sizeof(char *));
		*listptr = ptr;
		rtclient_ticketlist *list = *listptr;
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

void rtclient_ticket_search(rtclient_ticketlist **listptr, const char *query)
{
	*listptr = malloc(sizeof(rtclient_ticketlist));
	(*listptr)->length = 0;
	request(search_callback, (void *)listptr, NULL, "%s%s"
			, "REST/1.0/search/ticket?query=", query);
}

void rtclient_ticket_history(unsigned int id)
{
	request(NULL, NULL, NULL, "%s%d%s", "REST/1.0/ticket/", id
			, "/history?format=l");
}

void rtclient_ticket_freelist(rtclient_ticketlist *list)
{
	for (size_t i = 0; i < list->length; i++) {
		rtclient_ticket *ticket = list->tickets[i];
		free(ticket->subject);
		free(ticket);
	}
	free(list);
	list = NULL;
}
