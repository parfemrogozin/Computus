#include "construct.h"

Feast feast_list[MAIN_FEAST_COUNT] =
{
  { "Boží hod vánoční", 11, 25, true, 0},
  { "Mučedníka Štěpána", 11, 26,false, 0},
  { "Epifanie", 0, 6,  true, 0 },
  { "Masopustní neděle", 0, 0, false,  -7 * SECONDS_IN_WEEK },
  { "Popeleční středa", 0, 0, true, -46 * SECONDS_IN_DAY },
  { "Květná neděle", 0, 0, false, -1 * SECONDS_IN_WEEK },
  { "Zelený čtvrtek", 0, 0, false, -3 * SECONDS_IN_DAY },
  { "Velký pátek", 0, 0, false, -2 * SECONDS_IN_DAY },
  { "Boží hod velikonoční", 0, 0, true,  0 },
  { "Nanebevstoupení Páně", 0, 0, false, 39 * SECONDS_IN_DAY }, /* maybe true and delete next */
  { "Neděle po nanebevstoupení", 0, 0, false, 6 * SECONDS_IN_WEEK },
  { "Hod sv. Ducha", 0, 0, false, 7 * SECONDS_IN_WEEK },
  { "Hod sv. Trojice", 0, 0, true, 8 * SECONDS_IN_WEEK },
  { "poslední neděle v roce", 0, 0, false, 0 }
};

char tides[][14] =
{
  "adventní",
  "vánoční",
  "po Epifanii",
  "postní",
  "velikonoční",
  "po Trojici"
};