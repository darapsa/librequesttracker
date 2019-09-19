#include "request.h"

inline void post(const char *path, const char *pairs[], size_t n)
{
	size_t length = 0;
	for (size_t i = 0; i < n; i += 2) {
		const char *pair = pairs[i];
		if (pair && strcmp(pair, ""))
			length += strlen(pair) + strlen(++pair) + 3;
	}

	char content[length + 1];
	memset(content, 0, strlen(content));
	for (size_t i = 0; i < n; i += 2) {
		const char *pair = pairs[i];
		if (pair && strcmp(pair, ""))
			sprintf(content, "%s%s: %s\n", content, pairs[i + 1]
					, pair);
	}

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
