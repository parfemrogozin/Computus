#include <getopt.h>
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
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);

  while ((opt = getopt(argc, argv, ":m:")) != -1)
  {
    switch (opt)
    {
      case 'm':
        month =  atoi(optarg);
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
    year = tm.tm_year + 1900;
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
  else
  {
    for (int d = 0; d < day_index; d++)
    {
      print_service(calendar[d]);
    }
  }
  return 0;
}

