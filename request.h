#ifndef RTCLIENT_REQUEST_H
#define RTCLIENT_REQUEST_H

#if defined(DEBUG) && defined(ANDROID)
#include <android/log.h>
#endif
#include <string.h>
#include <stdio.h>
#include <curl/curl.h>

extern CURL *curl;
extern char *server_url;

inline void request(const char *path, const char *suffix
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
	}
#endif // DEBUG
}
#endif // RTCLIENT_REQUEST_H
