#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <TaskScheduler.h>
#include <Wire.h>
#include <stdio.h>
#include "HpmaObject.h"
#include "PMODHygro.h"
#include "Utils.h"
#include "IntSensors.h"
#include "Mosquitto.h"

#define WifiEnabled false
Utils utils; // common utils

PMODHygro pmodHygro; // Get temp humidity sensors
IntSensors intSensors; // Get int Sensors
WiFiClient client;
#if WifiEnabled
Mosquitto mosquitto(client);
#endif 
Scheduler userScheduler; // to control your personal task
void sendMessage();
Task taskSendMessage( TASK_SECOND * 4 , TASK_FOREVER, &sendMessage );

void sendMessage(){
  //client.publish("groupdiot", hpma_text.c_str());
  //client.publish("groupdiot", pmod_text.c_str());
}


void setup() {
  Serial.begin(9600);

  #if WifiEnabled
  mosquitto.init();
  #endif
  pmodHygro.init();
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  #if WifiEnabled
  mosquitto.getClient().loop();
  #endif

  userScheduler.execute(); // it will run mesh scheduler as well
  pmodHygro.collectTempHumidity();
  pmodHygro.print_pmod_info();
  delay(1000);
}