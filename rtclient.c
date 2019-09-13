#ifdef DEBUG
#ifdef ANDROID
#include <android/log.h>
#else
#include <stdio.h>
#endif // ANDROID
#endif // DEBUG
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "rtclient.h"

typedef struct rt_user rt_user;
static CURL *curl = NULL;
static char *server_url = NULL;

bool rtclient_init(const char *url)
{
	curl_global_init(CURL_GLOBAL_SSL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
		curl_easy_setopt(curl, CURLOPT_REFERER, url);
#ifdef DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif // DEBUG
		server_url = malloc(strlen(url) + 1);
		strcpy(server_url, url);
	}

	return (bool)curl;
}

static size_t
user_callback(void *contents, size_t size, size_t nmemb, void *writedata)
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
	}

	return realsize;
}

inline static void request(const char *path, const char *suffix
		, size_t (*writefunction)(void *, size_t, size_t, void *)
		, void *writedata, struct curl_httppost *post)
{
	char url[strlen(server_url) + strlen(path) + strlen(suffix) + 1];
	sprintf(url, "%s%s%s", server_url, path, suffix);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
	if (writedata)
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, writedata);
	else
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
	if (post)
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	else
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

#ifdef DEBUG
	CURLcode res =
#endif // DEBUG
		curl_easy_perform(curl);
#ifdef DEBUG
	if (res != CURLE_OK) {
		const char *error = curl_easy_strerror(res);
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "librtclient", "%s: %s"
				, __func__, error);
#else
		fprintf(stderr, "%s: %s\n", __func__, error);
#endif // ANDROID
#endif // DEBUG
	}
}

void rtclient_login(const char *name, const char *password)
{
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last
			, CURLFORM_COPYNAME, "user"
			, CURLFORM_PTRCONTENTS, name
			, CURLFORM_END);
	curl_formadd(&post, &last
			, CURLFORM_COPYNAME, "pass"
			, CURLFORM_PTRCONTENTS, password
			, CURLFORM_END);
	last = NULL;
	request("", "", NULL, NULL, post);
	curl_formfree(post);
	post = NULL;
}

void rtclient_userget(rt_user **userptr, const char *name)
{
	*userptr = malloc(sizeof(rt_user));
	request("/REST/1.0/user/", name, user_callback, (void *)userptr, NULL);
}

void rtclient_search(const char *query)
{
	request("/REST/1.0/search/ticket?query=", query, NULL, NULL, NULL);
}

void rtclient_userfree(rt_user *user)
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

void rtclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
