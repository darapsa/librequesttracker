#ifdef DEBUG
#ifdef ANDROID
#include <android/log.h>
#else
#include <stdio.h>
#endif // ANDROID
#endif // DEBUG
#include <stdlib.h>
#include <string.h>
#include "rtclient/common.h"
#include "rtclient/user.h"

typedef struct rt_user rt_user;

static size_t show_callback(void *contents, size_t size, size_t nmemb
		, void *writedata)
{
	size_t realsize = size * nmemb;
	char response[realsize + 1];
	memcpy(response, contents, realsize);
	response[realsize] = '\0';

	rt_user **userptr = (rt_user **)writedata;
	rt_user *user = *userptr;

	char *linesaveptr = NULL;
	char *line = strtok_r(response, "\n", &linesaveptr);
	if (strstr(line, "200 Ok")) {
		line = strtok_r(NULL, "\n", &linesaveptr);
		char *tokensaveptr = NULL, *token = NULL;
		do {
			token = strtok_r(line, ":", &tokensaveptr);
			if (!strcmp(token, "id")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->id = malloc(strlen(token));
				strcpy(user->id, ++token);
			} else if (!strcmp(token, "Password")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->password = malloc(strlen(token));
				strcpy(user->password, ++token);
			} else if (!strcmp(token, "Name")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->name = malloc(strlen(token));
				strcpy(user->name, ++token);
			} else if (!strcmp(token, "EmailAddress")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->emailaddress = malloc(strlen(token));
				strcpy(user->emailaddress, ++token);
			} else if (!strcmp(token, "RealName")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->realname = malloc(strlen(token));
				strcpy(user->realname, ++token);
			} else if (!strcmp(token, "NickName")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->nickname = malloc(strlen(token));
				strcpy(user->nickname, ++token);
			} else if (!strcmp(token, "Gecos")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->gecos = malloc(strlen(token));
				strcpy(user->gecos, ++token);
			} else if (!strcmp(token, "Organization")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->organization = malloc(strlen(token));
				strcpy(user->organization, ++token);
			} else if (!strcmp(token, "Address1")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->address1 = malloc(strlen(token));
				strcpy(user->address1, ++token);
			} else if (!strcmp(token, "Address2")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->address2 = malloc(strlen(token));
				strcpy(user->address2, ++token);
			} else if (!strcmp(token, "City")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->city = malloc(strlen(token));
				strcpy(user->city, ++token);
			} else if (!strcmp(token, "State")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->state = malloc(strlen(token));
				strcpy(user->state, ++token);
			} else if (!strcmp(token, "Zip")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->zip = malloc(strlen(token));
				strcpy(user->zip, ++token);
			} else if (!strcmp(token, "Country")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->country = malloc(strlen(token));
				strcpy(user->country, ++token);
			} else if (!strcmp(token, "HomePhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->homephone = malloc(strlen(token));
				strcpy(user->homephone, ++token);
			} else if (!strcmp(token, "WorkPhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->workphone = malloc(strlen(token));
				strcpy(user->workphone, ++token);
			} else if (!strcmp(token, "MobilePhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->mobilephone = malloc(strlen(token));
				strcpy(user->mobilephone, ++token);
			} else if (!strcmp(token, "PagerPhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->pagerphone = malloc(strlen(token));
				strcpy(user->pagerphone, ++token);
			} else if (!strcmp(token, "ContactInfo")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->contactinfo = malloc(strlen(token));
				strcpy(user->contactinfo, ++token);
			} else if (!strcmp(token, "Comments")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->comments = malloc(strlen(token));
				strcpy(user->comments, ++token);
			} else if (!strcmp(token, "Signature")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->signature = malloc(strlen(token));
				strcpy(user->signature, ++token);
			} else if (!strcmp(token, "Lang")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				strncpy(user->lang, ++token, 2);
			} else if (!strcmp(token, "Privileged")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->privileged = (bool)atoi(++token);
			} else if (!strcmp(token, "Disabled")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->disabled = (bool)atoi(++token);
			}
		} while ((line = strtok_r(NULL, "\n", &linesaveptr)));
	} else {
		free(*userptr);
		*userptr = NULL;
#ifdef DEBUG
		fprintf(stderr, "%s response status: %s\n", __func__, line);
#endif
	}

	return realsize;
}

void rtclient_user_show(rt_user **userptr, const char *name)
{
	*userptr = malloc(sizeof(rt_user));
	request("/REST/1.0/user/", name, show_callback, (void *)userptr, NULL);
}

void rtclient_user_free(rt_user *user)
{
	free(user->id);
	free(user->password);
	free(user->name);
	free(user->emailaddress);
	free(user->realname);
	free(user->nickname);
	free(user->gecos);
	free(user->organization);
	free(user->address1);
	free(user->address2);
	free(user->city);
	free(user->state);
	free(user->zip);
	free(user->country);
	free(user->homephone);
	free(user->workphone);
	free(user->mobilephone);
	free(user->pagerphone);
	free(user->contactinfo);
	free(user->comments);
	free(user->signature);
	free(user);
	user = NULL;
}
