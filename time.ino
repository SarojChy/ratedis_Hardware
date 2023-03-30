void updateTime() {
  configTime(20700, 0, "pool.ntp.org");
  time_t now = time(nullptr);
  if (now != -1) {
    strftime(AckDateString, sizeof(AckDateString), "%Y-%m-%d", localtime(&now));
    strftime(dateString, sizeof(dateString), "%d%m%Y", localtime(&now));
    strftime(timeString, sizeof(timeString), "%H%M", localtime(&now));

    strftime(Year, sizeof(Year), "%Y", localtime(&now));
    strftime(Month, sizeof(Month), "%m", localtime(&now));
    strftime(Day, sizeof(Day), "%d", localtime(&now));
    strftime(Hour, sizeof(Hour), "%H", localtime(&now));
    strftime(Min, sizeof(Min), "%M", localtime(&now));
    strftime(Sec, sizeof(Sec), "%S", localtime(&now));
  }
  Serial.println(AckDateString);
  Serial.println(dateString);
  Serial.println(timeString);
  int int_Hour = atoi(Hour);
  char f_Hour[3];
  if ( int_Hour == 0 || int_Hour == 12) {
    strncpy(f_Hour, "12", 3);
  }
  else if (int_Hour < 12) {
    strncpy(f_Hour, Hour, 3);
  }
  else if ( int_Hour > 12) {
    int int1 = int_Hour - 12;
    if (int1 <= 9) {
      String S = String("0") + String(int1);
      S.toCharArray(f_Hour, 3);
    }
    else {
      //      itoa(int1, f_Hour, 2);
      String SS = String(int1);
      SS.toCharArray(f_Hour, 3);
      //      strncpy(Hour, Hour, 3);
    }
  }
  String FormatedTime = String(f_Hour) + String(Min);
  display1.println(FormatedTime);
  Serial.println(FormatedTime);
  delay(500);
}
//void toUnixTime() {
//  struct tm timeinfo = { 0 };
//  timeinfo.tm_year = atoi(Year) - 1900; // years since 1900
//  timeinfo.tm_mon = atoi(Month);            // months since January (0-11)
//  timeinfo.tm_mday = atoi(Day);          // day of the month (1-31)
//  timeinfo.tm_hour = atoi(Hour);          // hours since midnight (0-23)
//  timeinfo.tm_min = atoi(Min);           // minutes after the hour (0-59)
//  timeinfo.tm_sec = atoi(Sec);            // seconds after the minute (0-60)
//
//  // convert the time to a Unix timestamp
//  time_t timestamp = mktime(&timeinfo);
//
//  // print the timestamp
//  Serial.println(timestamp);
//  delay(1000);
//}
