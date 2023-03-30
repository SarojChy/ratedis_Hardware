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
