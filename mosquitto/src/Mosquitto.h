#include <arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#ifndef MOSQUITTO_H
#define MOSQUITTO_H
class Mosquitto{
    
    PubSubClient client;

    public: 
    Mosquitto(WiFiClient espClient): client(espClient){
        //consturctor
    }
    
    void init();
    PubSubClient& getClient();
      
};

#endif