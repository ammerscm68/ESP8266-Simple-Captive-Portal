/* ***************** Captive Portal *********************/
IPAddress cpIP(192, 168, 10, 1);  // Captive Portal IP-Adresse - outside of the router's own DHCP range

void clearscreen() { 
for(int i=0; i<10; i++) {
Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
}

// *******************************************************************************

void CaptivePortal() {
WiFi.mode(WIFI_AP);
WiFi.softAPConfig(cpIP, cpIP, IPAddress(255, 255, 255, 0));   //Captive Portal IP-Adress
WiFi.softAP(ProgramName, "");
// Webserver - Ausgabe wenn Link nicht gefunden wurde
server.onNotFound(WebSiteNotFound);
server.on("/",  handlePortal);
server.begin();  
}

// *******************************************************************************

void handlePortal() {
String HTMLString; 
String ssid; // for Sort SSID's
int loops = 0; // for Sort SSID's
if (ProgramName == "") {ProgramName = "Hostname";} 
WiFi.scanDelete(); // WLAN-Scan zurücksetzen
  // Wenn gespeichert Button betätigt wurde 
// Serial.println((server.method() == HTTP_GET) ? "server.method() = GET" : "server.method() = POST");  // only for debuging
  if (server.method() == HTTP_POST) {
    // Einstellungen speichern
    WiFi_SSID = server.arg("ssid"); // WiFi-SSID
    WiFi_PassWD = server.arg("password"); // WiFi-Password
    // OPEN_WEATHER_MAP_API_KEY = server.arg("apikey"); // OpenWeatherMap - API-Key  -Parameter
    // OPEN_WEATHER_MAP_LOCATION_ID = server.arg("cityid"); // OpenWeatherMap - City ID -Parameter
    
    if (WiFi_SSID != "" && WiFi_PassWD != "") { 
    Serial.println("SSID: "+WiFi_SSID);
    Serial.println("Passwort: "+WiFi_PassWD);  
    HTMLString = "<!doctype html><html lang='de'>";
    HTMLString += "<head><meta charset='utf-8'>";
    HTMLString += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    HTMLString += "<title>WiFi-Manager</title>";
    HTMLString += "<style>";
    HTMLString += "*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#f5f5f5;}.form-control{display:block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:400px;padding:15px;margin:auto;}h1,p{text-align: center}";
    HTMLString += "h5 { font-size: 24px; text-align:center; margin-top: 0px; margin-bottom: 10px;}"; 
    HTMLString += "h6 { font-size: 18px; text-align:center; margin-top: 0px; margin-bottom: 10px;}";
    HTMLString += "</style>";
    HTMLString += "</head>";
    HTMLString += "<body><main class='form-signin'>";
    HTMLString += "<h1>WiFi-Manager</h1>";
    HTMLString += "<h5>("+ProgramName+")</h5>";
    HTMLString += "<br/>";
    HTMLString += "<h6>Die Einstellungen wurden gespeichert</h6>";
    HTMLString += "<h6>Das Programm wird neu gestartet</h6>";
    HTMLString += "</main>";
    HTMLString += "</body>";
    HTMLString += "</html>";
    server.send(200, "text/html", HTMLString);  
    // here Save Data
    // ...
    MyWaitLoop(2000);
    ESP.restart(); // restart program
    } else
       {
    HTMLString =  "<!doctype html><html lang='de'>";
    HTMLString += "<head><meta charset='utf-8'>";
    HTMLString += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    HTMLString += "<title>WiFi-Manager</title>";
    HTMLString += "<style>";
    HTMLString += "*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#f5f5f5;}.form-control{display:block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:400px;padding:15px;margin:auto;}h1,p{text-align: center}";
    HTMLString += "h5 { font-size: 24px; text-align:center; margin-top: 0px; margin-bottom: 10px;}"; 
    HTMLString += "h6 { font-size: 18px; text-align:center; margin-top: 0px; margin-bottom: 10px;}";
    HTMLString += "</style>";
    HTMLString += "</head>";
    HTMLString += "<body><main class='form-signin'>";
    HTMLString += "<h1>WiFi-Manager</h1>";
    HTMLString += "<h5>("+ProgramName+")</h5>";
    HTMLString += "<br/>";
    HTMLString += "<h6>Die Einstellungen sind unvollständig !</h6>";
    HTMLString += "<h6>Einstellungen wurden nicht gespeichert</h6>";
    HTMLString += "<br/>";
    HTMLString += "<a href =\"/\"><button class=\"button\">zurück zur Startseite</button></a>";
    HTMLString += "</main>";
    HTMLString += "</body>";
    HTMLString += "</html>";  
    server.send(200, "text/html", HTMLString);
       }
  } else {
    // Captive Portal
    int n = WiFi.scanNetworks(false, false); //WiFi.scanNetworks(async, show_hidden)
    HTMLString =  "<!doctype html><html lang='de'>";
    HTMLString += "<head><meta charset='utf-8'>";
    HTMLString += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
    HTMLString += "<title>WiFi-Manager</title>";
    HTMLString += "<style>";
    HTMLString += "*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#f5f5f5;}.form-control{display:block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:400px;padding:15px;margin:auto;}h1,p{text-align: center}";
    HTMLString += "h5 { font-size: 24px; text-align:center; margin-top: 0px; margin-bottom: 10px;}"; 
    HTMLString += "h6 { font-size: 18px; margin-left: 110px; margin-top: 15px; margin-bottom: 5px; color: #0245b0;}";
    HTMLString += "h7 { font-size: 20px; font-weight: bold; margin-left: 110px; margin-top: 0px; margin-bottom: 5px; color: #06942c;}";
    HTMLString += "</style>";
    HTMLString += "</head>";
    HTMLString += "<body><main class='form-signin'>";
    HTMLString += "<form action='/' method='post'>";
    HTMLString += "<h1>WiFi-Manager</h1>";
    HTMLString += "<h5>("+ProgramName+")</h5>";
    HTMLString += "<br/>";
    if (n > 0) {
     // WLAN's sort by RSSI
    int indices[n];
    int skip[n];
    String ssid;
    int o = n;
    int loops = 0;
    for (int i = 0; i < n; i++) {
    indices[i] = i;}
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
          if (WiFi.RSSI(indices[j]) > WiFi.RSSI(indices[i])) {
            loops++;
            //int temp = indices[j];
            //indices[j] = indices[i];
            //indices[i] = temp;
            std::swap(indices[i], indices[j]);
            std::swap(skip[i], skip[j]);}}}
      for (int i = 0; i < n; i++) {
        if(indices[i] == -1){
          --o;
          continue;}
        ssid = WiFi.SSID(indices[i]);
        for (int j = i + 1; j < n; j++) {
          loops++;
          if (ssid == WiFi.SSID(indices[j])) {
            indices[j] = -1;}}}
    for (int i = 0; i < n; ++i){
    // Print SSID 
    if (i == 0) {
    HTMLString += "<h7 onclick='SetSSID"+(String)i+"()' id='fssid"+(String)i+"'>" + WiFi.SSID(indices[i]) + "</h7>";} else {
    HTMLString += "<h6 onclick='SetSSID"+(String)i+"()' id='fssid"+(String)i+"'>" + WiFi.SSID(indices[i]) + "</h6>";}
    HTMLString += "<script>";
    HTMLString += "function SetSSID"+(String)i+"() {document.getElementById('ssid').value = document.getElementById('fssid"+(String)i+"').innerHTML;}";
    HTMLString += "</script>";}
    } else {
    HTMLString += "<br/>";  
    HTMLString += "<br/>"; 
    HTMLString += "<h6>Es wurde kein WLAN gefunden !</h6>";
    HTMLString += "<br/>";}
    HTMLString += "<div class='form-floating'><label>SSID</label><input type='text' class='form-control' name='ssid' id='ssid' value=''></div>";
    HTMLString += "<div class='form-floating'><br/><label>Password</label><input type='password' class='form-control' name='password' id='password' value=''></div>";
    HTMLString += "<br/>";
    // ******************************************* Parameter ************************************************************************************************************************************
    // HTMLString += "<div class='form-floating'><br/><label>OpenWeatherMap - API-Key</label><input type='text' class='form-control' name='apikey' id='apikey' value='"+OPEN_WEATHER_MAP_API_KEY+"'></div>";
    // HTMLString += "<div class='form-floating'><br/><label>OpenWeatherMap - City-ID</label><input type='text' class='form-control' name='cityid' id='cityid' value='"+OPEN_WEATHER_MAP_LOCATION_ID+"'></div>";
    // ******************************************* Parameter ************************************************************************************************************************************
    HTMLString += "<br/><br/>";
    HTMLString += "<button type='submit'>Speichern</button>";
    HTMLString += "</form>";
    HTMLString += "<br/><br/>";
    HTMLString += "<form action='/' method='get'>";
    HTMLString += "<button type='submit'>Aktualisieren</button>";
    HTMLString += "</form>";
    HTMLString += "</main>";
    HTMLString += "</body>";
    HTMLString += "</html>";
    server.send(200, "text/html", HTMLString); // Captive Portal 
  }
}

