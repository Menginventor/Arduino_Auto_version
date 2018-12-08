
int str_to_int(char* str, uint8_t start_index, uint8_t stop_index) {
  volatile  int16_t result = 0;
  volatile  int16_t place_val = 1;
  for (char i = stop_index ; i >= start_index; i--) {

    char ch = str[i];

    if (ch == '-' ) {
      result *= -1;
      break;
    }
    else if (ch < '0' || ch > '9') {
      break;
    }
    result += int(ch - '0') * place_val;
    place_val *= 10;
  }
  return result;
}
uint8_t month_int(char*date_str, uint8_t start_index) {
  const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";
  for (char i = 0; i < 12 * 3; i += 3) {
    for (char j = 0 ; j < 3; j++) {

      if (month_names[i + j] != date_str[start_index + j]) {
        break;
      }
      if (j == 2)return i / 3 + 1;
    }

  }
}

time_t str_to_time(char*date_str, char*time_str) {
  /*
    current date (at compile time) in the form mmm dd yyyy (e.g. "Jan 14 2012")
    current time (at compile time) in the form hh:mm:ss in 24 hour time (e.g. "22:29:12")
  */

  /*
     from TimeLib
    typedef struct  {
    uint8_t Second;
    uint8_t Minute;
    uint8_t Hour;
    uint8_t Wday;   // day of week, sunday is day 1
    uint8_t Day;
    uint8_t Month;
    uint8_t Year;   // offset from 1970;
    }tmElements_t, TimeElements, *tmElementsPtr_t;
  */
  TimeElements tm;

  uint8_t Second = str_to_int (time_str, 6, 7);
  uint8_t Minute = str_to_int (time_str, 3, 4);
  uint8_t Hour = str_to_int (time_str, 0, 1);
  tm.Second = Second;
  tm.Minute = Minute;
  tm.Hour = Hour;

  uint8_t Month = month_int(date_str, 0);

  uint8_t Day = str_to_int (date_str, 4, 5);

  uint8_t Year = str_to_int (date_str, 7, 10) - 1970;


  tm.Month = Month;
  tm.Day = Day;
  tm.Year = Year;

  //uint8_t Day = str_to_int (date_str, 4);
  //uint8_t Month = str_to_int (date_str, 6);
  //uint8_t Year = str_to_int (date_str, 8);  // off

  time_t t = makeTime(tm);
  return t;

}
void printTime(time_t t) {
  Serial.print(hour(t));
  Serial.print(':');
  Serial.print(minute(t));
  Serial.print(':');
  Serial.print(second(t));
  Serial.print(' ');
  Serial.print(day(t));
  Serial.print('/');
  Serial.print(dayStr(weekday(t)));
  Serial.print('/');
  Serial.print(monthStr(month(t)));
  Serial.print('/');
  Serial.println(year(t));
}

