const int SECONDS_IN_DAY = 86400;
const int SECONDS_IN_WEEK = SECONDS_IN_DAY * 7;



const char* const tides[] = {
  "adventní",
  "vánoční",
  "po Epfanii",
  "postní",
  "velikonoční",
  "po Trojici",
  };

const char* const fixed_feast_name[] = {
  "Boží hod vánoční",
  "Mučedníka Štěpána",
  "Epifanie"

};

const char* const fixed_feast_date[] = {
  "12-25",
  "12-26",
  "01-06"
};

const char* const easter_related_name[] = {
  "Masopustní neděle",
  "Popeleční středa",
  "Květná neděle",
  "Zelený čtvrtek",
  "Velký pátek",
  "Boží hod velikonoční",
  "Nanebevstoupení Páně",
  "Neděle po nanebevstoupení",
  "Hod. sv. Ducha",
  "Hod sv. Trojice",
};

const time_t easter_related_timedelta[] =
{
  -7 * SECONDS_IN_WEEK,
  -46 * SECONDS_IN_DAY,
  -SECONDS_IN_WEEK,
  -3 * SECONDS_IN_DAY,
  -2 * SECONDS_IN_DAY,
  0,
  39 * SECONDS_IN_DAY,
  6 * SECONDS_IN_WEEK,
  7 * SECONDS_IN_WEEK,
  8 * SECONDS_IN_WEEK
};

char * starts_tide[] =
{
  fixed_feast_name[0],
  fixed_feast_name[3],
  easter_related_name[1],
  easter_related_name[5],
easter_related_name[9]
};

