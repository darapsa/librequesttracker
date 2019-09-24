#include <stdbool.h>
#include <stdlib.h>
#include "request.h"
#include "rtclient/client.h"

CURL *curl = NULL;
char *server_url = NULL;

bool rtclient_init(const char *url, const char *certificate)
{
	curl_global_init(CURL_GLOBAL_SSL);
	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "");
		curl_easy_setopt(curl, CURLOPT_REFERER, url);
		if (certificate)
			curl_easy_setopt(curl, CURLOPT_CAINFO, certificate);
#ifdef DEBUG
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
		size_t length = strlen(url);
		bool append = !(bool)(url[length - 1] == '/');
		server_url = malloc(length + (size_t)append + 1);
		strcpy(server_url, url);
		if (append)
			strcat(server_url, "/");
	}

	return (bool)curl;
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
	request(NULL, NULL, post, "");
	curl_formfree(post);
	post = NULL;
}

void rtclient_cleanup()
{
	if (curl) {
		free(server_url);
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
