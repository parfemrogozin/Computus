#ifndef SERVICE_H
#define SERVICE_H

#include <time.h>


typedef struct service
{
  struct tm date;
  char description[29];
} Service;

void set_full_tm(struct tm * date);
void print_service(Service line);
#endif
