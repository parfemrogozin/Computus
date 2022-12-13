#include <stdio.h>
#include <time.h>

#include "service.h"

void set_full_tm(struct tm * date)
{
  time_t t = mktime(date);
  *date = *localtime(&t);
}

void print_service(Service line)
{
  char date_buffer[11];
  strftime(date_buffer, 11, "%Y-%m-%d", &line.date);
  printf("%s %s\n", date_buffer, line.description);
}
