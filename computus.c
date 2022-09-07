#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "description.h"

typedef struct service
{
  struct tm date;
  char description[29];
} Service;


void set_full_tm(struct tm * date)
{
  time_t t = mktime(date);
  *date = *localtime(&t);
}

void print_service(Service line)
{
  char date_buffer[11];
  strftime(date_buffer, 11, "%Y-%m-%d", &line.date);
  printf("%s %s\n\n", date_buffer, line.description);
}

struct tm get_easter_date(int year)
{
  struct tm easter_date = {0};
    easter_date.tm_year = year - 1900; /* The number of years since 1900   */
    easter_date.tm_mon = 2; /* month, range 0 to 11 */
    easter_date.tm_mday = 22; /* day of the month, range 1 to 31  */
  int lunar_phase_cycle_position = year % 19;
  int leap_days_julian = year % 4;
  int is_non_leap = year % 7;
  double century = floor ((double)year / 100) ;
  double lunar_orbit_correction = floor((double)(13 + 8 * century) / 25.0);
  int start_century_correction  = (int)(15 - lunar_orbit_correction + century - (floor)(century / 4)) % 30;
  int julian_gregorian_leap_days_difference = (int)(4 + century - (floor)(century / 4)) % 7;
  int to_paschal_full_moon = (int)(19 * lunar_phase_cycle_position + start_century_correction) % 30;
  int to_next_sunday = (int)(2 * leap_days_julian + 4 * is_non_leap + 6 * to_paschal_full_moon + julian_gregorian_leap_days_difference) % 7;
  int mday = (easter_date.tm_mday + to_paschal_full_moon + to_next_sunday);

  if ((to_paschal_full_moon == 29) && (to_next_sunday == 6))
  {
    easter_date.tm_mon += 1;
    easter_date.tm_mday = 19;
  }
  else if ((to_paschal_full_moon == 28) && (to_next_sunday == 6))
  {
    easter_date.tm_mon += 1;
    easter_date.tm_mday = 18;
  }
  else
  if (mday > 31)
  {
    easter_date.tm_mon += 1;
    easter_date.tm_mday = mday - 31;
  }
  else
  {
    easter_date.tm_mday = mday;
  }
  set_full_tm(&easter_date);
  return easter_date;
}

struct tm get_last_sunday (int year)
{
  time_t t;
  struct tm last_sunday = {0};
  struct tm last_advent_sunday = {0};
    last_advent_sunday.tm_year = year - 1900; /* The number of years since 1900   */
    last_advent_sunday.tm_mon = 11; /* month, range 0 to 11 */
    last_advent_sunday.tm_mday = 25; /* day of the month, range 1 to 31  */

  set_full_tm(&last_advent_sunday);

  if (last_advent_sunday.tm_wday == 0)
  {
    last_advent_sunday.tm_mday = last_advent_sunday.tm_mday - 7;
  }
  else
  {
    last_advent_sunday.tm_mday = last_advent_sunday.tm_mday - last_advent_sunday.tm_wday;
  }

  t = mktime(&last_advent_sunday);
  t -= SECONDS_IN_WEEK * 4;
  last_sunday = *localtime(&t);


  return  last_sunday;
}

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

int main(int argc, char **argv)
{
  int year;
  int i = 0;
  int ti = 0;
  int si = 1;
  time_t t = time(NULL);
  struct tm current_time = *localtime(&t);

  struct tm cur_sunday, last_sunday, last_sunday_prev = {0};
  Service next_service = {0};
  Service between_service = {0};
  time_t cur_sunday_t, next_t, end_t;

  if (argc < 2)
  {
    year = current_time.tm_year + 1900;
  }
  else
  {
    year = atoi(argv[1]);
  }

  last_sunday_prev = get_last_sunday(year - 1);
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
    next_t = mktime(&next_service.date);


    while ( cur_sunday_t < next_t )
    {
      between_service = get_regular(tides[ti], &cur_sunday_t, si);
      print_service(between_service);
      si++;
      cur_sunday_t += SECONDS_IN_WEEK;
    }


    print_service(next_service);
    if ( feast_list[i].starts_tide )
    {
      ti++;
      si = 1;
    }
    i++;

  } while (cur_sunday_t + SECONDS_IN_WEEK < end_t);

  return 0;
}

