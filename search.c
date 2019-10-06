#include <stdlib.h>
#include "request.h"
#include "rtclient/ticket.h"
#include "rtclient/search.h"

typedef struct rtclient_ticket rtclient_ticket;
typedef struct rtclient_search_ticket_list rtclient_search_ticket_list;

static size_t ticket_handler(void *contents, size_t size, size_t nmemb
		, void *writedata)
{
	size_t realsize = size * nmemb;
	char response[realsize + 1];
	memcpy(response, contents, realsize);
	response[realsize] = '\0';
	char lines[strlen(response) + 1];
	strcpy(lines, response);
	rtclient_search_ticket_list **listptr
		= (rtclient_search_ticket_list **)writedata;
	rtclient_search_ticket_list *list = *listptr;

	char *line = strtok(response, "\n");
	if (strstr(line, "200 Ok")) {
		line = strtok(NULL, "\n");
		do {
			list->length++;
			if (!strcmp(line, "No matching results.")) {
				free(*listptr);
				*listptr = NULL;
				return realsize;
			}
		} while ((line = strtok(NULL, "\n")));

		*listptr = realloc(list, sizeof(rtclient_search_ticket_list)
				+ list->length * sizeof(rtclient_ticket));
		list = *listptr;

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

void rtclient_search_ticket(rtclient_search_ticket_list **listptr
		, const char *query)
{
	*listptr = malloc(sizeof(rtclient_search_ticket_list));
	(*listptr)->length = 0;
	request(ticket_handler, (void *)listptr, NULL, "%s%s"
			, "REST/1.0/search/ticket?query=", query);
}

void rtclient_search_ticket_free(rtclient_search_ticket_list *list)
{
	for (size_t i = 0; i < list->length; i++) {
		rtclient_ticket *ticket = list->tickets[i];
		free(ticket->subject);
		free(ticket);
	}
	free(list);
	list = NULL;
}
