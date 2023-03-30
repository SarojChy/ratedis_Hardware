String httpGET_Request(String getDataEND) {
  HTTPClient http;
  WiFiClient client;
  http.begin(client, getDataEND);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode  = http.GET();
  String payload = "{}";
  Serial.println("Get Response Code " + String(httpResponseCode));
  if (httpResponseCode > 0) {
    payload = http.getString();
    Serial.print("Response data: ");
    Serial.println(payload);
  }
  http.end();
  return payload;
}
String httpGET_ack(String postDataEND) {
  HTTPClient http;
  WiFiClient client;
  http.begin(client, postDataEND);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode  = http.GET();
  String ack_payload = "{}";
  Serial.println("ACK response code: " + String(httpResponseCode));
  if (httpResponseCode > 0) {
    ack_payload = http.getString();
    Serial.print("Response ack_data: ");
    Serial.println(ack_payload);
  }
  http.end();
  return ack_payload;
}

String http_NepaliTime(String getNepaliDate) {
  HTTPClient http;
  WiFiClient client;
  http.begin(client, getNepaliDate);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode  = http.GET();
  String Date_Payload = "{}";
  Serial.println("Nepali date response code: " + String(httpResponseCode));
  if (httpResponseCode > 0) {
    Date_Payload = http.getString();
    Serial.print("Nepalidate: ");
    Serial.println(Date_Payload);
  }
  http.end();
  return  Date_Payload;
}
