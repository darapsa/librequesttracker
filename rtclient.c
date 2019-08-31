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

static CURL *handle = NULL;
static char *server_url = NULL;

bool rtclient_init(const char *url)
{
	curl_global_init(CURL_GLOBAL_SSL);
	handle = curl_easy_init();
	if (handle) {
		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
#ifdef DEBUG
		curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
#endif // DEBUG
		server_url = malloc(strlen(url) + 1);
		strcpy(server_url, url);
	}

	return (bool)handle;
}

static size_t handle_login(const char *response, size_t size, size_t nmemb, void *writedata)
{
#ifdef DEBUG
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "librtclient.so", "Login response:\n%s", response);
#else
	fprintf(stderr, "Login response:\n%s\n", response);
#endif // ANDROID
#endif // DEBUG
	return size * nmemb;
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

	curl_easy_setopt(handle, CURLOPT_URL, server_url);
	curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, handle_login);
	curl_easy_setopt(handle, CURLOPT_HTTPPOST, post);
#ifdef DEBUG
	CURLcode res =
#endif // DEBUG
		curl_easy_perform(handle);
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

void rtclient_cleanup()
{
	if (handle) {
		free(server_url);
		curl_easy_cleanup(handle);
	}
	curl_global_cleanup();
}
