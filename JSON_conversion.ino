void JSON_Conversion() {

  //    Serial.println(valueReadings);
  JSONVar myObject = JSON.parse(Data);
  //  Serial.println(myObject);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  Serial.print('\n');
  //     myObject.keys() can be used to get an array of all the keys in the object
  JSONVar keys = myObject.keys();

  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myObject[keys[i]];
    valueReadingsArr[i] = JSON.stringify(value);
    S_unixTime = valueReadingsArr[0];
    buy_gold_22_per_tola = valueReadingsArr[4];
    buy_gold_24_per_tola = valueReadingsArr[5];
    buy_gold_22_per_10g = valueReadingsArr[6];
    buy_silver = valueReadingsArr[7];
    sell_gold_22_per_tola = valueReadingsArr[8];
    sell_gold_24_per_tola = valueReadingsArr[9];
    sell_gold_22_per_10g = valueReadingsArr[10];
    sell_silver = valueReadingsArr[11];
  }
}
void DateJSON_Conversion() {

  //    Serial.println(valueReadings);
  JSONVar myObject = JSON.parse(http_NepaliTime(getNepaliDate));
  //  Serial.println(myObject);

  // JSON.typeof(jsonVar) can be used to get the type of the var
  if (JSON.typeof(myObject) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }
  Serial.print('\n');
  //     myObject.keys() can be used to get an array of all the keys in the object
  JSONVar keys = myObject.keys();

  for (int i = 0; i < keys.length(); i++) {
    JSONVar value = myObject[keys[i]];
    valueReadingsArr[i] = JSON.stringify(value);
    NepaliDate = valueReadingsArr[0];
  }
  //  Serial.println(NepaliDate);
  // extract year, month, and day components from the string
  String year = NepaliDate.substring(1, 5);
  String month = NepaliDate.substring(6, 8);
  String day = NepaliDate.substring(9, 11);
  // combine the components into a single integer
  //  int dateValue = year * 10000 + month * 100 + day;
  String dateValue = day + month + year;
  Serial.println(dateValue);
  writeFile(SPIFFS, DatePath, dateValue.c_str());
  SPIFFS_Date = readFile(SPIFFS, DatePath);
 
}
