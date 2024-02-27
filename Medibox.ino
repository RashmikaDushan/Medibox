#include <Wire.h> //Library for I2C protocol
#include <Adafruit_GFX.h> // Libraries for OLED display
#include <Adafruit_SSD1306.h>
#include <WiFi.h> // WiFi library
#include "time.h" // Libraries for working with time
#include "sntp.h"

#define SCREEN_WIDTH 128 // Display width
#define SCREEN_HEIGHT 64 // Display height
#define OLED_RESET     -1 // Display reset pin
#define SCREEN_ADDRESS 0x3C //Display address for I2C protocol

Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);

const char* ssid       = "YOUR_SSID";
const char* password   = "YOUR_PASS";

const char* ntpServer1 = "pool.ntp.org"; // Servers for fetching time
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 0; // GMT offset for the location
const int   daylightOffset_sec = 3600;

const String Menu[3] = {"Set time zone","Set Alarm","Disable Alarm"}; // Menu 1 texts
const String SetTimeZone[3] = {"Set Date","Set Hour","Set Minute"}; // Menu 2 texts
const String Alarm[3] = {"Alarm-1","Alarm-2","Alarm-3"}; // Menu 3 texts

void setup() {
  Serial.begin(9600); // Start the serial communication
  if(! display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){ // Initialize the OLED display
    Serial.println("Display Initialization Failed!!!");
    for(;;);
  }

  sntp_set_time_sync_notification_cb( timeavailable );
  sntp_servermode_dhcp(1);
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);

  connect_wifi(ssid, password); // Connect to WiFi

  display.setTextSize(1); // Set the text size
  display.setTextColor(WHITE); // Set the text color
}

void loop() {
  print_line(Menu[1]);
  delay(10);
}

void print_line(String message){
  display.clearDisplay(); // Clear the diplay before printing anything
  display.setCursor(0,0); // Curser location
  display.println(message); // Print the message
}

void print_time_now(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("No time available (yet)");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void update_time(){

}

void update_time_with_check_alarm(){

}

void ring_alarm(){

}

int wait_for_button_press(){
  
}

void go_to_menu(){

}

void run_mode(){

}

void check temp(){

}

void connet_wifi(ssid, password){
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
}

void timeavailable(struct timeval *t)
{
  Serial.println("Got time adjustment from NTP!");
  printLocalTime();
}