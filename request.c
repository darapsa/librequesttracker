#if defined __ANDROID__ && defined DEBUG
#include <android/log.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "request.h"

#ifdef __EMSCRIPTEN__

extern emscripten_fetch_attr_t attr;

#else

#ifdef HAVE_THREADS_H
#include <threads.h>
#else
#include <pthread.h>
typedef pthread_t thrd_t;
#endif
#include <curl/curl.h>

extern char *server_url;
extern char *cookies_path;
extern char *cainfo;

struct container {
	struct curl_httppost *post;
	void (*handler)(rtclient_response *);
	rtclient_response *response;
};

static size_t append(char *data, size_t size, size_t nmemb, rtclient_response *response)
{
	size_t realsize = size * nmemb;
	response->data = realloc(response->data, response->numBytes + realsize + 1);
	memcpy(&(response->data[response->numBytes]), data, realsize);
	response->numBytes += realsize;
	response->data[response->numBytes] = '\0';
	return realsize;
}

static
#ifdef HAVE_THREADS_H
int
#else
void *
#endif
async(void *arg)
{
#ifdef HAVE_THREADS_H
	int ret = thrd_success;
#endif
	struct container *container = (struct container *)arg;
	CURLcode res = curl_easy_perform(container->response->curl);
	if (container->post)
		curl_formfree(container->post);
	if (res == CURLE_OK && container->handler)
		container->handler(container->response);
	else {
#ifdef HAVE_THREADS_H
		ret = thrd_error;
#endif
#ifdef DEBUG
		const char *error = curl_easy_strerror(res);
#ifdef __ANDROID__
		__android_log_print(ANDROID_LOG_ERROR, "librtclient.so", "%s", error);
#else
		fprintf(stderr, "%s\n", error);
#endif
#endif
	}
	free(container);
#ifdef HAVE_THREADS_H
	return ret;
#else
	return NULL;
#endif
}
#endif

void request(void (*handler)(rtclient_response *), void (*callback)(void *), struct body *body, char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	unsigned int uval;
	size_t length =
#ifndef __EMSCRIPTEN__
		strlen(server_url) +
#endif
		strlen(fmt);

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%')
			continue;
		switch(*++p) {
			case 's':
				sval = va_arg(ap, char *);
				length += strlen(sval) - 2;
				break;
			case 'u':
				uval = va_arg(ap, unsigned int);
				do {
					length++;
				} while ((uval /= 10));
				length -= 2;
				break;
			case 'c':
				length++;
				break;
			default:
				break;
		}
	}
	va_end(ap);

	char url[length + 1];
#ifdef __EMSCRIPTEN__
	memset(url, '\0', length + 1);
#else
	length = 0;
	strcpy(url, server_url);
#endif

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%')
			continue;
		switch(*++p) {
			case 's':
				sval = va_arg(ap, char *);
				strcat(url, sval);
				length = strlen(url);
				break;
			case 'u':
				uval = va_arg(ap, unsigned int);
				sprintf(url, "%s%u", url, uval);
				length = strlen(url);
				break;
			case 'c':
				url[length++] = (char)va_arg(ap, int);
				url[length] = '\0';
				break;
			default:
				break;
		}
	}
	va_end(ap);

#ifdef __EMSCRIPTEN__
	if (handler)
		attr.onsuccess = handler;
	if (body) {
		size_t length = 0;
		char *post = malloc(1);
		memset(post, '\0', 1);
		for (size_t i = 0; i < body->num_pairs; i++) {
			struct pair pair = body->pairs[i];
			if (!pair.value)
				continue;
			length += strlen(pair.key) + strlen(pair.value) + (i ? 1 : 0) + 1;
			post = realloc(post, length + 1);
			if (i)
				strcat(post, "&");
			sprintf(post, "%s%s=%s", post, pair.key, pair.value);
		}
		strcpy(attr.requestMethod, "POST");
		const char *headers[] = { "Content-Type", "application/x-www-form-urlencoded", NULL };
		attr.requestHeaders = headers;
		attr.requestData = post;
		attr.requestDataSize = length + 1;
		attr.userData = post;
	} else {
		strcpy(attr.requestMethod, "GET");
		attr.userData = callback;
	}
	emscripten_fetch(&attr, url);
#else
	CURL *curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookies_path);
	FILE *cookies_file = fopen(cookies_path, "r");
	if (cookies_file)
		fclose(cookies_file);
	else
		curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookies_path);
	curl_easy_setopt(curl, CURLOPT_REFERER, url);
	if (cainfo)
		curl_easy_setopt(curl, CURLOPT_CAINFO, cainfo);
#ifdef DEBUG
	curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
#endif
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, append);
	rtclient_response *response = malloc(sizeof(rtclient_response));
	response->data = malloc(1);
	response->numBytes = 0;
	response->userData = callback;
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
	struct curl_httppost *post = NULL;
	struct curl_httppost *last = NULL;
	if (body) {
		for (size_t i = 0; i < body->num_pairs; i++) {
			struct pair pair = body->pairs[i];
			if (!pair.value)
				continue;
			curl_formadd(&post, &last, CURLFORM_COPYNAME, pair.key, CURLFORM_PTRCONTENTS, pair.value, CURLFORM_END);
		}
		last = NULL;
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, post);
	} else
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
	struct container *container = malloc(sizeof(struct container));
	response->curl = curl;
	container->post = post;
	container->handler = handler;
	container->response = response;
	thrd_t thread;
#ifdef HAVE_THREADS_H
	thrd_create(&thread, async, container);
#else
	pthread_create(&thread, NULL, async, container);
#endif
#endif
}
