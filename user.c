#include <stdlib.h>
#include "rtclient/request.h"
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
		, enum rtclient_lang lang
		, enum rtclient_timezone timezone
		, bool disabled
		, bool privileged)
{
	size_t length = 0;
	if (name && strcmp(name, ""))
		length += strlen("Name: \n") + strlen(name);
	if (password && strcmp(password, ""))
		length += strlen("Password: \n") + strlen(password);
	if (emailaddress && strcmp(emailaddress, ""))
		length += strlen("EmailAddress: \n") + strlen(emailaddress);
	if (realname && strcmp(realname, ""))
		length += strlen("RealName: \n") + strlen(realname);
	if (nickname && strcmp(nickname, ""))
		length += strlen("NickName: \n") + strlen(nickname);
	if (organization && strcmp(organization, ""))
		length += strlen("Organization: \n") + strlen(organization);
	if (address1 && strcmp(address1, ""))
		length += strlen("Address1: \n") + strlen(address1);
	if (address2 && strcmp(address2, ""))
		length += strlen("Address1: \n") + strlen(address2);
	if (city && strcmp(city, ""))
		length += strlen("City: \n") + strlen(city);
	if (state && strcmp(state, ""))
		length += strlen("State: \n") + strlen(state);
	if (zip && strcmp(zip, ""))
		length += strlen("Zip: \n") + strlen(zip);
	if (country && strcmp(country, ""))
		length += strlen("Country: \n") + strlen(country);
	if (homephone && strcmp(homephone, ""))
		length += strlen("HomePhone: \n") + strlen(homephone);
	if (workphone && strcmp(workphone, ""))
		length += strlen("WorkPhone: \n") + strlen(workphone);
	if (mobilephone && strcmp(mobilephone, ""))
		length += strlen("MobilePhone: \n") + strlen(mobilephone);
	if (pagerphone && strcmp(pagerphone, ""))
		length += strlen("PagerPhone: \n") + strlen(pagerphone);
	if (contactinfo && strcmp(contactinfo, ""))
		length += strlen("ContactInfo: \n") + strlen(contactinfo);
	if (comments && strcmp(comments, ""))
		length += strlen("Comments: \n") + strlen(comments);
	if (signature && strcmp(signature, ""))
		length += strlen("Signature: \n") + strlen(signature);
	if (gecos && strcmp(gecos, ""))
		length += strlen("Gecos: \n") + strlen(gecos);

	char content[length + strlen("Privileged: \nDisabled: \n") + 3];
	memset(content, 0, strlen(content));
	if (name && strcmp(name, ""))
		sprintf(content, "%sName: %s\n", content, name);
	if (password && strcmp(password, ""))
		sprintf(content, "%sPassword: %s\n", content, password);
	if (emailaddress && strcmp(emailaddress, ""))
		sprintf(content, "%sEmailAddress: %s\n", content, emailaddress);
	if (realname && strcmp(realname, ""))
		sprintf(content, "%sRealName: %s\n", content, realname);
	if (nickname && strcmp(nickname, ""))
		sprintf(content, "%sNickName: %s\n", content, nickname);
	if (organization && strcmp(organization, ""))
		sprintf(content, "%sOrganization: %s\n", content, organization);
	if (address1 && strcmp(address1, ""))
		sprintf(content, "%sAddress1: %s\n", content, address1);
	if (address2 && strcmp(address2, ""))
		sprintf(content, "%sAddress2: %s\n", content, address2);
	if (city && strcmp(city, ""))
		sprintf(content, "%sCity: %s\n", content, city);
	if (state && strcmp(state, ""))
		sprintf(content, "%sState: %s\n", content, state);
	if (zip && strcmp(zip, ""))
		sprintf(content, "%sZip: %s\n", content, zip);
	if (country && strcmp(country, ""))
		sprintf(content, "%sCountry: %s\n", content, country);
	if (homephone && strcmp(homephone, ""))
		sprintf(content, "%sHomePhone: %s\n", content, homephone);
	if (workphone && strcmp(workphone, ""))
		sprintf(content, "%sWorkPhone: %s\n", content, workphone);
	if (mobilephone && strcmp(mobilephone, ""))
		sprintf(content, "%sMobilePhone: %s\n", content, mobilephone);
	if (pagerphone && strcmp(pagerphone, ""))
		sprintf(content, "%sPagerPhone: %s\n", content, pagerphone);
	if (contactinfo && strcmp(contactinfo, ""))
		sprintf(content, "%sContactInfo: %s\n", content, contactinfo);
	if (comments && strcmp(comments, ""))
		sprintf(content, "%sComments: %s\n", content, comments);
	if (signature && strcmp(signature, ""))
		sprintf(content, "%sSignature: %s\n", content, signature);
	if (gecos && strcmp(gecos, ""))
		sprintf(content, "%sGecos: %s\n", content, gecos);
	sprintf(content, "%sPrivileged: %d\nDisabled: %d\n", content, privileged
			, disabled);

	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last
			, CURLFORM_COPYNAME, "content"
			, CURLFORM_PTRCONTENTS, content
			, CURLFORM_END);
	last = NULL;
	request("/REST/1.0/user/new", "", NULL, NULL, post);
	curl_formfree(post);
	post = NULL;
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

void rtclient_user_show(rtclient_user **userptr, const char *name)
{
	*userptr = malloc(sizeof(rtclient_user));
	rtclient_user *user = *userptr;
	user->id = NULL;
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
	user->lang = RTCLIENT_LANG_NONE;
	user->timezone = RTCLIENT_TIMEZONE_NONE;
	user->privileged = false;
	user->disabled = true;
	request("/REST/1.0/user/", name, show_callback, (void *)userptr, NULL);
}

void rtclient_user_free(rtclient_user *user)
{
	if (user->id)
		free(user->id);
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
