#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "description.h"


int main(int argc, char **argv)
{
  Service calendar[60];
  day_index = make_calendar(calendar, year);

  for (int d = 0; d < day_index; d++)
  {
    print_service(calendar[d]);
  }

  return 0;
}

