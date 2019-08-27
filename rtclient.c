#ifdef DEBUG
#ifdef ANDROID
#include <android/log.h>
#else
#include <stdio.h>
#endif // ANDROID
#endif // DEBUG
#include <stdbool.h>
#include <curl/curl.h>
#include "rtclient.h"

static CURL *handle = NULL;

bool rtclient_init()
{
	curl_global_init(CURL_GLOBAL_SSL);
	handle = curl_easy_init();
	if (handle) {
		curl_easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 1L);
#ifdef DEBUG
		curl_easy_setopt(handle, CURLOPT_VERBOSE, 1L);
#endif
	}

	return (bool)handle;
}

void rtclient_cleanup()
{
	if (handle)
		curl_easy_cleanup(handle);
	curl_global_cleanup();
}
