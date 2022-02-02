#ifndef REQUEST_H
#define REQUEST_H

#include "rtclient/typedefs.h"

struct body {
	size_t num_pairs;
	struct pair {
		const char *key;
		const char *value;
	} pairs[20];
};

void request(void (*)(rtclient_response *), void (*)(void *), struct body *, char *, ...);

#endif
