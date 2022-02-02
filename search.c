#ifdef DEBUG
#ifdef __ANDROID__
#include <android/log.h>
#else
#include <stdio.h>
#endif
#endif
#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "rtclient.h"
#include "rtclient/ticket.h"
#include "rtclient/search.h"

static void handle_search(rtclient_response *response)
{
	char data[response->numBytes];
	strcpy(data, response->data);
	char lines[response->numBytes];
	strcpy(lines, response->data);

	char *line = strtok(data, "\n");
	if (strstr(line, "200 Ok")) {
		line = strtok(NULL, "\n");
		size_t length = 0;
		do {
			length++;
			if (!strcmp(line, "No matching results."))
				return;
		} while ((line = strtok(NULL, "\n")));

		struct rtclient_ticket **list
			= malloc(sizeof(struct rtclient_ticket) * (length + 1));

		char *linesaveptr = NULL;
		line = strtok_r(lines, "\n", &linesaveptr);
		line = strtok_r(NULL, "\n", &linesaveptr);
		for (size_t i = 0; i < length; i++) {
			list[i] = malloc(sizeof(struct rtclient_ticket));
			struct rtclient_ticket *ticket = list[i];

			char *tokensaveptr = NULL;
			char *token = strtok_r(line, ":", &tokensaveptr);
			ticket->id = atoi(token);

			token = strtok_r(NULL, ":", &tokensaveptr);
			ticket->subject = malloc(strlen(token));
			strcpy(ticket->subject, ++token);

			line = strtok_r(NULL, "\n", &linesaveptr);
		}
		list[length] = NULL;
		((void (*)(struct rtclient_ticket **))response->userData)(list);
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

void rtclient_search_ticket(const char *query,
		void (*callback)(struct rtclient_ticket **))
{
	request(handle_search, (void (*)(void *))callback, NULL,
			"%s%s", "REST/1.0/search/ticket?query=", query);
}