// *******************************************************************************

void WebSiteNotFound() {
String HTMLString;   
HTMLString =  "<!doctype html><html lang='de'>";
HTMLString += "<head><meta charset='utf-8'>";
HTMLString += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
HTMLString += "<title>WiFi-Manager</title>";
HTMLString += "<style>";
HTMLString += "*,::after,::before{box-sizing:border-box;}body{margin:0;font-family:'Segoe UI',Roboto,'Helvetica Neue',Arial,'Noto Sans','Liberation Sans';font-size:1rem;font-weight:400;line-height:1.5;color:#212529;background-color:#f5f5f5;}.form-control{display:block;width:100%;height:calc(1.5em + .75rem + 2px);border:1px solid #ced4da;}button{border:1px solid transparent;color:#fff;background-color:#007bff;border-color:#007bff;padding:.5rem 1rem;font-size:1.25rem;line-height:1.5;border-radius:.3rem;width:100%}.form-signin{width:100%;max-width:400px;padding:15px;margin:auto;}h1,p{text-align: center}";
HTMLString += "h5 { font-size: 24px; text-align:center; margin-top: 0px; margin-bottom: 10px;}"; 
HTMLString += "h6 { font-size: 20px; text-align:center; margin-top: 0px; margin-bottom: 10px;}"; 
HTMLString += "</style>";
HTMLString += "</head>";
HTMLString += "<body><main class='form-signin'>";
HTMLString += "<h1>WiFi-Manager</h1>";
HTMLString += "<h5>("+ProgramName+")</h5>";
HTMLString += "<br/>";
HTMLString += "<h6>Die Webseite wurde nicht gefunden !</h6>";
HTMLString += "<br/><br/>";
HTMLString += "<a href =\"/\"><button class=\"button\">zurück zur Startseite</button></a>";
HTMLString += "</main>";
HTMLString += "</body>";
HTMLString += "</html>";    
server.send(200, "text/html", HTMLString);   
} 

// *******************************************************************************

void MyWaitLoop(int wlt)
{// Pause Loop
int waitloop = 0; // Variable zurücksetzen
while (waitloop < wlt) // Pause in Millisekunden
{ 
waitloop += 1; // inc waitloop 1
delay(1);
yield(); // Equivalent zu  Application.ProcessMessages; 
// Serial.println(String(waitloop));
}
}

// *******************************************************************************
