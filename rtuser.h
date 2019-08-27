#ifndef RTUSER_H
#define RTUSER_H

typedef struct rt_user {
	unsigned int id;
	char *name;
	char *password;
	char *authtoken;
	char *emailaddress;
	char *organization;
	char *realname;
	char *nickname;
	char *lang;
	char *gecos;
	char *homephone;
	char *workphone;
	char *mobilephone;
	char *pagerphone;
	char *address1;
	char *address2;
	char *city;
	char *state;
	char *zip;
	char *country;
	char *timezone;
} rt_user;

#endif // RTUSER_H
