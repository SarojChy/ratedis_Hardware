/*
 * Nepaltronix Enginnering Solution
 * Nepatronix.org
 */
#include <Arduino_JSON.h>
#include <WiFi.h>
#include <time.h>
#include <TM1640.h>  // sub-class of TM16xx
#include <TM16xxDisplay.h>
#include <TM1638Anode.h>
#include <HTTPClient.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
IPAddress localIP;
//IPAddress localIP(192, 168, 1, 200); // hardcoded
// Set your Gateway IP address
//IPAddress localGateway;
IPAddress localGateway(192, 168, 1, 1); //hardcoded
IPAddress subnet(255, 255, 0, 0);
// Search for parameter in HTTP POST request
const char* PARAM_INPUT_1 = "ssid";
const char* PARAM_INPUT_2 = "pass";
const char* PARAM_INPUT_3 = "uid";
//Variables to save values from HTML form
String Data;
String ssid;
String pass;
String ip;
String gateway;
String uid;

#define trig_pin 16 // PUSH button pin for Reseting WiFi Configuration 
#define LED 17      //LED pin for WiFi Connection Indication
// Pins for SEGMENTs dispaly
const int DIO = 2;
const int CLK = 4;
const int STB1 = 27;
const int STB6 = 13;
const int STB2 = 26;
const int STB3 = 25;
const int STB4 = 33;
const int STB5 = 32;
const int STB7 = 12;
const int STB8 = 14;
const int STB9 = 5;
const int STB10 = 18;

///////// TIME & DATE MODULE SETUP //////
TM1638Anode module1(DIO, CLK, STB1, true, 7); // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display1(&module1, 4);    // TM16xx object, 8 digits

