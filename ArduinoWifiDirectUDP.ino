#include "arduino_secrets.h"
#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

WiFiUDP udp;

IPAddress localIP(192, 168, 4, 1);
const int localPort = 1234;
const unsigned int TXPort = TARGET_PORT;
const char* ssid = SECRET_SSID;
const char* pass = SECRET_PASS;
// This is the default address used until an actual target has been found. 
IPAddress MyRemoteIP = IPAddress(192, 168, 4, 2);
int status = WL_IDLE_STATUS;


//Headers for the messages. 
String Message;
String S1Type = "S1";
String S2Type = "S2";
String S3Type = "S3";
String P1Type = "P1";
String P2Type = "P2";
String P3Type = "P3";
String P4Type = "P4";

// pinouts for sensors
const int Switch1 = 4;
const int Switch2 = 5;
const int Pot1 = A0;
const int Pot2 = A1;
const int Pot3 = A2;
const int Pot4 = A3;


// sensor readings
int S1Val;
int S2Val;
int S3Val;
float P1Val;
float P2Val;
float P3Val;
float P4Val;


void setup() {
  Serial.begin(9600);

  // define pin modes
  pinMode(Switch1, INPUT_PULLUP);
  pinMode(Switch2, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);


  

  // print the network name (SSID);
  Serial.print("Creating access point named: ");
  Serial.println(ssid);

  // Create open network. Change this line if you want to create an WEP network:
  status = WiFi.beginAP(ssid, pass);

  if(status == WL_AP_LISTENING){
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("Access Point Successfully Created");
  }
  
  
  Serial.println(WiFi.localIP());
  // Start UDP client on access point interface
  udp.begin(localPort);
}

void loop() {
//  Serial.println("whats up");
  // listen for incoming packets
//  int packetSize = udp.parsePacket();
//  Serial.println(packetSize);
//  IPAddress MyRemoteIP = udp.remoteIP();

  IPAddress MyRemoteIP = IPAddress(255, 255, 255, 255);

  Serial.println(MyRemoteIP);

  // read sensors. 
  P1Val = analogRead(Pot1);
  P2Val = analogRead(Pot2);
  P3Val = analogRead(Pot3);
  P4Val = analogRead(Pot4);
  S1Val = digitalRead(Switch1);
  S2Val = digitalRead(Switch2);

  // send sensor data
  SendData(MyRemoteIP, P1Type, P1Val);
  SendData(MyRemoteIP, P2Type, P2Val);
  SendData(MyRemoteIP, P3Type, P3Val);
  SendData(MyRemoteIP, P4Type, P4Val);
  SendData(MyRemoteIP, S1Type, S1Val);
  SendData(MyRemoteIP, S2Type, S2Val);
}

// some functions for formatting and sending UDP packets
void SendData(IPAddress targetIP, String Source, float Value){
    digitalWrite(LED_BUILTIN, HIGH); 
    String Content = Source + String(Value);
    //Serial.println(Content);
    char buf[Content.length() + 1];
    Content.toCharArray(buf, 50);
    udp.beginPacket(targetIP, TXPort);
    udp.write(buf);
    udp.endPacket();
    digitalWrite(LED_BUILTIN, LOW); 
}

void SendData(IPAddress targetIP, String Source, int Value){
    digitalWrite(LED_BUILTIN, HIGH); 
    String Content = Source + String(Value);
    //Serial.println(Content);
    char buf[Content.length() + 1];
    Content.toCharArray(buf, 50);
    udp.beginPacket(targetIP, TXPort);
    udp.write(buf);
    udp.endPacket();
    digitalWrite(LED_BUILTIN, LOW); 
    
}
