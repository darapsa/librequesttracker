#ifdef DEBUG
#ifdef __ANDROID__
#include <android/log.h>
#else
#include <stdio.h>
#endif
#endif
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "request.h"
#include "rtclient.h"
#include "rtclient/user.h"

void rtclient_user_new(const char *name,
		const char *password,
		const char *email_address,
		const char *real_name,
		const char *nick_name,
		const char *organization,
		const char *address1,
		const char *address2,
		const char *city,
		const char *state,
		const char *zip,
		const char *country,
		const char *home_phone,
		const char *work_phone,
		const char *mobile_phone,
		const char *pager_phone,
		const char *contact_info,
		const char *comments,
		const char *signature,
		const char *gecos,
		enum rtclient_user_lang lang,
		enum rtclient_user_timezone timezone,
		bool disabled,
		bool privileged)
{
	request(NULL, NULL, &(struct body){ 20, {
			{ "Name", name },
			{ "Password", password },
			{ "EmailAddress", email_address },
			{ "RealName", real_name },
			{ "NickName", nick_name },
			{ "Organization", organization },
			{ "Address1", address1 },
			{ "Address2", address2 },
			{ "City", city },
			{ "State", state },
			{ "Zip", zip },
			{ "Country", country },
			{ "HomePhone", home_phone },
			{ "WorkPhone", work_phone },
			{ "MobilePhone", mobile_phone },
			{ "PagerPhone", pager_phone },
			{ "ContactInfo", contact_info },
			{ "Comments", comments },
			{ "Signature", signature },
			{ "Gecos", gecos }
	}}, "%s", "REST/1.0/user/new");
}

static void handle_show(rtclient_response *response)
{
	char data[response->numBytes];
	strcpy(data, response->data);

	char *linesaveptr = NULL;
	char *line = strtok_r(data, "\n", &linesaveptr);
	if (strstr(line, "200 Ok")) {
		line = strtok_r(NULL, "\n", &linesaveptr);
		struct rtclient_user *user = malloc(sizeof(struct rtclient_user));
		user->password = NULL;
		user->email_address = NULL;
		user->real_name = NULL;
		user->nick_name = NULL;
		user->organization = NULL;
		user->address1 = NULL;
		user->address2 = NULL;
		user->city = NULL;
		user->state = NULL;
		user->zip = NULL;
		user->country = NULL;
		user->home_phone = NULL;
		user->work_phone = NULL;
		user->mobile_phone = NULL;
		user->pager_phone = NULL;
		user->contact_info = NULL;
		user->comments = NULL;
		user->signature = NULL;
		user->gecos = NULL;
		user->lang = RTCLIENT_USER_LANG_NONE;
		user->timezone = RTCLIENT_USER_TIMEZONE_NONE;
		user->privileged = false;
		user->disabled = true;
		do {
			char *tokensaveptr = NULL;
			char *token = strtok_r(line, ":", &tokensaveptr);
			if (!strcmp(token, "id")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				token += 6;
				user->id = atoi(token);
			} else if (!strcmp(token, "Name")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->name = malloc(strlen(token));
				strcpy(user->name, ++token);
			} else if (!strcmp(token, "EmailAddress")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->email_address = malloc(strlen(token));
				strcpy(user->email_address, ++token);
			} else if (!strcmp(token, "RealName")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->real_name = malloc(strlen(token));
				strcpy(user->real_name, ++token);
			} else if (!strcmp(token, "NickName")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->nick_name = malloc(strlen(token));
				strcpy(user->nick_name, ++token);
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
				user->home_phone = malloc(strlen(token));
				strcpy(user->home_phone, ++token);
			} else if (!strcmp(token, "WorkPhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->work_phone = malloc(strlen(token));
				strcpy(user->work_phone, ++token);
			} else if (!strcmp(token, "MobilePhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->mobile_phone = malloc(strlen(token));
				strcpy(user->mobile_phone, ++token);
			} else if (!strcmp(token, "PagerPhone")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->pager_phone = malloc(strlen(token));
				strcpy(user->pager_phone, ++token);
			} else if (!strcmp(token, "ContactInfo")) {
				token = strtok_r(NULL, ":", &tokensaveptr);
				user->contact_info = malloc(strlen(token));
				strcpy(user->contact_info, ++token);
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
		((void (*)(struct rtclient_user *))response->userData)(user);
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

void rtclient_user_showid(unsigned int id, void (*callback)(struct rtclient_user *))
{
	request(handle_show, (void (*)(void *))callback, NULL, "%s%u", "REST/1.0/user/", id);
}

void rtclient_user_showname(const char *name, void (*callback)(struct rtclient_user *))
{
	request(handle_show, (void (*)(void *))callback, NULL, "%s%s", "REST/1.0/user/", name);
}

void rtclient_user_free(struct rtclient_user *user)
{
	if (user->gecos)
		free(user->gecos);
	if (user->signature)
		free(user->signature);
	if (user->comments)
		free(user->comments);
	if (user->contact_info)
		free(user->contact_info);
	if (user->pager_phone)
		free(user->pager_phone);
	if (user->mobile_phone)
		free(user->mobile_phone);
	if (user->work_phone)
		free(user->work_phone);
	if (user->home_phone)
		free(user->home_phone);
	if (user->country)
		free(user->country);
	if (user->zip)
		free(user->zip);
	if (user->state)
		free(user->state);
	if (user->city)
		free(user->city);
	if (user->address2)
		free(user->address2);
	if (user->address1)
		free(user->address1);
	if (user->organization)
		free(user->organization);
	if (user->nick_name)
		free(user->nick_name);
	if (user->real_name)
		free(user->real_name);
	if (user->email_address)
		free(user->email_address);
	if (user->password)
		free(user->password);
	if (user->name)
		free(user->name);
	free(user);
	user = NULL;
}
