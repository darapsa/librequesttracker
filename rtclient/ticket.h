#ifndef RTCLIENT_TICKET_H
#define RTCLIENT_TICKET_H

struct rt_ticketlist {
	unsigned int length;
	char *tickets[];
};

#endif // RTCLIENT_TICKET_H
