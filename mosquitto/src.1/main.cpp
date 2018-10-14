#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TaskScheduler.h>
#include <Wire.h>
#include <stdio.h>
#include "HpmaObject.h"
#include "PMODHygro.h"
#include "Utils.h"

#define SDA_PIN D2//4
#define SCL_PIN D1//5
#define DDEControllerAddress 0x2A
#define name "groupdiot"
#define connectWifi true

// Connect to the WiFi
const char* ssid = "IoTnodes"; //
const char* password = "node1234"; //T@nw7yGs

//const char* mqttServer = "iot";
IPAddress mqttServer(192,168,4,1);
const int mqttPort = 1883;
const char* mqttUser = "nodes";
const char* mqttPassword = "node1234";

WiFiClient espClient;
PubSubClient client(espClient);
// test online 
//const char* ssid = "CHiPhone"; //
//const char* password = "12345abcde"; //T@nw7yGs
//const char* ssid = "dlink-BAB8"; 
//const char* password = "qwertyui8";
//const char* mqttServer = "broker.hivemq.com";
//const int mqttPort = 1883;

Utils utils;

PMODHygro pmodHygro;
HpmaObject hpmaObject; // create hpmaObject

Scheduler userScheduler; // to control your personal task
void sendMessage();
Task taskSendMessage( TASK_SECOND * 4 , TASK_FOREVER, &sendMessage );

const byte ledPin = 2; // Pin with LED on Adafruit Huzzah

String msg_received;
String print_hpma_info();
String print_pmod_info();

void init_hpma(){
  // config hpma all in one sensor
  //I2C start
  Wire.beginTransmission(DDEControllerAddress);
  Wire.write(0xC0); //Scan Start
  Wire.write(0xFF);  // all init
  if(Wire.endTransmission() == 0)
    Serial.println("Initialized hpma.");
  else
    Serial.println("Didnt Initialized hpma.");
  delay(80); 
}
void collect_hpma(){
  uint16_t reading_temp[7] ={};
  Serial.println("~~~~~~~~~~~~~~~~ Refreshing data ~~~~~~~~~~~~~~~~");
  init_hpma();
  for (int i = 1, j = 0; i <= 14; j++){
    //I2C start
    Wire.beginTransmission(DDEControllerAddress);
    Wire.write(i++);  // get all sensors
    if(Wire.endTransmission() == 0){}
      //Serial.println("Requesting data from hpma."); 

    Wire.requestFrom(DDEControllerAddress,2);

    while (Wire.available()==0);
    reading_temp[j] = Wire.read(); //read data from register
    reading_temp[j] = reading_temp[j] << 8;    // shift high byte to be high 8 bits
    //I2C start
    Wire.beginTransmission(DDEControllerAddress);
    Wire.write(i++);  // get all sensors
    if(Wire.endTransmission() == 0){}
      //Serial.println("Requesting data from hpma."); 

    Wire.requestFrom(DDEControllerAddress,2);

    while (Wire.available()==0);
    reading_temp[j] |= Wire.read(); //read data from register
  }

  //set values
  hpmaObject.setReading_temp(reading_temp[0]);
  hpmaObject.setReading_humidity(reading_temp[1]);
  hpmaObject.setReading_light(reading_temp[2]);
  hpmaObject.setReading_audio(reading_temp[3]);
  hpmaObject.setReading_battery_volts(reading_temp[4]);
  hpmaObject.setReading_co2(reading_temp[5]);
  hpmaObject.setReading_voc(reading_temp[6]);
}
void sendMessage(){
  
  collect_hpma();
  String hpma_text = print_hpma_info();
  /*
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%g", temperature);

  String textToSend = "Temperature: ";
  textToSend.concat(buffer);
  snprintf(buffer, sizeof(buffer), "%g", temperature);
  textToSend.concat("\nHumidity: ");
  snprintf(buffer, sizeof(buffer), "%g", humidty);
  textToSend.concat(buffer);
  textToSend.concat("\n");
  */
  //client.publish("groupdiot", hpma_text.c_str());
  //client.publish("groupdiot", pmod_text.c_str());
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  msg_received = "";
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg_received.concat((char)payload[i]);
  }
}


void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
 // digitalWrite(2,1);
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
    client.subscribe(name,1);
  }
  
  Serial.println("Init done. Subcribing to groupidiot");

  
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
  
}
  
String print_hpma_info(){

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_temp());
  String str = "\nValues from hpma \n=================\nTemperature: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_humidity());
  str += "\nHumidity: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_light());
  str += "\nLight: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_battery_volts());
  str += "\nBattery Volts: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_co2());
  str += "\nCO2: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_voc());
  str += "\nVOC: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", hpmaObject.getReading_audio());
  str += "\nSound(db): ";
  str.concat(buffer);
  str += "\n";
  Serial.println(str);

  return str;
}

void loop() {
  if(connectWifi == true)
  client.loop();
  userScheduler.execute(); // it will run mesh scheduler as well
}