TM1638Anode module6(DIO, CLK, STB6, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display6(&module6, 8);    // TM16xx object, 8 digits

///////// SALE SIDE MODULE SETUP //////

TM1638Anode module2(DIO, CLK, STB2, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display2(&module2, 6);    // TM16xx object, 8 digits

TM1638Anode module3(DIO, CLK, STB3, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display3(&module3, 6);    // TM16xx object, 8 digits

TM1638Anode module4(DIO, CLK, STB4, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display4(&module4, 6);    // TM16xx object, 8 digits

TM1638Anode module5(DIO, CLK, STB5, true, 7); // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display5(&module5, 6);    // TM16xx object, 8 digits

///////// BUY SIDE MODULE SETUP //////

TM1638Anode module7(DIO, CLK, STB7, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display7(&module7, 6);    // TM16xx object, 8 digits

TM1638Anode module8(DIO, CLK, STB8, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display8(&module8, 6);    // TM16xx object, 8 digits

TM1638Anode module9(DIO, CLK, STB9, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display9(&module9, 6);    // TM16xx object, 8 digits

TM1638Anode module10(DIO, CLK, STB10, true, 7);        // DIO=8, CLK=9, STB=7, activateDisplay, intensity
TM16xxDisplay display10(&module10, 6);    // TM16xx object, 8 digits
// Variables for the Timing Strings
char AckDateString[20];
char dateString[20];
char timeString[20];
char Year[10];
char Month[10];
char Day[10];
char Hour[3];
char Min[3];
char Sec[3];

unsigned long currentTime; // To store millis value
const unsigned long eventUpdateData = 1000; // Update Interval for data(Send ACK to the Server)
unsigned long prevUpdateTime = 0;
const unsigned long WifiInnterval = 5000;  //Check WiFi connection at each  5 Seconds
unsigned long prevWifievent = 0;
const unsigned long eventAPmode = 15000;  //Turn into Access point mode for WiFi configuration for 15 Secconds
unsigned long prevAPevent = 0;
const unsigned long DateUpdateInterval = 300000;  //Update Nepali Date for each 5 Minutes
unsigned long  prevDateTime = 0;
const unsigned long LED_Blink = 500; // If WiFi is not connected then LED blink for each 500 miliseconds
unsigned long LED_Prev = 0;

// File paths to save input values permanently
const char* ssidPath = "/ssid.txt";
const char* passPath = "/pass.txt";
const char* uidPath = "/uid.txt";
const char* dataPath = "/data.txt";
const char* DatePath = "/DatePath.txt";


//Your Domain name with URL path or IP address with path
String getDataEND;
String postDataEND;
//variables to store Nepali date
String getNepaliDate;
String NepaliDate;
String SPIFFS_Date;
//Variables to store Price details form server
String valueReadingsArr[9];
String valueReadings;
String S_unixTime;
String data_date;
String buy_gold_22_per_tola;
String buy_gold_24_per_tola;
String buy_gold_22_per_10g;
String buy_silver;
String sell_gold_22_per_tola;
String sell_gold_24_per_tola;
String sell_gold_22_per_10g;
String sell_silver;
//Dispaly Variables
String s_HGoldTen;
String b_HGoldTen;
String s_SilverTen;
String b_SilverTen;
String s_HGold;
String b_HGold;
String s_TGold;
String b_TGold;


void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  initSPIFFS();
  pinMode(trig_pin, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  // Load values saved in SPIFFS
  ssid = readFile(SPIFFS, ssidPath);
  pass = readFile(SPIFFS, passPath);
  uid = readFile (SPIFFS, uidPath);
  uid = uid.c_str();
  getDataEND = "http://ratedis.nepatronix.org/api/v1/device/get-rate-data/?uid=" + uid;
  getNepaliDate = "http://ratedis.nepatronix.org/api/v1/device/nepali-date/?uid=" + uid;
  Serial.println(getDataEND);
  Serial.println(ssid);
  Serial.println(pass);
  Serial.println(uid);
  for (int i = 0; i < 5; i ++) {
    WiFi.begin(ssid.c_str(), pass.c_str());  //Waits for WiFi for 5 Seconds
    delay(1000);
  }
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  //  If WiFi connected then Initializes all the parameters from server
  if ( WiFi.status() == WL_CONNECTED) {
    updateTime();
    DateJSON_Conversion();
    valueReadings = httpGET_Request(getDataEND);
    writeFile(SPIFFS, dataPath, valueReadings.c_str());
    delay(500);
  }
  Data = readFile(SPIFFS, dataPath);        // Read Data from SPIFFS
  SPIFFS_Date = readFile(SPIFFS, DatePath); // Read Date from SPIFFS
  Serial.println(SPIFFS_Date);
}

void loop() {
  currentTime = millis();
  //   Access Point configuration for WiFI and UID
  if (digitalRead(trig_pin) == LOW) {
    if (currentTime - prevAPevent >= eventAPmode) {
      AP_Mode();
      prevAPevent = currentTime;
    }
  }

  //  Check WiFi connection, if not connected then try to recoonect to the WiFi
  if ((WiFi.status() != WL_CONNECTED) && (currentTime - prevWifievent >= WifiInnterval)) {
    Serial.println("WiFi Disconnected");
    WiFi.disconnect();
    WiFi.reconnect();
    prevWifievent = currentTime;
  }

  //  If WiFi not Connected then Blinks the LED at 500 miliseconds intervals
  if ((WiFi.status() != WL_CONNECTED) && (currentTime - LED_Prev >= LED_Blink)) {
    digitalWrite(LED, !digitalRead(LED));
    LED_Prev = currentTime;
  }
  else {
    //  If connected the just LIGHT the LED ON
    digitalWrite(LED, HIGH);
  }

  //  Check for New Data Update in each 1 seconds
  if ((WiFi.status() == WL_CONNECTED) && (currentTime - prevUpdateTime >= eventUpdateData))  {
    if (httpGET_ack(postDataEND) == "\"not_latest\"") {
      valueReadings = httpGET_Request(getDataEND);
      writeFile(SPIFFS, dataPath, valueReadings.c_str());
      Data = readFile(SPIFFS, dataPath);
    }
    prevUpdateTime = currentTime;
  }
  //  Update Nepali date at each 5 minutes interval
  if ((WiFi.status() == WL_CONNECTED) && (currentTime - prevDateTime >= DateUpdateInterval)) {

    DateJSON_Conversion();  //Receives New date from Server
    prevDateTime = currentTime;
  }

  JSON_Conversion();  //  Converst the price details from JSONs
  printData(); //Print data to Serial Monitor
  dispalyData(); // Display data to Dispaly Board
  updateTime(); // Update Time and display to Board
  //Conversion Of UnixTime to unsigned long
  unsigned long unixTime = strtoul(S_unixTime.c_str(), NULL, 10);
  // Dynamic String for POST the UID and Unix time for ACK
  postDataEND = "http://ratedis.nepatronix.org/api/v1/device/send-ack/?uid=" + uid + "&timestamp=" + unixTime;
}
