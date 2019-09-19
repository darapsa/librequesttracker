#include "request.h"

extern inline void request(const char *, const char *
		, size_t (*)(void *, size_t, size_t, void *)
		, void *, struct curl_httppost *);
