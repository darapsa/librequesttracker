#include <stdlib.h>
#include <string.h>
#include "request.h"
#include "rtclient.h"

#ifdef __EMSCRIPTEN__
emscripten_fetch_attr_t attr;
#else
char *server_url = NULL;
char *cookies_path = NULL;
char *cainfo = NULL;
#endif

void rtclient_init(const char *url, const char *cookies,
		const char *certificate)
{
#ifdef __EMSCRIPTEN__
	emscripten_fetch_attr_init(&attr);
	attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
#else
	size_t length = strlen(url);
	size_t append = url[length - 1] != '/';
	server_url = malloc(length + append + 1);
	strcpy(server_url, url);
	if (append)
		strcat(server_url, "/");
	cookies_path = malloc(strlen(cookies) + 1);
	strcpy(cookies_path, cookies);
	curl_global_init(CURL_GLOBAL_SSL);
	if (certificate) {
		cainfo = malloc(strlen(certificate) + 1);
		strcpy(cainfo, certificate);
	}
#endif
}

void rtclient_login(const char *name, const char *password,
		void (*handler)(rtclient_response *))
{
	request(handler, NULL, &(struct body){ 2, {
			{ "user", name },
			{ "pass", password }
		}}, "");
}

void rtclient_free_response(rtclient_response *response)
{
#ifdef __EMSCRIPTEN__
	if (response->userData)
		free(response->userData);
	emscripten_fetch_close(response);
#else
	free(response->data);
	curl_easy_cleanup(response->curl);
	free(response);
#endif
}

void rtclient_cleanup()
{
#ifndef __EMSCRIPTEN__
	if (cainfo)
		free(cainfo);
	free(cookies_path);
	free(server_url);
	curl_global_cleanup();
#endif
}
