#include "request.h"

inline void post(const char *path, const char *pairs[], size_t n)
{
	size_t length = 0;
	for (size_t i = 0; i < n; i += 2) {
		const char *pair = pairs[i];
		if (pair && strcmp(pair, ""))
			length += strlen(pair) + strlen(pairs[i + 1]) + 3;
	}

	char content[length + 1];
	memset(content, 0, strlen(content));
	for (size_t i = 0; i < n; i += 2) {
		const char *pair = pairs[i];
		if (pair && strcmp(pair, ""))
			sprintf(content, "%s%s: %s\n", content, pairs[i + 1]
					, pair);
	}
#ifdef DEBUG
#ifdef ANDROID
	__android_log_print(ANDROID_LOG_DEBUG, "librtclient", "%s\nContent:\n%s"
			, __func__, content);
#else
	fprintf(stderr, "%s\nContent:\n%s", __func__, content);
#endif // ANDROID
#endif // DEBUG

	struct curl_httppost *post, *last = NULL;
	curl_formadd(&post, &last
			, CURLFORM_COPYNAME, "content"
			, CURLFORM_PTRCONTENTS, content
			, CURLFORM_END);
	last = NULL;
	request(path, "", NULL, NULL, post);
	curl_formfree(post);
	post = NULL;
}
