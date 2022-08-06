const int SECONDS_IN_DAY = 86400;
const int SECONDS_IN_WEEK = SECONDS_IN_DAY * 7;



char tides[][13] = {
  "adventní",
  "vánoční",
  "po Epfanii",
  "postní",
  "velikonoční",
  "po Trojici",
  };

char fixed_feast_date[][6] = {
  "12-25",
  "12-26",
  "01-06"
};

char feast_name[][27] = {
  "Boží hod vánoční", //0 t f0
  "Mučedníka Štěpána", //1 f1
  "Epifanie", //2 t f3
  "Masopustní neděle", //3 e0
  "Popeleční středa", //4 t e1
  "Květná neděle", //5 e2
  "Zelený čtvrtek", //6 e3
  "Velký pátek", //7  e4
  "Boží hod velikonoční", //8 t e5
  "Nanebevstoupení Páně", //9 e6
  "Neděle po nanebevstoupení", //10 e7
  "Hod. sv. Ducha", //11 e8
  "Hod sv. Trojice" //12 t e9
};

const time_t easter_related_timedelta[] =
{
  -7 * SECONDS_IN_WEEK,
  -46 * SECONDS_IN_DAY,
  -1 * SECONDS_IN_WEEK,
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
  feast_name[0],
  feast_name[2],
  feast_name[4],
  feast_name[8],
  feast_name[12]
};

char * is_fixed[] =
{
  feast_name[0],
  feast_name[1],
  feast_name[2],
};