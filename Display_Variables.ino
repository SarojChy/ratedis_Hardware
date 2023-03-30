void assigningValue() {
  s_HGold = sell_gold_24_per_tola;
  b_HGold = buy_gold_24_per_tola;

  s_TGold = sell_gold_22_per_tola;
  b_TGold = buy_gold_22_per_tola;

  s_HGoldTen = sell_gold_22_per_10g;
  b_HGoldTen = buy_gold_22_per_10g;

  s_SilverTen = sell_silver;
  b_SilverTen = buy_silver;
}
void dispalyData() {
  assigningValue();
  display2.println(s_HGoldTen);
  display3.println(s_SilverTen);
  display4.println(s_HGold);
  display5.println(s_TGold);
  display7.println(b_HGoldTen);
  display8.println(b_SilverTen);
  display9.println(b_HGold);
  display10.println(b_TGold);
  display6.println(readFile(SPIFFS, DatePath));
}
