#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>



#include "easter.h"
#include "service.h"
#include "construct.h"

int main(int argc, char **argv)
{
int year;
int opt;
time_t t = time(NULL);
struct tm tm = *localtime(&t);

  while ((opt = getopt(argc, argv, ":m:")) != -1)
  {
    switch (opt)
     {
      case 'm':
        printf("Tisk měsíce %s\n", optarg);
        break;
      case ':':
        printf("Nebyl zadán měsíc -%c\n", optopt);
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

  int day_index;
  Service calendar[60];
  day_index = make_calendar(calendar, year);

  for (int d = 0; d < day_index; d++)
  {
    print_service(calendar[d]);
  }

  return 0;
}

