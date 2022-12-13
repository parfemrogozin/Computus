#ifndef CONSTRUCT_H
#define CONSTRUCT_H

#include <stdbool.h>
#include "description.h"
#include "service.h"

typedef struct feast
{
  char description[29]; //29
  unsigned char month; //1
  unsigned char day; //1
  bool starts_tide; //1
  time_t easter_delta; //8
}Feast;

Service get_service(Feast * prototype, int year);
Service get_regular(char * tide, time_t * time, int si);
int make_calendar(Service * calendar, int year);
#endif