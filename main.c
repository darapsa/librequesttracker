#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <rtclient/client.h>
#include <rtclient/user.h>
#include <rtclient/ticket.h>

int main(void)
{
	char *url_line = NULL, *name_line = NULL, *pass_line = NULL;
	printf("URL: ");
	ssize_t url_nread = getline(&url_line, &(size_t){0}, stdin);
	printf("Name: ");
	ssize_t name_nread = getline(&name_line, &(size_t){0}, stdin);
	printf("Pass: ");
	ssize_t pass_nread = getline(&pass_line, &(size_t){0}, stdin);

	char *url = malloc(--url_nread + 1), *name = malloc(--name_nread + 1)
		, *pass = malloc(--pass_nread + 1);
	strncpy(url, url_line, url_nread);
	free(url_line);
	strncpy(name, name_line, name_nread);
	free(name_line);
	strncpy(pass, pass_line, pass_nread);
	free(pass_line);

	rtclient_init(url);
	free(url);

	rtclient_login(name, pass);
	free(pass);

	struct rtclient_user *user = NULL;
	rtclient_user_showname(&user, name);

	if (user) {
		printf("id: %d\nname: %s\npassword: %s\nemailaddress: %s\nrealname: %s\nnickname: %s\norganization: %s\naddress1: %s\naddress2: %s\ncity: %s\nstate: %s\nzip: %s\ncountry: %s\nhomephone: %s\nworkphone: %s\nmobilephone: %s\npagerphone: %s\ncontactinfo: %s\ncomments: %s\nsignature: %s\ngecos: %s\nlang: %d\ntimezone: %d\nprivileged: %d\ndisabled: %d\n"
				, user->id
				, user->name
				, user->password
				, user->emailaddress
				, user->realname
				, user->nickname
				, user->organization
				, user->address1
				, user->address2
				, user->city
				, user->state
				, user->zip
				, user->country
				, user->homephone
				, user->workphone
				, user->mobilephone
				, user->pagerphone
				, user->contactinfo
				, user->comments
				, user->signature
				, user->gecos
				, user->lang
				, user->timezone
				, user->privileged
				, user->disabled);
		rtclient_user_free(user);

		struct rtclient_ticketlist *list = NULL;
		static const char *prefix = "Owner='";
		char query[strlen(prefix) + strlen(name) + 2];
		sprintf(query, "%s%s'", prefix, name);
		rtclient_ticket_search(&list, query);
		if (list) {
			for (size_t i = 0; i < list->length; i++) {
				char *ticket = list->tickets[i];
				printf("Ticket %zu: %s\n", i, ticket);
			}
			rtclient_ticket_freelist(list);
		}
	}
	free(name);

	rtclient_cleanup();

	return 0;
}
