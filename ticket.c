#include <stdlib.h>
#include "rtclient/request.h"
#include "rtclient/ticket.h"

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
	size_t length = strlen("id: ticket/new\n");
	if (queue && strcmp(queue, ""))
		length += strlen("Queue: \n") + strlen(queue);
	if (requestor && strcmp(requestor, ""))
		length += strlen("Requestor: \n") + strlen(requestor);
	if (subject && strcmp(subject, ""))
		length += strlen("Subject: \n") + strlen(subject);
	if (cc && strcmp(cc, ""))
		length += strlen("Cc: \n") + strlen(cc);
	if (admincc && strcmp(admincc, ""))
		length += strlen("AdminCc: \n") + strlen(admincc);
	if (owner && strcmp(owner, ""))
		length += strlen("Owner: \n") + strlen(owner);
	if (status && strcmp(status, ""))
		length += strlen("Status: \n") + strlen(status);
	if (priority && strcmp(priority, ""))
		length += strlen("Priority: \n") + strlen(priority);
	if (initialpriority && strcmp(initialpriority, ""))
		length += strlen("InitialPriority: \n") + strlen(initialpriority);
	if (finalpriority && strcmp(finalpriority, ""))
		length += strlen("FinalPriority: \n") + strlen(finalpriority);
	if (timeestimated && strcmp(timeestimated, ""))
		length += strlen("TimeEstimated: \n") + strlen(timeestimated);
	if (starts && strcmp(starts, ""))
		length += strlen("Starts: \n") + strlen(starts);
	if (due && strcmp(due, ""))
		length += strlen("Due: \n") + strlen(due);
	if (text && strcmp(text, ""))
		length += strlen("Text: \n") + strlen(text);

	char content[length + 1];
	strcpy(content, "id: ticket/new\n");
	if (queue && strcmp(queue, ""))
		sprintf(content, "%sQueue: %s\n", content, queue);
	if (requestor && strcmp(requestor, ""))
		sprintf(content, "%sRequestor: %s\n", content, requestor);
	if (subject && strcmp(subject, ""))
		sprintf(content, "%sSubject: %s\n", content, subject);
	if (cc && strcmp(cc, ""))
		sprintf(content, "%sCc: %s\n", content, cc);
	if (admincc && strcmp(admincc, ""))
		sprintf(content, "%sAdminCc: %s\n", content, admincc);
	if (owner && strcmp(owner, ""))
		sprintf(content, "%sOwner: %s\n", content, owner);
	if (status && strcmp(status, ""))
		sprintf(content, "%sStatus: %s\n", content, status);
	if (priority && strcmp(priority, ""))
		sprintf(content, "%sPriority: %s\n", content, priority);
	if (initialpriority && strcmp(initialpriority, ""))
		sprintf(content, "%sInitialPriority: %s\n", content, initialpriority);
	if (finalpriority && strcmp(finalpriority, ""))
		sprintf(content, "%sFinalPriority: %s\n", content, finalpriority);
	if (timeestimated && strcmp(timeestimated, ""))
		sprintf(content, "%sTimeEstimated: %s\n", content, timeestimated);
	if (starts && strcmp(starts, ""))
		sprintf(content, "%sStarts: %s\n", content, starts);
	if (due && strcmp(due, ""))
		sprintf(content, "%sDue: %s\n", content, due);
	if (text && strcmp(text, ""))
		sprintf(content, "%sText: %s\n", content, text);

	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last
			, CURLFORM_COPYNAME, "content"
			, CURLFORM_PTRCONTENTS, content
			, CURLFORM_END);
	last = NULL;
	request("/REST/1.0/ticket/new", "", NULL, NULL, post);
	curl_formfree(post);
	post = NULL;
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
		(*listptr)->length = 0;
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
		for (unsigned int i = 0; i < list->length; i++) {
			token = strtok_r(line, ":", &tokensaveptr);
			token = strtok_r(NULL, ":", &tokensaveptr);
			list->tickets[i] = malloc(strlen(token));
			strcpy(list->tickets[i], ++token);
			line = strtok_r(NULL, "\n", &linesaveptr);
		}
	} else {
		free(*listptr);
		*listptr = NULL;
#ifdef DEBUG
		fprintf(stderr, "%s response status: %s\n", __func__, line);
#endif
	}

	return realsize;
}

void rtclient_ticket_search(rtclient_ticketlist **listptr, const char *query)
{
	*listptr = malloc(sizeof(rtclient_ticketlist));
	request("/REST/1.0/search/ticket?query=", query, search_callback
			, (void *)listptr, NULL);
}

void rtclient_ticket_freelist(rtclient_ticketlist *list)
{
	for (unsigned short i = 0; i < list->length; i++)
		free(list->tickets[i]);
	free(list);
	list = NULL;
}
