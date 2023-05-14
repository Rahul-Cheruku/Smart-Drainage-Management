#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
HTTPClient http;
const char* ssid = "ssip23";
const char* password = "12345678";


void setup () {

  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D3, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);
  digitalWrite(D8, LOW);
  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {

if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
  Serial.print("connection established");
    


    String url = "https://192.168.62.163:5000/currentstatus/";
    String str_dist;
    delay(2000);
    int float1 = digitalRead(D0);
    int float2 = digitalRead(D1);
    int float3 = digitalRead(D3);
    int float4 = digitalRead(D5);
    delay(1000);
 if  (float4 == HIGH) 
{
    // The condition is true, do something.

        str_dist = "uniqueid_node2_currentlevel_4";
        digitalWrite(D6, HIGH);
        digitalWrite(D7, LOW);
        // blue
        digitalWrite(D8, LOW);


}
//  else if  (float3 == HIGH) 
// {
//     // The condition is true, do something.

//         str_dist = "uniqueid_node2_currentlevel_3";
//         digitalWrite(D6, LOW);
//         digitalWrite(D7, LOW);
//         digitalWrite(D8, HIGH);

// }
//  else if  (float2 == HIGH) 
// {
//     // The condition is true, do something.

//         str_dist = "uniqueid_node2_currentlevel_2";
//         digitalWrite(D6, LOW);
//         digitalWrite(D7, LOW);
//         digitalWrite(D8, HIGH);

// }
else
{
    // Oops, the condition is false, do something else!
       str_dist = "uniqueid_node2_currentlevel_1";
       digitalWrite(D6, LOW);
        digitalWrite(D7, HIGH);
        digitalWrite(D8, LOW);

}
    String stringThree;
    stringThree =  url + str_dist;
    Serial.println(stringThree);

     
    http.begin(wifiClient, stringThree);  //Specify request destination
    int httpCode = http.GET();     //Send the request                                                           
    // Serial.print(httpCode);
    if (httpCode > 0) { //Check the returning code
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    http.end();   //Close connection
}
else{ 
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }
  Serial.print("connection established");

}
  
 


  delay(60000);    //Send a request every 30 seconds
}
