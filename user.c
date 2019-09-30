#include <stdlib.h>
#include <stdbool.h>
#include "post.h"
#include "rtclient/user.h"

typedef struct rtclient_user rtclient_user;

void rtclient_user_new(const char *name
		, const char *password
		, const char *emailaddress
		, const char *realname
		, const char *nickname
		, const char *organization
		, const char *address1
		, const char *address2
		, const char *city
		, const char *state
		, const char *zip
		, const char *country
		, const char *homephone
		, const char *workphone
		, const char *mobilephone
		, const char *pagerphone
		, const char *contactinfo
		, const char *comments
		, const char *signature
		, const char *gecos
		, enum rtclient_user_lang lang
		, enum rtclient_user_timezone timezone
		, bool disabled
		, bool privileged)
{
	post("REST/1.0/user/new", (const char *[]){
			name, "Name"
			, password, "Password"
			, emailaddress, "EmailAddress"
			, realname, "RealName"
			, nickname, "NickName"
			, organization, "Organization"
			, address1, "Address1"
			, address2, "Address2"
			, city, "City"
			, state, "State"
			, zip, "Zip"
			, country, "Country"
			, homephone, "HomePhone"
			, workphone, "WorkPhone"
			, mobilephone, "MobilePhone"
			, pagerphone, "PagerPhone"
			, contactinfo, "ContactInfo"
			, comments, "Comments"
			, signature, "Signature"
			, gecos, "Gecos"
	}, 40);
}

static size_t show_callback(void *contents, size_t size, size_t nmemb
		, void *writedata)
{
	size_t realsize = size * nmemb;
	char response[realsize + 1];
	memcpy(response, contents, realsize);
	response[realsize] = '\0';

	rtclient_user **userptr = (rtclient_user **)writedata;
	rtclient_user *user = *userptr;

	char *linesaveptr = NULL;
	char *line = strtok_r(response, "\n", &linesaveptr);
	if (strstr(line, "200 Ok")) {
		line = strtok_r(NULL, "\n", &linesaveptr);
		char *tokensaveptr = NULL, *token = NULL;
		do {
			token = strtok_r(line, ":", &tokensaveptr);
			if (!strcmp(token, "id")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				token += 6;
				user->id = atoi(token);
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

static inline void user_init(rtclient_user **userptr)
{
	*userptr = malloc(sizeof(rtclient_user));
	rtclient_user *user = *userptr;
	user->id = 0;
	user->name = NULL;
	user->password = NULL;
	user->emailaddress = NULL;
	user->realname = NULL;
	user->nickname = NULL;
	user->organization = NULL;
	user->address1 = NULL;
	user->address2 = NULL;
	user->city = NULL;
	user->state = NULL;
	user->zip = NULL;
	user->country = NULL;
	user->homephone = NULL;
	user->workphone = NULL;
	user->mobilephone = NULL;
	user->pagerphone = NULL;
	user->contactinfo = NULL;
	user->comments = NULL;
	user->signature = NULL;
	user->gecos = NULL;
	user->lang = RTCLIENT_USER_LANG_NONE;
	user->timezone = RTCLIENT_USER_TIMEZONE_NONE;
	user->privileged = false;
	user->disabled = true;
}

void rtclient_user_showid(rtclient_user **userptr, unsigned int id)
{
	user_init(userptr);
	request(show_callback, (void *)userptr, NULL, "%s%u", "REST/1.0/user/"
			, id);
}

void rtclient_user_showname(rtclient_user **userptr, const char *name)
{
	user_init(userptr);
	request(show_callback, (void *)userptr, NULL, "%s%s", "REST/1.0/user/"
			, name);
}

void rtclient_user_free(rtclient_user *user)
{
	if (user->name)
		free(user->name);
	if (user->password)
		free(user->password);
	if (user->emailaddress)
		free(user->emailaddress);
	if (user->realname)
		free(user->realname);
	if (user->nickname)
		free(user->nickname);
	if (user->organization)
		free(user->organization);
	if (user->address1)
		free(user->address1);
	if (user->address2)
		free(user->address2);
	if (user->city)
		free(user->city);
	if (user->state)
		free(user->state);
	if (user->zip)
		free(user->zip);
	if (user->country)
		free(user->country);
	if (user->homephone)
		free(user->homephone);
	if (user->workphone)
		free(user->workphone);
	if (user->mobilephone)
		free(user->mobilephone);
	if (user->pagerphone)
		free(user->pagerphone);
	if (user->contactinfo)
		free(user->contactinfo);
	if (user->comments)
		free(user->comments);
	if (user->signature)
		free(user->signature);
	if (user->gecos)
		free(user->gecos);
	free(user);
	user = NULL;
}
