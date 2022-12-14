#include <time.h>
#include <math.h>

#include "service.h"
#include "description.h"
#include "easter.h"

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