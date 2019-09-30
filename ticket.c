#include <stdlib.h>
#include "post.h"
#include "rtclient/ticket.h"

typedef struct rtclient_ticket rtclient_ticket;

void rtclient_ticket_new(const char *queue
			, const char *requestor
			, const char *subject
			, const char *cc
			, const char *admin_cc
			, const char *owner
			, const char *status
			, const char *priority
			, const char *initial_priority
			, const char *final_priority
			, const char *time_estimated
			, const char *starts
			, const char *due
			, const char *text)
{
	post("REST/1.0/ticket/new", (const char *[]){
			"ticket/new", "id"
			, queue, "Queue"
			, requestor, "Requestor"
			, subject, "Subject"
			, cc, "Cc"
			, admin_cc, "AdminCc"
			, owner, "Owner"
			, status, "Status"
			, priority, "Priority"
			, initial_priority, "InitialPriority"
			, final_priority, "FinalPriority"
			, time_estimated, "TimeEstimated"
			, starts, "Starts"
			, due, "Due"
			, text, "Text"
			}, 28);
}

void rtclient_ticket_history(unsigned int id)
{
	request(NULL, NULL, NULL, "%s%u%s", "REST/1.0/ticket/", id
			, "/history?format=l");
}
