#ifdef DEBUG
#ifdef ANDROID
#include <android/log.h>
#else
#include <stdio.h>
#endif // ANDROID
#endif // DEBUG
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "rtclient.h"

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

static inline void request(const char *url)
{
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	curl_easy_perform(curl);
}

void rtclient_user(const char *name)
{
	static const char *path = "/REST/1.0/user/";
	char url[strlen(server_url) + strlen(path) + strlen(name) + 1];
	sprintf(url, "%s%s%s", server_url, path, name);
	request(url);
}

void rtclient_search(const char *query)
{
	static const char *path = "/REST/1.0/search/ticket?query=";
	char url[strlen(server_url) + strlen(path) + strlen(query) + 1];
	sprintf(url, "%s%s%s", server_url, path, query);
	request(url);
}

void rtclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
