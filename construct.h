#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include "description.h"
#include "service.h"

Service get_service(Feast * prototype, int year);
Service get_regular(char * tide, time_t * time, int si);
int make_calendar(Service * calendar, int year);
#endif