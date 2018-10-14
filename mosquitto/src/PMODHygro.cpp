#include <arduino.h>
#include <Wire.h>
#include "PMODHygro.h"

#define I2CAddressSensor 0x40
#define SDA_PIN D2//4
#define SCL_PIN D1//5


double PMODHygro::tempCalculation(uint16_t temp){
    return (((double)(temp)/(1<<16)) * 165.0) - 40.0;
}

double PMODHygro::humidityCalculation(uint16_t upper){
    return (((double)(upper)/(1<<16)) * 100.0); 
}

//public functions
double PMODHygro::getTemperature(){
    
    return this->temperature;
}

double PMODHygro::getHumidity(){
    return this->humidity;
}

void PMODHygro::init(){
    Serial.begin(9600);
    //init 
    Wire.setClock(100000);
    Wire.begin(SDA_PIN, SCL_PIN);
    delay(100);

    // config pmod hydro sensor 
    Wire.beginTransmission(I2CAddressSensor);
    Wire.write(0x02);
    Wire.write(0x90);
    Wire.write(0x00);
    Wire.endTransmission();
    delay(20);// set time to initalize sensors

    // trigger pmod hydro sensor 
    Wire.beginTransmission(I2CAddressSensor);
    Wire.write(0x00);
    Wire.endTransmission() ;
    delay(20);
}

String PMODHygro::print_pmod_info(){
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%g", temperature);
  String str = "\nValues from PMod \n=================\nTemperature: ";
  str.concat(buffer);

  snprintf(buffer, sizeof(buffer), "%g", humidity);
  str += "\nHumidity: ";
  str.concat(buffer);

  Serial.println(str);

  return str;
}
void PMODHygro::collectTempHumidity(){
    uint16_t reading_temp;
    uint16_t reading_hum;
    Wire.requestFrom(I2CAddressSensor, 4);    // Request from Sensor, expecting 4 bytes

    if (4 <= Wire.available()) { // if four bytes are received
        reading_temp = Wire.read();  // receive high byte
        reading_temp = reading_temp << 8;    // shift 8 bits to the left
        reading_temp |= Wire.read(); // receive low byte

        reading_hum = Wire.read();  // receive high byte (overwrites previous reading)
        reading_hum = reading_hum << 8;    // shift 8 bits to the left
        reading_hum |= Wire.read(); // receive low byte as lower 8 bits

        temperature = tempCalculation(reading_temp);
        humidity = humidityCalculation(reading_hum);  
    }

    /* trigger pmod hydro sensor for new measurement */
    Wire.beginTransmission(I2CAddressSensor);
    Wire.write(0x00);
    Wire.endTransmission();
}


