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

void rtclient_login(const char *name, const char *password)
{
	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "user",
			CURLFORM_PTRCONTENTS, name,
			CURLFORM_END);
	curl_formadd(&post, &last,
			CURLFORM_COPYNAME, "pass",
			CURLFORM_PTRCONTENTS, password,
			CURLFORM_END);
	last = NULL;

	curl_easy_setopt(curl, CURLOPT_URL, server_url);
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
#ifdef DEBUG
	CURLcode res =
#endif // DEBUG
		curl_easy_perform(curl);
#ifdef DEBUG
	if (res != CURLE_OK) {
		const char *error = curl_easy_strerror(res);
#ifdef ANDROID
		__android_log_print(ANDROID_LOG_ERROR, "librtclient.so", "cURL perform error: %s", error);
#else
		fprintf(stderr, "cURL perform error: %s\n", error);
#endif // ANDROID
	}
#endif // DEBUG
}

static size_t
user_callback(void *contents, size_t size, size_t nmemb, void *writedata)
{
	size_t realsize = size * nmemb;
	char response[realsize + 1];
	memcpy(response, contents, realsize);
	response[realsize] = '\0';

	static const unsigned short nproperties = 24;
	char *lines[nproperties];
	char *line = strtok(response, "\n");
	if (strstr(line, "200 Ok")) {
		line = strtok(NULL, "\n");
		unsigned short i = 0;
		while (line && i < nproperties) {
			lines[i++] = line;
			line = strtok(NULL, "\n");
		}
		rt_user **userp = (rt_user **)writedata;
		rt_user *user = *userp;
		for (unsigned short i = 0; i < nproperties; i++) {
			char *token = strtok(lines[i], ":");
			if (!strcmp(token, "id")) {
				token = strtok(NULL, ":");
				user->id = malloc(strlen(token));
				strcpy(user->id, ++token);
			} else if (!strcmp(token, "Password")) {
				token = strtok(NULL, ":");
				user->password = malloc(strlen(token));
				strcpy(user->password, ++token);
			} else if (!strcmp(token, "Name")) {
				token = strtok(NULL, ":");
				user->name = malloc(strlen(token));
				strcpy(user->name, ++token);
			} else if (!strcmp(token, "EmailAddress")) {
				token = strtok(NULL, ":");
				user->emailaddress = malloc(strlen(token));
				strcpy(user->emailaddress, ++token);
			} else if (!strcmp(token, "RealName")) {
				token = strtok(NULL, ":");
				user->realname = malloc(strlen(token));
				strcpy(user->realname, ++token);
			} else if (!strcmp(token, "NickName")) {
				token = strtok(NULL, ":");
				user->nickname = malloc(strlen(token));
				strcpy(user->nickname, ++token);
			} else if (!strcmp(token, "Gecos")) {
				token = strtok(NULL, ":");
				user->gecos = malloc(strlen(token));
				strcpy(user->gecos, ++token);
			} else if (!strcmp(token, "Organization")) {
				token = strtok(NULL, ":");
				user->organization = malloc(strlen(token));
				strcpy(user->organization, ++token);
			} else if (!strcmp(token, "Address1")) {
				token = strtok(NULL, ":");
				user->address1 = malloc(strlen(token));
				strcpy(user->address1, ++token);
			} else if (!strcmp(token, "Address2")) {
				token = strtok(NULL, ":");
				user->address2 = malloc(strlen(token));
				strcpy(user->address2, ++token);
			} else if (!strcmp(token, "City")) {
				token = strtok(NULL, ":");
				user->city = malloc(strlen(token));
				strcpy(user->city, ++token);
			} else if (!strcmp(token, "State")) {
				token = strtok(NULL, ":");
				user->state = malloc(strlen(token));
				strcpy(user->state, ++token);
			} else if (!strcmp(token, "Zip")) {
				token = strtok(NULL, ":");
				user->zip = malloc(strlen(token));
				strcpy(user->zip, ++token);
			} else if (!strcmp(token, "Country")) {
				token = strtok(NULL, ":");
				user->country = malloc(strlen(token));
				strcpy(user->country, ++token);
			} else if (!strcmp(token, "HomePhone")) {
				token = strtok(NULL, ":");
				user->homephone = malloc(strlen(token));
				strcpy(user->homephone, ++token);
			} else if (!strcmp(token, "WorkPhone")) {
				token = strtok(NULL, ":");
				user->workphone = malloc(strlen(token));
				strcpy(user->workphone, ++token);
			} else if (!strcmp(token, "MobilePhone")) {
				token = strtok(NULL, ":");
				user->mobilephone = malloc(strlen(token));
				strcpy(user->mobilephone, ++token);
			} else if (!strcmp(token, "PagerPhone")) {
				token = strtok(NULL, ":");
				user->pagerphone = malloc(strlen(token));
				strcpy(user->pagerphone, ++token);
			} else if (!strcmp(token, "ContactInfo")) {
				token = strtok(NULL, ":");
				user->contactinfo = malloc(strlen(token));
				strcpy(user->contactinfo, ++token);
			} else if (!strcmp(token, "Comments")) {
				token = strtok(NULL, ":");
				user->comments = malloc(strlen(token));
				strcpy(user->comments, ++token);
			} else if (!strcmp(token, "Signature")) {
				token = strtok(NULL, ":");
				user->signature = malloc(strlen(token));
				strcpy(user->signature, ++token);
			} else if (!strcmp(token, "Lang")) {
				token = strtok(NULL, ":");
				strncpy(user->lang, ++token, 2);
			} else if (!strcmp(token, "Privileged")) {
				token = strtok(NULL, ":");
				user->privileged = (bool)atoi(++token);
			} else if (!strcmp(token, "Disabled")) {
				token = strtok(NULL, ":");
				user->disabled = (bool)atoi(++token);
			}
		}
	}

	return realsize;
}

static inline void request(const char *path, const char *suffix)
{
	char url[strlen(server_url) + strlen(path) + strlen(suffix) + 1];
	sprintf(url, "%s%s%s", server_url, path, suffix);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	curl_easy_perform(curl);
}

bool rtclient_get_user(rt_user **user, const char *name)
{
	*user = malloc(sizeof(rt_user));
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)user);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, user_callback);
	request("/REST/1.0/user/", name);
	return (bool)(*user);
}

void rtclient_search(const char *query)
{
	request("/REST/1.0/search/ticket?query=", query);
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
}

void rtclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
