/* ***************** My Program *********************/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer  server(80);

String WiFi_SSID = ""; // Value from Captive Portal
String WiFi_PassWD = ""; // Value from Captive Portal

// Example Captive Portal Parameter Values
// OPEN_WEATHER_MAP_API_KEY = ""; // Value from Captive Portal
// OPEN_WEATHER_MAP_LOCATION_ID = ""; // Value from Captive Portal 

String ProgramName = "MyProgram"; // Name from your Programm or Hostname

void setup() {
Serial.begin(115200); // Serielle Verbindung mit 115200 Baud  
clearscreen(); // Serial Monitor Clear

// Load your Adjustments (Example from LittleFS)

if (WiFi_SSID == "" | WiFi_PassWD == "") {CaptivePortal();} else 
{// here your program
  
} // here your programm - end 
}

// *******************************************************************************

void loop() {
if (WiFi_SSID == "" | WiFi_PassWD == "") {  
server.handleClient();} else
{// here your programm
  
} // here your programm - end
}

// *******************************************************************************
