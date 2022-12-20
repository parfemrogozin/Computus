#include <getopt.h>
#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>

#include "easter.h"
#include "service.h"
#include "construct.h"

int main(int argc, char **argv)
{
  Service calendar[60];
  int year = 0;
  int month = 0;
  int day_index = 0;
  int opt;
  bool next = false;
  time_t timestamp_now = time(NULL);
  struct tm tm_now = *localtime(&timestamp_now);

  while ((opt = getopt(argc, argv, ":m:p")) != -1)
  {
    switch (opt)
    {
      case 'm':
        month =  atoi(optarg);
        break;
      case 'p':
        next = true;
        break;
      case ':':
        printf("Použití: computus [rok] -%c <měsíc>\n", optopt);
        exit(-1);
        break;
    }
  }

  if (optind < argc)
  {
    while (optind < argc)
    {
      year = atoi(argv[optind++]);
    }
  }
  else
  {
    year = tm_now.tm_year + 1900;
  }

  if (year > 0)
  {
    day_index = make_calendar(calendar, year);
  }
  else
  {
  exit(-1);
  }

  if (month > 0)
  {
    find_month(calendar, month);
  }
  else if (next)
  {
    find_next(calendar, tm_now);
  }
  else
  {
    for (int d = 0; d < day_index; d++)
    {
      print_service(calendar[d], "%Y-%m-%d");
    }
  }
  return 0;
}

