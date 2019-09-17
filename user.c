#include <stdlib.h>
#include "rtclient/request.h"
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
		, enum rt_lang lang
		, enum rt_timezone timezone
		, bool disabled
		, bool privileged)
{
	size_t length = 0;
	if (name && strcmp(name, ""))
		length += strlen("name: \n") + strlen(name);
	if (emailaddress && strcmp(emailaddress, ""))
		length += strlen("emailaddress: \n") + strlen(emailaddress);
	if (realname && strcmp(realname, ""))
		length += strlen("realname: \n") + strlen(realname);
	if (nickname && strcmp(nickname, ""))
		length += strlen("nickname: \n") + strlen(nickname);
	if (gecos && strcmp(gecos, ""))
		length += strlen("gecos: \n") + strlen(gecos);
	if (contactinfo && strcmp(contactinfo, ""))
		length += strlen("contactinfo: \n") + strlen(contactinfo);
	if (password && strcmp(password, ""))
		length += strlen("password: \n") + strlen(password);
	if (comments && strcmp(comments, ""))
		length += strlen("comments: \n") + strlen(comments);
	if (signature && strcmp(signature, ""))
		length += strlen("signature: \n") + strlen(signature);
	if (organization && strcmp(organization, ""))
		length += strlen("organization: \n") + strlen(organization);
	if (address1 && strcmp(address1, ""))
		length += strlen("address1: \n") + strlen(address1);
	if (address2 && strcmp(address2, ""))
		length += strlen("address1: \n") + strlen(address2);
	if (city && strcmp(city, ""))
		length += strlen("city: \n") + strlen(city);
	if (state && strcmp(state, ""))
		length += strlen("state: \n") + strlen(state);
	if (zip && strcmp(zip, ""))
		length += strlen("zip: \n") + strlen(zip);
	if (country && strcmp(country, ""))
		length += strlen("country: \n") + strlen(country);
	if (homephone && strcmp(homephone, ""))
		length += strlen("homephone: \n") + strlen(homephone);
	if (workphone && strcmp(workphone, ""))
		length += strlen("workphone: \n") + strlen(workphone);
	if (mobilephone && strcmp(mobilephone, ""))
		length += strlen("mobilephone: \n") + strlen(mobilephone);
	if (pagerphone && strcmp(pagerphone, ""))
		length += strlen("pagerphone: \n") + strlen(pagerphone);

	char content[length + strlen("privileged: \nenabled: \n") + 3];
	if (name && strcmp(name, ""))
		sprintf(content, "%sname: %s\n", content, name);
	if (emailaddress && strcmp(emailaddress, ""))
		sprintf(content, "%semailaddress: %s\n", content, emailaddress);
	if (realname && strcmp(realname, ""))
		sprintf(content, "%srealname: %s\n", content, realname);
	if (nickname && strcmp(nickname, ""))
		sprintf(content, "%snickname: %s\n", content, nickname);
	if (gecos && strcmp(gecos, ""))
		sprintf(content, "%sgecos: %s\n", content, gecos);
	if (contactinfo && strcmp(contactinfo, ""))
		sprintf(content, "%scontactinfo: %s\n", content, contactinfo);
	if (password && strcmp(password, ""))
		sprintf(content, "%spassword: %s\n", content, password);
	if (comments && strcmp(comments, ""))
		sprintf(content, "%scomments: %s\n", content, comments);
	if (signature && strcmp(signature, ""))
		sprintf(content, "%ssignature: %s\n", content, signature);
	if (organization && strcmp(organization, ""))
		sprintf(content, "%sorganization: %s\n", content, organization);
	if (address1 && strcmp(address1, ""))
		sprintf(content, "%saddress1: %s\n", content, address1);
	if (address2 && strcmp(address2, ""))
		sprintf(content, "%saddress2: %s\n", content, address2);
	if (city && strcmp(city, ""))
		sprintf(content, "%scity: %s\n", content, city);
	if (state && strcmp(state, ""))
		sprintf(content, "%sstate: %s\n", content, state);
	if (zip && strcmp(zip, ""))
		sprintf(content, "%szip: %s\n", content, zip);
	if (country && strcmp(country, ""))
		sprintf(content, "%scountry: %s\n", content, country);
	if (homephone && strcmp(homephone, ""))
		sprintf(content, "%shomephone: %s\n", content, homephone);
	if (workphone && strcmp(workphone, ""))
		sprintf(content, "%sworkphone: %s\n", content, workphone);
	if (mobilephone && strcmp(mobilephone, ""))
		sprintf(content, "%smobilephone: %s\n", content, mobilephone);
	if (pagerphone && strcmp(pagerphone, ""))
		sprintf(content, "%spagerphone: %s\n", content, pagerphone);

	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last
			, CURLFORM_COPYNAME, "content"
			, CURLFORM_PTRCONTENTS, content
			, CURLFORM_END);
	last = NULL;
	request("", "", NULL, NULL, post);
	curl_formfree(post);
	post = NULL;
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
