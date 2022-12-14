#include <time.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


#include "easter.h"
#include "construct.h"

extern Feast feast_list[];
extern char tides[][14];

Service get_service(Feast * prototype, int year)
{
  Service date_and_desc = {0};
  struct tm easter_relative;
  time_t easter_relative_t;
  strncpy(date_and_desc.description, prototype->description, 29);
  if (prototype->day > 0)
  {
    date_and_desc.date.tm_mon = prototype->month;
    date_and_desc.date.tm_mday = prototype->day;
    date_and_desc.date.tm_year = year-1900;
  }
  else
  {
    easter_relative = get_easter_date(year);
    easter_relative_t = mktime(&easter_relative);
    easter_relative_t +=  prototype->easter_delta;
    date_and_desc.date =  *localtime(&easter_relative_t);
  }

  set_full_tm(&date_and_desc.date);
  return date_and_desc;
}

Service get_regular(char * tide, time_t * time, int si)
{
  Service date_and_desc = {0};
  char buffer[12];
  sprintf(buffer, "%d. neděle ", si);
  date_and_desc.date =  *localtime(time);
  strncat (date_and_desc.description, buffer, 12);
  strncat (date_and_desc.description, tide, 14);
  return date_and_desc;
}

int make_calendar(Service * calendar, int year)
{
  const int service_hour = 9;
  int start_year;
  int i = 0;
  int ti = 0;
  int si = 1;


  struct tm cur_sunday, last_sunday, last_sunday_prev = {0};
  Service next_service = {0};
  Service between_service = {0};
  time_t cur_sunday_t, next_t, end_t;
  int day_index = 0;

  start_year = year -1;
  last_sunday_prev = get_last_sunday(start_year);
  cur_sunday_t = mktime(&last_sunday_prev);
  cur_sunday_t += SECONDS_IN_WEEK;
  cur_sunday = *localtime(&cur_sunday_t);
  last_sunday = get_last_sunday(year);
  feast_list[13].day = last_sunday.tm_mday;
  feast_list[13].month = last_sunday.tm_mon;
  end_t = mktime(&last_sunday);


  do
  {
    cur_sunday = *localtime(&cur_sunday_t);
    year = cur_sunday.tm_year + 1900;
    if (cur_sunday.tm_mday == next_service.date.tm_mday && cur_sunday.tm_mon == next_service.date.tm_mon)
    {
      cur_sunday_t += SECONDS_IN_WEEK;
    }
    next_service = get_service(&feast_list[i], year);
    if (year == start_year && next_service.date.tm_mon == 0 && next_service.date.tm_mday == 6)
    {
      next_service.date.tm_year++;
    }
    next_t = mktime(&next_service.date);


    while ( cur_sunday_t < next_t )
    {
      between_service = get_regular(tides[ti], &cur_sunday_t, si);
      between_service.date.tm_hour = service_hour;
      calendar[day_index] = between_service;
      day_index++;
      si++;
      cur_sunday_t += SECONDS_IN_WEEK;
    }

    next_service.date.tm_hour = service_hour;
    calendar[day_index] = next_service;
    day_index++;
    if ( feast_list[i].starts_tide )
    {
      ti++;
      si = 1;
    }
    i++;

  assert(day_index < 60);

  } while (cur_sunday_t + SECONDS_IN_WEEK < end_t);

  return day_index;
}

void find_month(Service * calendar, int mon)
{
  mon -= 1;
  for (int day_index = 0; day_index < 58; day_index++)
  {
    if (calendar[day_index].date.tm_mon == mon)
    {
      print_service(calendar[day_index], "%-d.%-m. %H:%M");
    }
  }
}