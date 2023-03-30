void printData() {
  Serial.println(S_unixTime);
  Serial.println(readFile(SPIFFS, DatePath));
  Serial.println(buy_gold_22_per_tola);
  Serial.println(buy_gold_24_per_tola);
  Serial.println(buy_gold_22_per_10g);
  Serial.println(buy_silver);
  Serial.println(sell_gold_22_per_tola);
  Serial.println(sell_gold_24_per_tola);
  Serial.println(sell_gold_22_per_10g);
  Serial.println(sell_silver);
}
