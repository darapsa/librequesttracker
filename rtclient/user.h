#ifndef RTCLIENT_USER_H
#define RTCLIENT_USER_H

#include <stdbool.h>

struct rt_user {
	char *id;
	char *password;
	char *name;
	char *emailaddress;
	char *realname;
	char *nickname;
	char *gecos;
	char *organization;
	char *address1;
	char *address2;
	char *city;
	char *state;
	char *zip;
	char *country;
	char *homephone;
	char *workphone;
	char *mobilephone;
	char *pagerphone;
	char *contactinfo;
	char *comments;
	char *signature;
	char lang[2];
	bool privileged;
	bool disabled;
};

#ifdef __cplusplus
extern "C" {
#endif

	void rtclient_user_show(struct rt_user **userptr, const char *name);
	void rtclient_user_free(struct rt_user *user);

#ifdef __cplusplus
}
#endif

#endif // RTCLIENT_USER_H
