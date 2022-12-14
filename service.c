#include <stdio.h>
#include <time.h>

#include "service.h"

void set_full_tm(struct tm * date)
{
  time_t t = mktime(date);
  *date = *localtime(&t);
}

void print_service(Service line, const char * format)
{
  char date_buffer[12];
  strftime(date_buffer, 12, format, &line.date); /*  %Y-%m-%d, %-d.%-m. */
  printf("%11s %s\n", date_buffer, line.description);
}
