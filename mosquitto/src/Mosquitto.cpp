#include <arduino.h>
#include <ESP8266WiFi.h>
#include "Mosquitto.h"


#define connectWifi true

// Configurations
String name =  "groupdiot";
//--- WiFi Credentials
const char* ssid = "IoTnodes"; //
const char* password = "node1234"; //T@nw7yGs

//const char* mqttServer = "iot";
//---MQTT server Credentials
IPAddress mqttServer(192,168,4,1);
const int mqttPort = 1883;
const char* mqttUser = "nodes";
const char* mqttPassword = "node1234";

// test online server
//const char* ssid = "CHiPhone"; 
//const char* password = "12345abcde"; //T@nw7yGs
//const char* ssid = "dlink-BAB8"; 
//const char* password = "qwertyui8";
//const char* mqttServer = "broker.hivemq.com";
//const int mqttPort = 1883;


void callback(char* topic, byte* payload, unsigned int length) {
    String msg_received;
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    
    Serial.print("Message:");
    msg_received = "";
    for (unsigned int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
        msg_received.concat((char)payload[i]);
    }
}
PubSubClient& Mosquitto::getClient(){
    return this->client;
}
void Mosquitto::init(){
    Serial.begin(9600);
    if(connectWifi == true){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
  
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
    
    while (!client.connected()) {
      Serial.println("Connecting to MQTT...");
  
      if (client.connect("ESP8266Client")) {//, mqttUser, mqttPassword 
  
        Serial.println("connected");  
        Serial.print(client.state());  
      } else {
  
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
  
      }
    }
    this->client.subscribe(name.c_str(),1);
    Serial.println("Init done. Subcribing to \""+ name +"\"");
  }
}