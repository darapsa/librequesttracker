#ifndef RTCLIENT_COMMON_H
#define RTCLIENT_COMMON_H

#include <curl/curl.h>

extern CURL *curl;
extern char *server_url;

void request(const char *path, const char *suffix
		, size_t (*writefunction)(void *, size_t, size_t, void *)
		, void *writedata, struct curl_httppost *post);

#endif // RTCLIENT_COMMON_H
